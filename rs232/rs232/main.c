/////////////////////////
//////// DEFINE ////////
///////////////////////

//#define F_CPU 1000000UL
#define BAUD 9600 //usart baudrate
#define USART_BUF_SIZE 50 //rozmiar bufora usart
#define VREF 2.59 //definicja napięcia referencyjnego


/////////////////////////
//////// INCLUDE ///////
///////////////////////

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>
#include <util/delay.h>
//#include <avr/sleep.h>
#include <util/setbaud.h>
#include <avr/eeprom.h>
//#include <avr/power.h>
#include "pins.h"
#include "global.h"
#include "accel/mma7455.h"



/////////////////////////
//////// GLOBAL ////////
///////////////////////

//accel
volatile double accel_x = 0;
volatile double accel_y = 0;
volatile double accel_z = 0;

//usart
volatile uint8_t usartIsReceived = 0; //flaga odbioru
volatile char usartReceivedByte; //bufor odbierania
volatile unsigned int usartBuforIndex; //indeks bufora nadawania
char usartBufor[USART_BUF_SIZE] = "#Connected"; //bufor nadawania

volatile uint32_t REFRESH = 0;

////////////////////////
////// FUNCTIONS //////
//////////////////////

/** USART **/

void USART_init(void)
{
	//ustaw obliczone przez makro wartości
	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;
	#if USE_2X
	UCSRA |=  (1<<U2X);
	#else
	UCSRA &=~ (1<<U2X);
	#endif

	UCSRC = (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);
	//bitów danych: 8
	//bity stopu:  1
	//parzystość:  brak
	
	//nadajnik i odbiornik oraz przerwania odbiornika
	UCSRB = (1<<TXEN) | (1<<RXEN) | (1<<RXCIE);
}

void USART_sendBufor(void)
{
	for(int z=0; z<USART_BUF_SIZE; z++)
	{
		//czy to koniec tekstu w tablicy
		if(usartBufor[z] == 0)
		{
			//tak znaleziono koniec tekstu, dodajemy znak CR
			//usartBufor[z]  = 13;  //znak powrotu karetki CR (Carriage Return)
			//usartBufor[z+1] = 10; //znak nowej linii LF (Line Feed)
			//usartBufor[z+2] = 0;  //znak końca ciągu tekstu w tablicy
			usartBufor[z] = '\n';
			usartBufor[z+1] = 0;
			break;
		}
	}

	//Zaczekaj, aż bufor nadawania będzie pusty
	while (!(UCSRA & (1<<UDRE)));

	//następny znak do wysyłki to znak nr 1
	usartBuforIndex = 0;

	//włącz przerwania pustego bufora UDR, co rozpocznie transmisję aktualnej zawartości bufora
	UCSRB |= (1<<UDRIE);
}

void USART_Send(char _cmd[USART_BUF_SIZE])
{
	sprintf(usartBufor, "%s", _cmd);
	USART_sendBufor();
}

void processReceivedCommand(char _x);


/** ADC **/

void ADC_init(void)
{
	ADCSRA = (1<<ADEN)  //włączenie ADC
	|(1<<ADPS0) //preskaler na  8!!  [50-200kHz] max!
	|(1<<ADPS1);
	
	ADMUX = (1<<REFS0) | (1<<REFS1)   //2.56 internal jako napięcie referencyjne
	| ADC7; //wybór kanału pomiarowego
	
	ADC_IN_DDR &=~ (1<<ADC_IN_PIN);              //Ustawienie Wejścia ADC
}

void ADC_measure(void)
{
	float adc;//zmienna do obliczeń napięcia
	char wynik[10] = "";//bufor tekstowy, wyczyszczenie bufora
	
	ADCSRA |= (1<<ADSC);//ADSC: Uruchomienie pojedynczej konwersji
	
	//while(ADCSRA & (1<<ADSC)); //czeka na zakończenie konwersji
	while(!(ADCSRA&(1<<ADIF)));
	
	adc=((ADC*VREF)/1024)*2.0;
	//adc = ((((ADC*VREF)/1024)/VREF)*5.0) + (((1-(2.5/2.6)))*((((ADC*VREF)/1024)/VREF)*5.0));
	//adc = ((((ADC*VREF)/1024)/VREF)*5);
	//adc = ((((ADC*VREF)/1023)/VREF)*(((((ADC*VREF)/1023)))*2));
	//adc=ADC;      //przeliczenie wartości na napięcie
	
	sprintf(wynik,"^%1.3f",adc);   //konwersja na łańcuch znakowy
	USART_Send(wynik);

	ADCSRA |= (1<<ADIF);
}


/** ACCELEROMETER **/

void ACCEL_getAndSendData()
{
	mma7455_getdata((double*)&accel_x, (double*)&accel_y, (double*)&accel_z);
	char arr[sizeof(accel_x) + sizeof(accel_y) + sizeof(accel_z) + (sizeof(char) * 4)];
	char beg = '~';
	char separator[3] = {'x', 'y', 'z'};
	sprintf(arr,"%c%c%0.2f%c%0.2f%c%0.2f", beg,separator[0],accel_x,separator[1],accel_y,separator[2],accel_z);
	
	USART_Send(arr);
}

void ACCEL_enableTimer()
{
	TCCR1B |= _BV(CS11) | _BV(CS10); // preskaler 64
	TIMSK |= (1<<TOIE1); // Przerwanie overflow
	TCNT1 = TIMER1; // 1Hz = 1000ms
}


/** MOTORS **/

//dc
void MOTOR_DC_init()
{
	// initialize TCCR0 -> PWM <-
	TCCR0 |= (1<<WGM00)|(1<<WGM01) // Fast PWM
	|(1<<COM00) | (1<<COM01) // Clear OC0 on compare match, set OC0 at BOTTOM (non-inverting mode)
	|(1<<CS01); // clk/1(No prescaling)
	
	// make sure to make OC0 pin (pin PB3 for atmega32/16) as output pin
	DDRB |= (1<<PB3);
}

void MOTOR_DC_enable(uint8_t enabled)
{
	if(enabled)
	{
		BIT_SET(PB3, DDRB);
	}
	else
	{
		BIT_CLEAR(PB3, DDRB);
	}
}

#define kAccelStep 5
void MOTOR_DC_accelerate_step() {
	uint8_t x = OCR0;
	if(x < (255 - kAccelStep))
	OCR0 = x + kAccelStep;
	else
	OCR0 = 255;
}

//stepper
void MOTOR_STEPPER_init()
{
	TCCR2 |= _BV(CS21); // preskaler 8
	TIMSK |= (1<<TOIE2);           // Przerwanie overflow (przepełnienie timera)
	TCNT2 = TIMER2; // 1500Hz ? //todo: sprawdzić
	
	//pins init
	L297_ENABLE_DDR |= _BV(L297_ENABLE_PIN);
	L297_DIR_DDR |= _BV(L297_DIR_PIN);
	L297_CLOCK_DDR |= _BV(L297_CLOCK_PIN);
}

void MOTOR_STEPPER_enable(uint8_t enabled)
{
	if(enabled)
	{
		BIT_SET(L297_ENABLE_PIN, L297_ENABLE_PORT);
	}
	else
	{
		BIT_CLEAR(L297_ENABLE_PIN, L297_ENABLE_PORT);
	}
}

void MOTOR_STEPPER_direction(char dir)
{
	if(dir == 'R' || dir == 'r')
	{
		BIT_SET(L297_DIR_PIN, L297_DIR_PORT);
	}
	if(dir == 'L' || dir == 'l')
	{
		BIT_CLEAR(L297_DIR_PIN, L297_DIR_PORT);
	}
}

void MOTORS_DISABLE_ALL()
{
	MOTOR_STEPPER_enable(0);
	MOTOR_DC_enable(0);
}


/////////////////////////
////// INTERRUPTS //////
///////////////////////

/** TIMERS **/

ISR(TIMER2_OVF_vect) //timer2, stepper
{
	TCNT2 = TIMER2;
	L297_CLOCK_PORT ^= _BV(L297_CLOCK_PIN);
}

ISR(TIMER1_OVF_vect) //timer1, accel
{
	TCNT1 = TIMER1;
	ACCEL_getAndSendData();
}


/** USART **/

ISR(USART_RXC_vect) //przerwanie generowane po odebraniu bajtu
{
	//todo: led usart
	usartReceivedByte = UDR;
	usartIsReceived = 1;
}

ISR(USART_UDRE_vect) //przerwanie generowane, gdy bufor nadawania jest już pusty,
{
	//todo: przerwanie w main() ??
	if(usartBufor[usartBuforIndex]!= 0) //sprawdzamy, czy bajt do wysłania jest znakiem końca tekstu, czyli zerem
	{
		UDR = usartBufor[usartBuforIndex++]; //załaduj znak do rejestru wysyłki i ustaw indeks na następny znak
	}
	else
	{
		//koniec tablicy usartBufor[]
		UCSRB &= ~(1<<UDRIE); //wyłącz przerwania pustego bufora nadawania
	}
}






//** MAIN **//

int main(void)
{
	JTAG_disable();
	sei(); //włącz przerwania globalne

	initPins();
	USART_init();
	USART_sendBufor();  //wysłanie buforu na starcie
	ADC_init();
	ACCEL_init(); //init mma7455
	ACCEL_enableTimer(); //start accelerometer
	
	MOTOR_STEPPER_init();
	//MOTOR_STEPPER_enable(1);
	
	
	
	
	//todo: rx led w przerwaniu czy w main()
	

	while(1)
	{
		//todo: ??
		//REFRESH++;
		//if(REFRESH >= F_CPU/40)
		//{
			////co 1 sekunde????????????????
			//MOTORS_DISABLE_ALL();
			//REFRESH = 0;
		//}
		
		if(usartIsReceived)
		{
			BLINK_LED(LED_RX_PIN, LED_RX_PORT, 20);
			usartIsReceived = 0;
			processReceivedCommand(usartReceivedByte);
		}


		
		
		
		
		
		
		
		
		
		
		
		
		
		// while (UCSRB & (1<<UDRIE)); ??????????????????????
	}
	
}

void processReceivedCommand(char _x)
{
	//char temp[USART_BUF_SIZE] = {_x};
	//char temp[] = {_x, 0};
	switch (_x)
	{
		case 'R':
		MOTOR_STEPPER_direction('R');
		MOTOR_STEPPER_enable(1);
		break;
		
		case 'r':
		MOTOR_STEPPER_enable(0);
		break;
		
		case 'L':
		MOTOR_STEPPER_direction('L');
		MOTOR_STEPPER_enable(1);
		break;
		
		case 'l':
		MOTOR_STEPPER_enable(0);
		break;
		
		case '$':
		REFRESH = 0;
		break;

		case 'v':
		ADC_measure();
		break;

		default:
		USART_Send("Unknown command received");
		break;
	}
}






//#if MMA7455_GETATTITUDE == 1
//double pitch = 0;
//double roll = 0;
//mma7455_getpitchroll(ax, ay, az, &pitch, &roll);
//pitch = pitch * 180 / M_PI; //radians to degree
//roll = roll * 180 / M_PI; //radians to degree
//dtostrf(pitch, 3, 5, itmp); uart_puts(itmp); uart_putc(' ');
//dtostrf(roll, 3, 5, itmp); uart_puts(itmp); uart_putc(' ');
//#endif
