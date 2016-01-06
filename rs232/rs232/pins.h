#ifndef PINS_H_
#define PINS_H_

/** PINS **/

//wejœcie ADC
#define ADC_IN_DDR DDRA
#define ADC_IN_PIN PA7

//L297
#define L297_ENABLE_DDR DDRA
#define L297_ENABLE_PORT PORTA
#define L297_ENABLE_PIN PA0

#define L297_DIR_DDR DDRA
#define L297_DIR_PORT PORTA
#define L297_DIR_PIN PA1

#define L297_CLOCK_DDR DDRA
#define L297_CLOCK_PORT PORTA
#define L297_CLOCK_PIN PA2

//leds
#define LED_TX_DDR
#define LED_TX_PORT
#define LED_TX_PIN

#define LED_RX_DDR DDRD
#define LED_RX_PORT PORTD
#define LED_RX_PIN PD7



#define INIT_PINS 1

void initPins()
{
	#if INIT_PINS == 1
	//LED_TX_DDR |= _BV(LED_TX_PIN);
	LED_RX_DDR |= _BV(LED_RX_PIN);
	#endif
}






#endif /* PINS_H_ */