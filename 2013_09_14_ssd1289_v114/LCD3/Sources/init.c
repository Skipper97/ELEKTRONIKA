/*
 * init.c
 *
 *      Author: Guillaume Sahuc
 
  This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "init.h"
#include "board.h"
#include "derivative.h"
#include "SSD1289.h"
/**********************************************************************************
Fonction d'initialisation/configuration de la puce. Elle peut-être modifiée selon l'application 
souhaitée.
**********************************************************************************/
void Init_Fbus(void){
	ICGC1 = 0x78; //f8
	ICGC2 = 0x30; // fbus = 4 Mhz = 0x01 // 0x30 = 40Mhz
	while(ICGS1_LOCK == 0 ){ }//attente maintien de l'horloge
	ICGS1 = 0x00; //read only for clear interrupt flag
	ICGS2 = 0x00;//read only should read DCOS
}


void Init_Port(void){
LCD_DATA_L    = 0x00; LCD_DATA_L_DIR   = SORTIE; /*LCD DATA BUS LOWER BYTE */ 
LCD_DATA_H   = 0x00; LCD_DATA_H_DIR   = SORTIE; /*LCD DATA BUS HIGHER BYTE*/  
 PTCD    = 0x00; PTCDD_PTCDD2 = 0; PTCDD_PTCDD6 = 0; /*pull up =>*/ PTCPE_PTCPE2 = ON; PTCPE_PTCPE6 = ON; 
 PTDD    = 0x00; PTDDD   = ENTREE; /*pull up =>*/ PTDPE_PTDPE0 = OFF; PTDPE_PTDPE2 = ON; PTDPE_PTDPE3 = ON;
 PTED    = 0x00; PTEDD   = SORTIE; 
 PTFD    = 0x00; PTFDD   = SORTIE; //led
 PTGD    = 0x00; PTGDD   = SORTIE; //SDCARD CS ET TOUCH CS
 LCD_BACKLIGHT = 1; PTCDD_PTCDD0 = 1; PTCDS_PTCDS0 = 1;  // backlight 
 LCD_RD = 1; LCD_WR = 1;  LCD_CS = 1; LCD_RS = 1; // LCD ( actif à l'état bas )
 TOUCH_CS = 1; SDCARD_CS = 1; // SPI CHIP SELECT TOUCHSCREEN & SDCARD 
 IRQSC = 0x13; // irq pin enabled
 PTCDD_PTCDD1 = 0; // TOUCH BUSY

}


//SCI init
void Init_SCI(void){
	  SCI1C2 = 0x00;                       /* Disable the SCI1 module */
	  (void)(SCI1S1 == 0);                 /* Dummy read of the SCI1S1 register to clear flags */
	  (void)(SCI1D == 0);                  /* Dummy read of the SCI1D register to clear flags */
	  SCI1S2 = 0x00;
	  SCI1BDH = 0x00;     //toujours en premier                                  
	  SCI1BDL = 0x0D;     //en second  baudrate 1A = 9600 , 0D = 19200                               
	  SCI1C1 = 0x00;                                      
	  SCI1C3 = 0x00;                                      
	  SCI1C2 = 0x00;                                     
	}

void Init_SCI2(void){
	  SCI2C2 = 0x00;                       /* Disable the SCI2 module */
	  (void)(SCI2S1 == 0);                 /* Dummy read of the SCI2S1 register to clear flags */
	  (void)(SCI2D == 0);                  /* Dummy read of the SCI2D register to clear flags */
	  SCI2S2 = 0x00;
	  SCI2BDH = 0x00;     //toujours en premier                                  
	  SCI2BDL = 0x08;     //en second  baudrate 1A = 9600 , 0D = 19200  ; 08 = 31250                             
	  SCI2C1 = 0x00;                                      
	  SCI2C3 = 0x00;                                      
	  SCI2C2 = 0x00;                                     
	}

void Init_SPI(void){
	SPI1C1 = 0x50; // no interrupt and master
	SPI1C2 = 0x00;
	SPI1BR = 0x01; 
}
void Init_ADC(void){
    ADC1CFG = 0x80;
    ADC1SC2 = 0x00;  
    APCTL2 = 0xF2;
}
//timer:
UINT16 TimerOverflow = 46875;

void Init_Timer(void){
	  TPM1SC = TIMER_STOP;  			   /* Stop and reset counter */
	  // Initial duty cycle 
	  (void)(TPM1SC == 0); 
	  // Timer1 period
      TPM1MOD = TimerOverflow;
	  /* ### Init_TPM init code */
	  (void)(TPM1C0SC == 0);    
	  TPM1C0V = TimerOverflow / 2;
	  TPM1C0SC = 0x28;                  
      // Starts Timer1 
      TPM1SC = TIMER_START;
}

/**********************************************************************************
                 initialisation du MicroControlleur 
**********************************************************************************/
void Init_MC08(void){
SOPT_COPE = 0x00; 		//Inhibe le WATCHDOG pour permettre l'initialisation à la mise sous tension. 
Init_Fbus();
Init_Port();    		//Initialise les PORTS.
Init_SCI();				//Initialise la liaison série SCI <> PORT COM PC
//Init_SCI2();
Init_SPI();
//Init_ADC();			//Initialise le convertisseur Analogique/Numérique
//Init_Timer();
Init_LCD();
}
