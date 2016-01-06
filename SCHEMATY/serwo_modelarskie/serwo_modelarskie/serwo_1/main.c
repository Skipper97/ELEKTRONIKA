/*
   ABXYZ
   KURS AVR-GCC, SERWO MODELARSKIE
   
   przyk³ad 1
   Steruje 12 serwami
 
   atmega8 (16MHz)


   Programowanie    fuse-bitów
   C:\>avrdude -c usbasp -p m8 -U hfuse:w:0xc9:m -U lfuse:w:0xef:m
   Odczyt
   C:\>avrdude -c usbasp -p m8 -U hfuse:r:con:h -U lfuse:r:con:h
*/

#include <avr/io.h>

// Wychylenie serw
unsigned char servos[12] ;   
	     

int main(void)
{
    volatile unsigned char  n,p_c,p_d,p_cc,p_dd;
    unsigned char t; 
  
    // Pocz¹tkowe wychylenie 12 serw
    // centrum 1,5ms 
  	for(n=0; n<12; n++) servos[n] = 0x8B;
    
	// Wyjœcia PC0..PC5	i PD2..PD7 - 12 serw
	DDRC  = 0x3f;  // wyjœcia PC0..PC5 - s6..s11
	DDRD  = 0xfc;  // wyjœcia PD2..PD7 - s0..s5 

	// Start Timer1, preskaler 8
	// Tajmer1 zlicza co ósmy cykl zegara 
	// taktuj¹cego uC (16MHz), czyli co 0,5us
	TCCR1B = (1<<CS11);
	
    //   G£ÓWNA PÊTLA PROGRAMU
	for(t=0;;t++) 
	{  		
        p_c = 0;
        p_d = 0;
 
        // Start impulsu - wszystkie wyjœcia 
        // w stan wysoki    
 		PORTC |= 0x3f;
		PORTD |= 0xfc;   
        
        // Czas wykonania pêtli 241*9,5us 2,3ms
		for(n=0; n<241; n++)
		{   
			TCNT1 = 0; // Zeruje Timer1 
			SFIOR = 1; // Resetuje preskaler   	
  	
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
            
            // Koniec impulsu     
            PORTD &= p_dd;
			PORTC &= p_cc;

            // Czeka, jeœli zawartoœæ tajmera1 
            // jest mniejsza ni¿ 19,  czyli 9,5us od 
            // momentu zerowania tajmera
			while(TCNT1<19 ); // 0,5 * 19 = 9,5us
		}
        
		TCNT1 = 0; 	  // Zeruje Timer1
		SFIOR = 1;    // Resetuje preskaler
	   
	    // Pêtla wykonuje siê dopóki zawartoœæ tajmera1
	    // jest mniejsza ni¿  35100, czyli 
	    // ok 18ms od momentu zerowania tajmera
		while(TCNT1<35100)  //  0,5*3510 = 1,7550 ms
		{
		// Tutaj, w pêtli, reszta programu,
		// powinien siê wykonaæ w czasie <18ms.
		
			if(t==1)
			{
		      servos[0] = 0x5e;
              servos[1] = 0xb8;
              servos[2] = 0x5e;
              servos[3] = 0xb8;
		      servos[4] = 0x5e;
              servos[5] = 0xb8;
              servos[6] = 0x5e;
              servos[7] = 0xb8;           
		      servos[8] = 0x5e;
              servos[9] = 0xb8;
              servos[10] = 0x5e;
              servos[11] = 0xb8;               
			}
			else if(t==50)
			{
              servos[0] = 0x8B;
              servos[1] = 0x8B;
              servos[2] = 0x8B;
              servos[3] = 0x8B;
              servos[4] = 0x8B;
              servos[5] = 0x8B;
              servos[6] = 0x8B;
              servos[7] = 0x8B;              
              servos[8] = 0x8B;
              servos[9] = 0x8B;
              servos[10] = 0x8B;
              servos[11] = 0x8B;                          					
			}
			else if(t==100)
			{
               servos[0] = 0xB8;
               servos[1] = 0x5e;
               servos[2] = 0xB8;
               servos[3] = 0x5e;
               servos[4] = 0xB8;
               servos[5] = 0x5e;
               servos[6] = 0xB8;
               servos[7] = 0x5e;               
               servos[8] = 0xB8;
               servos[9] = 0x5e;
               servos[10] = 0xB8;
               servos[11] = 0x5e;              
            }
			else if(t==150)
			{
               t=0;
            }          
		}		
	}
	
	return 0;
}

