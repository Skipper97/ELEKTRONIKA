#ifndef global_h__
#define global_h__

//*** MACROS ***//

#define BIT_SET(Bit, Register)        (Register |= (1<<Bit))
#define BIT_CLEAR(Bit, Register)      (Register &=~ (1<<Bit))
#define BIT_CHECK(Bit, Register)      (Register & (1<<Bit))

#define BLINK_LED(Bit, Register, Duration_ms) ({Register |= (1<<Bit); _delay_ms(Duration_ms); Register &=~ (1<<Bit); })

//#define TIMER1 49911 //453
#define TIMER2 170 //170
#define TIMER1 63973 //453


//*** FUNCTIONS ***//

// JTAG disabler
void JTAG_disable()
{
	MCUCSR |= (1<<JTD);
	MCUCSR |= (1<<JTD);
	MCUCSR |= (1<<JTD);
	MCUCSR |= (1<<JTD);
}




//*** ADC ***//

// ADC channels
#define ADC0
#define ADC1 (1<<MUX0)
#define ADC2 (1<<MUX1)
#define ADC3 (1<<MUX0) | (1<<MUX1)
#define ADC4 (1<<MUX2)
#define ADC5 (1<<MUX2) | (1<<MUX0)
#define ADC6 (1<<MUX2) | (1<<MUX1)
#define ADC7 (1<<MUX0) | (1<<MUX1) | (1<<MUX2)










#endif // global_h__
