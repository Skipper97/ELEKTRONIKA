/* TEST krokowca (pod unipolarny)
// TPT
// mega16+LCD
// mLCD (C0-C5)
// 14.07.2013
// aktualizacja 17.07.2013
// stan:OK!!!
// 
// UWAGA!!!
// W pliku HD44780.h nale¿y zdefiniowaæ piny, do których pod³¹czysz LCD.
*/

//#define F_CPU 8000000UL  //Program dla 8MHz. Ustaw w opcjach projektu lub
                           //usuñ znaki komentarza


#include <avr/io.h>
#include <avr/interrupt.h>

#include "HD44780.h"

#define SW1 PD6
#define SW2 PD5
#define SW3 PD4
#define DIR PD3
#define LEDG PB0
#define LEDY PB1
#define LEDR PB2
#define CLOCK PD2

volatile unsigned int i=0; // ON/OFF
volatile unsigned int j=0; // Direction

volatile unsigned int cnt  = 0;
volatile unsigned int cnt2 = 0;

// Zmienne do kontroli przycisków
uint8_t oldkey[2];
uint8_t key[2];


//*****************************************************************

void io_init(void){ //Ustawienia pinów

     //atmega16
     DDRA |= 0b00000000;
     DDRB |= 0b00000111;
     DDRD |= 0b10001100;

     //Pull Up-y
     PORTD |= (1<<SW1) | (1<<SW2) | (1<<SW3);

     i=0;
     cnt=0;
}

//*****************************************************************

void timer_init(void)
{
     TIMSK |= (1<<TOIE0); //W³¹cz przerwanie overflow (przepe³nienie timera)  
     TCCR0 |= (1<<CS01) | (1<<CS00); //preskaler
}

//*****************************************************************

void left (void) // Krêcenie w lewo  
{
 PORTD &= ~(1<<DIR);
 PORTB |= (1<<LEDG);
 PORTB &= ~(1<<LEDY);
}

//*****************************************************************

void right (void) // Krêcenie w prawo  
{
 PORTD |= (1<<DIR);
 PORTB &= ~(1<<LEDG);
 PORTB |= (1<<LEDY);
}

//*****************************************************************

void defaultThis() // Reset  
{
 PORTB &= ~(1<<LEDG);
 PORTB &= ~(1<<LEDY);
 PORTB &= ~(1<<LEDR);
 PORTD &= ~(1<<CLOCK);
}

//*****************************************************************

void lcd_layout(void) // Obs³uga LCD  
{
 LCD_Clear();
 LCD_GoTo(0,0);
 
 if (i == 1)
 {
  LCD_WriteText("Engine: OFF");
  LCD_GoTo(0,1);
  LCD_WriteText("Direction: OFF");
  defaultThis();
 }
 
 if ((i == 2) && (j == 0))
 {
  LCD_WriteText("Engine: ON");
  LCD_GoTo(0,1);
  LCD_WriteText("Direction: LEFT"); 
 }
 
 if ((i == 2) && (j == 1))
 {
  LCD_WriteText("Engine: ON");
  LCD_GoTo(0,1);
  LCD_WriteText("Direction: RIGHT"); 
 } 
}

//*****************************************************************

void readButtons() // Obsluga przycisków  
{
 oldkey[0] = 1;
 oldkey[1] = 1;
 oldkey[2] = 1;
 
 key[0]= PIND & (1<<SW1);
 key[1]= PIND & (1<<SW2);
 key[2]= PIND & (1<<SW3);
 
 if((key[0]^oldkey[0]) && (key[0]==0))
 {
  j=0;
  left();
  lcd_layout();
 }
 
 if((key[1]^oldkey[1]) && (key[1]==0))
 {
  j=1;
  right();
  lcd_layout();
 }
 
 if((key[2]^oldkey[2]) && (key[2]==0))
 {
  if (i == 1)
  {
   i = 2;
   lcd_layout();
   OCR2 = 0;
   PORTB |= (1<<LEDR);
   
   if ( j == 0 )
   {
    PORTB |= (1<<LEDY);
    PORTB &= ~(1<<LEDG);
   }
   if ( j == 1 )
   {
    PORTB |= (1<<LEDG);
    PORTB &= ~(1<<LEDY);
   }
  }
  else
  {
   i = 1;
   lcd_layout();
   OCR2 = 255;
  }
 }
}


//*****************************************************************

int main (){  //Pocz¹tek programu

 io_init();
 timer_init();

 LCD_Initalize();

 sei();

 LCD_GoTo(0,0);
 LCD_WriteText("TEST KROKOWCA");
 LCD_GoTo(0,1);
 LCD_WriteText("MIKROKONTROLERY");

 i=1;
 while (1) {
  //pêtla g³ówna
 }
}

//*****************************************************************

ISR(TIMER0_OVF_vect)//przerwanie po przepe³nieniu timera 
{
 cnt++;
 if (cnt == 100) //eliminacja drgañ styków
 {
  readButtons();
  cnt=0;
  }
 if( i == 2)
 {
  cnt2++;
  if (cnt2 == 50) // SPEED
  {
   PORTD ^= (1<<CLOCK);
   cnt2=0;
  }
 }
}
