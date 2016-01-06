/*
   KURS AVR-GCC, SERWO MODELARSKIE
   Program steruje 12 serwami modelarskimi  
 
   atmega8 (16MHz)

   Programowanie  fuse-bitów (16MHz)
   C:\>avrdude -c usbasp -p m8 -U hfuse:w:0xc9:m -U lfuse:w:0xef:m
   Odczyt
   C:\>avrdude -c usbasp -p m8 -U hfuse:r:con:h -U lfuse:r:con:h
*/

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h> 

#define BAUD 9600 // Prêdkoœæ transmisji szeregowej
#define MYUBRR  F_CPU/BAUD/16-1

#define NSERV 12

volatile unsigned char rs_in_i = 0;
volatile unsigned char rs_in_buf[2*NSERV+2]; 

// bufor  - wychylenie serw i suma kontrolna
unsigned char s_buf[NSERV+1];    
        
// Wychylenie serw, w sekcji "noinit"
unsigned char servos[NSERV] __attribute__ ((section (".noinit")));   
	     
//----------------------------------------------------------------------
// Konfiguracja USARTa
//----------------------------------------------------------------------
void USART_init(unsigned int myubrr)
{
    // Prêdkoœæ transmisji szeregowej 
    UBRRH = (unsigned char)(myubrr>>8);
    UBRRL = (unsigned char)myubrr;

    // W³¹cza nadajnik, odbiornik i przerwanie USART_RXC  
    UCSRB |= (1<<RXEN)|(1<<RXCIE);    
     
    // 8 bitów danych, 1 bit stopu, bit parzystoœci - brak
    UCSRC |= (3<<UCSZ0)|(1<<URSEL);    
}

//----------------------------------------------------------------------
// Przerwanie  "USART_RXC"
//----------------------------------------------------------------------
ISR(USART_RXC_vect)
{
	unsigned char byte = UDR;
   
	if(rs_in_i == 2*NSERV+3)
	{
		if(byte == ':')
                   rs_in_i = 0;
	}
	else  if(rs_in_i < 2*NSERV+2)
		           rs_in_buf[rs_in_i++] = byte;		    
}

//----------------------------------------------------------------------
//  Suma kontrolna ramki danych 
//----------------------------------------------------------------------
unsigned char sum(void)
{
	unsigned char i,s;
	
	for(i=0,s=0; i < NSERV+1; i++)
	                         s+= s_buf[i];
	                         
	return s;	
}

//----------------------------------------------------------------------
//  HEX_ASCII na HEX
//----------------------------------------------------------------------
signed char hex_ascii2byte(void)
{
	unsigned char i,j,b,v;
	
	for(i=0,j=0; i<2*NSERV+2; i++)
	{
		b = rs_in_buf[i];
	
		if(b >= '0' && b <= '9')
			v = b-'0';
		else if(b >= 'A' && b <= 'F')
			v = b-'A'+ 10;		
		else if(b >= 'a' && b <= 'f')
			v = b-'a'+ 10;
		else
			return -1; // b³ad
			

		if(i&1)				
		     s_buf[j++] |= v & 0x0f;
		else
		     s_buf[j] = (v<<4);
				
	}
	return 0; // ok		
}

//----------------------------------------------------------------------
// MAIN
//----------------------------------------------------------------------
int main(void)
{
    volatile unsigned char  p_c,p_d;
    volatile unsigned char n,p_cc,p_dd; 
  
	// Wyjœcia PC0..PC5	i PD2..PD7 - 12 serw
	//
	DDRC  = 0x3f;  // wyjœcia PC0..PC5 - s6..s11
	DDRD  = 0xfc;  // wyjœcia PD2..PD7 - s0..s5 
//	DDRB  = 0x00;
//	PORTB = 0x01;
    
    if(MCUCSR & (1<<PORF))
	          for(n=0; n<NSERV; n++) servos[n] = 0xb8;

   	MCUCSR = 0;  
		
    wdt_enable(WDTO_30MS); // W³¹czam watchdog 30ms

	USART_init(MYUBRR); // Konfiguracja USARTa	
	
	sei(); // W³¹cza przerwania 

	// Start Timer1, preskaler 8
	// Tajmer1 bêdzie liczy³ co ósmy cykl zegara taktuj¹cego uC (16MHz)
	// czyli co 0,5us
	TCCR1B = (1<<CS11);
	
    //   G£ÓWNA PÊTLA PROGRAMU
	while(1)
	{  		
        p_c = 0;
        p_d = 0;
 
        // Start inpulsu - Wszystkie wyjœcia w stan wysoki    
 		PORTC |= 0x3f;
		PORTD |= 0xfc;   
 
		for(n=0; n<241; n++)
		{   
			TCNT1 = 0; 	  // Zeruje Timer1 
			SFIOR = 1;    // Resetuje preskaler   	
  	
			if(n>servos[0])  p_d |= (1<<2);   
			if(n>servos[1])  p_d |= (1<<3);
			if(n>servos[2])  p_d |= (1<<4);  
			if(n>servos[3])  p_d |= (1<<5);    
			if(n>servos[4])  p_d |= (1<<6);  
			if(n>servos[5])  p_d |= (1<<7); 
           
			if(n>servos[6])  p_c |= (1<<0);  
			if(n>servos[7])  p_c |= (1<<1); 
			if(n>servos[8])  p_c |= (1<<2);  
			if(n>servos[9])  p_c |= (1<<3);
			if(n>servos[10]) p_c |= (1<<4);  
			if(n>servos[11]) p_c |= (1<<5);

            p_cc = ~p_c;
            p_dd = ~p_d; 
                 
            cli();
            // Koniec inpulsu - stan niski
            PORTD &= p_dd;
			PORTC &= p_cc;
            sei();

            // Program czeka, dopóki zawartoœæ tajmera1 jest mniejsza 
            // ni¿ 19,  czyli 9,5us od momentu zerowania tajmera
			while(TCNT1<19 ); // 0,5 * 9 = 9,5us
		}
        
		TCNT1 = 0; 	  // Zeruje Timer1
		SFIOR = 1;    // Resetuje preskaler
	   
	    // Pêtla wykonuje siê dopóki zawartoœæ tajmera1 jest mniejsza ni¿
	    // wartoœæi 35100, czyli ok 18ms od momentu zerowania tajmera
		while(TCNT1<35100)  //  0,5*3510 = 1,7550 ms
		{
		// Tutaj, w pêtli, reszta programu,
		// powinien siê wykonaæ w czasie <18ms.
		
			if(rs_in_i == 2*NSERV+2)
			{
				if(!sum())  // 
				    if(! hex_ascii2byte())
					      for(n=0; n<NSERV; n++) servos[n] = s_buf[n];
        
				rs_in_i++;
			}

		}
		// Resetuje Watchdog
		wdt_reset();   
	}

	return 0;
	
}

