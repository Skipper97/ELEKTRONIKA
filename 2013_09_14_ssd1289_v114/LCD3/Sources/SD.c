/******************************************************************************
*                                                  
*  (c) copyright Freescale Semiconductor 2008
*  ALL RIGHTS RESERVED
*
*  File Name:   SD.c
*                                                                          
*  Description: SD Card using SPI Driver 
*                                            
*  Version:     1.5                                                         
*                                                                                                                                                         
*  Author:      Sahuc Guillaume
*                                                                                       
* UPDATED HISTORY:
*
* REV   AUTHOR        		DESCRIPTION OF CHANGE
* ---   ------        		--------------------- 
* 1.0   Jose Ruiz     		Initial version
* 1.1	Sahuc Guillaume 	-Use with HX8347a touchpanel LCD TFT 3.2" include sdcard
* 							without SD card detection.( with CW v 10.1 and tested with CW6.3 )
* 							- Use buffer in fat.c for more RAM !! :o)p
* 1.2	Sahuc Guillaume		- add function SD_ReadBmpFile
* 1.3   Sahuc Guillaume 	- change SD_ReadBmpFile, add color to SD_ReadFile
* 1.4   Sahuc Guillaume     - add function SD_Read16BitsBmpFile 
* 1.5   Sahuc Guillaume 	- use console
******************************************************************************/                                                                        
/* Freescale  is  not  obligated  to  provide  any  support, upgrades or new */
/* releases  of  the Software. Freescale may make changes to the Software at */
/* any time, without any obligation to notify or provide updated versions of */
/* the  Software  to you. Freescale expressly disclaims any warranty for the */
/* Software.  The  Software is provided as is, without warranty of any kind, */
/* either  express  or  implied,  including, without limitation, the implied */
/* warranties  of  merchantability,  fitness  for  a  particular purpose, or */
/* non-infringement.  You  assume  the entire risk arising out of the use or */
/* performance of the Software, or any systems you design using the software */
/* (if  any).  Nothing  may  be construed as a warranty or representation by */
/* Freescale  that  the  Software  or  any derivative work developed with or */
/* incorporating  the  Software  will  be  free  from  infringement  of  the */
/* intellectual property rights of third parties. In no event will Freescale */
/* be  liable,  whether in contract, tort, or otherwise, for any incidental, */
/* special,  indirect, consequential or punitive damages, including, but not */
/* limited  to,  damages  for  any loss of use, loss of time, inconvenience, */
/* commercial loss, or lost profits, savings, or revenues to the full extent */
/* such  may be disclaimed by law. The Software is not fault tolerant and is */
/* not  designed,  manufactured  or  intended by Freescale for incorporation */
/* into  products intended for use or resale in on-line control equipment in */
/* hazardous, dangerous to life or potentially life-threatening environments */
/* requiring  fail-safe  performance,  such  as  in the operation of nuclear */
/* facilities,  aircraft  navigation  or  communication systems, air traffic */
/* control,  direct  life  support machines or weapons systems, in which the */
/* failure  of  products  could  lead  directly to death, personal injury or */
/* severe  physical  or  environmental  damage  (High  Risk Activities). You */
/* specifically  represent and warrant that you will not use the Software or */
/* any  derivative  work of the Software for High Risk Activities.           */
/* Freescale  and the Freescale logos are registered trademarks of Freescale */
/* Semiconductor Inc.                                                        */ 
/*****************************************************************************/
#pragma MESSAGE DISABLE C1420 /*desactive les messages d'erreur */
#pragma MESSAGE DISABLE C1801 /*desactive les messages d'erreur */
/* Includes */
#include "SD.h"
#include "board.h"
#include "color16bits.h"
#include "color24bits.h"
#include "Fat.h"
#include "SSD1289.h"
#include "derivative.h"
#include "libbmp.h"
#include "string.h"
#include "FslTypes.h"
#include "main.h"
#include "console.h"

T32_8 gu8SD_Argument;

/******************** USED VARIABLES *************************/

UINT8  u8sd_status;       /* Variable to indicate SD status */
UINT8  u8sd_command;      /* Variable to indicate commands for SD */
UINT16 u16buffer_index;   /* Variable to indicate position of buffer */
UINT16 u16file_counter;   /* Variable to indicate remaining bytes of a file */
UINT8 u8sd_extension;      /* Variable to indicate SD extension's file */
const UINT8* SdCardDetect = "SD card Detect...";
const UINT8* FileFound = "FILE.TXT was found.";
const UINT8* FileCreate = "FILE.TXT was created.";

UINT8 SD_Init(void) 
{
  //  _SD_PRESENT=_IN;
    
    /* Check for SD */
//    if(SD_PRESENT)
//        return(NO_SD_CARD);
    
    /* Initialize SPI Module */
	SPI_Init(); // from SPI.c

    
    /* Start SD card Init */
    SPI_SS=ENABLE;
    SD_CLKDelay(SD_WAIT_CYCLES);            // Send 80 clocks 
    SPI_SS=DISABLE;
  
    gu8SD_Argument.lword=0;
    SD_CLKDelay(8);  
    
    /* IDLE Command */
    
    SPI_SS=ENABLE;
    if(SD_SendCommand(SD_CMD0|0x40,SD_IDLE,0x95))
    {
        SPI_SS=DISABLE;
        return(INIT_FAILS);      
    }
    SPI_SS=DISABLE;
    
    (void)ReadSPIByte();  // Dummy SPI cycle
    
    /*  Initialize SD Command */
    SPI_SS=ENABLE;
    while(SD_SendCommand(SD_CMD1|0x40,SD_OK,0xff));
    SPI_SS=DISABLE;
    
    (void)ReadSPIByte();  // Dummy SPI cycle

    /*  Block Length */
    SPI_SS=ENABLE;
      
    gu8SD_Argument.lword=SD_BLOCK_SIZE;
    if(SD_SendCommand(SD_CMD16|0x40,SD_OK,0xff))
    {
        SPI_SS=DISABLE;
        return(INIT_FAILS);      
    }
    
    SPI_SS=DISABLE;
    
    HighSpeedSPI();

    WriteSPIByte(0x00);
    WriteSPIByte(0x00);
    return(OK);
}

/*****************************************************************************/
UINT8 SD_Write_Block(UINT32 u16SD_Block,UINT8 *pu8DataPointer) 
{
    UINT16 u16Counter;
    SPI_SS=ENABLE;

    gu8SD_Argument.lword=u16SD_Block;
    gu8SD_Argument.lword=gu8SD_Argument.lword<< SD_BLOCK_SHIFT;

    if(SD_SendCommand(SD_CMD24|0x40,SD_OK,0xff))
    {
        SPI_SS=DISABLE;
        return(WRITE_COMMAND_FAILS);      
    }
    
    WriteSPIByte(0xFE);
    for(u16Counter=0;u16Counter<BLOCK_SIZE;u16Counter++)
    {
    	   WriteSPIByte(*pu8DataPointer++);
    }
     
    WriteSPIByte(0xFF);    // checksum Bytes not needed
    WriteSPIByte(0xFF);

   for(u16Counter=0;u16Counter<BLOCK_SIZE;u16Counter++);

    if((ReadSPIByte() & 0x0F) != 0x05)
    {
        SPI_SS=DISABLE;
        return(WRITE_DATA_FAILS);      
    }
    while(SPI_Receive_byte()==0x00){}  	// Dummy SPI cycle

    SPI_SS=DISABLE;
    return(OK);
}

/*****************************************************************************/
UINT8 SD_Read_Block(UINT32 u16SD_Block,UINT8 *pu8DataPointer) 
{
    UINT8 u8Temp=0;
    UINT16 u16Counter;
    SPI_SS=ENABLE;
    gu8SD_Argument.lword=u16SD_Block;
    gu8SD_Argument.lword=gu8SD_Argument.lword<< SD_BLOCK_SHIFT;

    if(SD_SendCommand(SD_CMD17|0x40,SD_OK,0xff))
    {
        SPI_SS=DISABLE;
        return(READ_COMMAND_FAILS);      
    }
    while(u8Temp!=0xFE)
    {
    	u8Temp=SPI_Receive_byte();
    }
    for(u16Counter=BLOCK_SIZE;u16Counter!=0;u16Counter--)
    {
    	 *pu8DataPointer++=SPI_Receive_byte();
    }
    (void)ReadSPIByte();  // Dummy SPI cycle ( checksum )
    (void)ReadSPIByte();  
    SPI_SS=DISABLE;
    (void)ReadSPIByte();  // Dummy SPI cycle
    return(OK);
}

/*****************************************************************************/
UINT8 SD_SendCommand(UINT8 u8SDCommand,UINT8 u8SDResponse,UINT8 CRC) 
{
    UINT8 u8Counter;
    volatile UINT8 u8Temp=0;

    /* Send Start byte */
    WriteSPIByte(u8SDCommand);

    /* Send Argument */
    for(u8Counter=0;u8Counter<4;u8Counter++) 
        WriteSPIByte(gu8SD_Argument.bytes[u8Counter]);
  
    /* Send CRC */
    WriteSPIByte(CRC);
  
    /* Response RHandler */
    u8Counter=SD_WAIT_CYCLES;
    do
    {
        u8Temp=ReadSPIByte();
        u8Counter--;
    }while((u8Temp != u8SDResponse) && u8Counter > 0);
    
    if(u8Counter)   return(OK);
    else            return(COMMAND_FAILS);
}

/*****************************************************************************/
void SD_CLKDelay(UINT8 u8Frames) 
{
    while(u8Frames--)
    {
    	  WriteSPIByte(0xFF);
    }
}


void SDcheck(void)
{
  /* Check the status of the SD card and sends messages */ 
  if (u8sd_status!=NO_SD_CARD && u8sd_status !=INIT_FAILS)
  {
	  ConsolePrint(&console,SdCardDetect);
    //If the SD is ok, reads the Master Block of the memory
    FAT_Read_Master_Block();
    u8sd_status = FAT_FileOpen("FILE.TXT",MODIFY);
      
    if (u8sd_status == FILE_NOT_FOUND) 
    {
      //If the file does not exist, it is created
      u8sd_status = FAT_FileOpen("FILE.TXT",CREATE); 
      ConsolePrintf(&console,"\n%s",FileCreate );
    } 
    else
    { 
      //If the exists, just a message is sent
    	 ConsolePrintf(&console,"\n%s",FileFound);
    }
    FAT_FileClose(); 
    //This part sets the initial values of these variables
        u16buffer_index = 0;
        u8sd_command = SD_INACTIVE;     
  } else
  { 
	  SD_SysHalt();
  }
}


/*----------------------------------------------------------------------------------*/
void SD_ReadFile(UINT8 *file)
{
  u8sd_command = SD_FILE_READING;
  //Indicates that the file will be read
  u8sd_status = FAT_FileOpen(file,READ);
  if (u8sd_status == FILE_FOUND) 
  {  
		  //Sends an message to show the content of the file
	  	  ConsolePrint(&console,"The content of file is:\n");  
		      //Return of funtion FAT_FileRead indicates how many bytes were read
		      //To read a complete file, this function should be invoked until it returns zero
		      u16file_counter = FAT_FileRead(ag8FATReadBuffer,&RHandler); 
		      ConsolePrint(&console,ag8FATReadBuffer);
		      while(u16file_counter){ // tant qu'il y a des données on les affiches.
		    	 u16file_counter = FAT_FileRead(ag8FATReadBuffer,&RHandler);
		    	 while(SW1){ } 
		    	 	 ConsoleClear(&console);
		    	 	 ConsolePrint(&console,ag8FATReadBuffer);
		      }
		      ConsolePrint(&console,"<EOF>END OF FILE");
		    //Sets these variables to inactive states
		    u8sd_command = SD_INACTIVE;
		    u16buffer_index = 0;
  } 
  else
  {       
    //If the file was not found, the system is halted
	  SD_SysHalt();
  }     
}


extern LCD_Position Lcd_XY;
extern ReadRHandler RHandler;
extern Color_RGB _Color;


void SD_Read24BitsBmpFile(UINT16 _x,UINT16 _y,UINT8 *file,t_bmp *bmp)
{
	unsigned char flagColor;
	int x;
	int count = 0;
	long int WriteCount = 0 ;
  u8sd_command = SD_FILE_READING;
  //Indicates that the file will be read
  u8sd_status = FAT_FileOpen(file,READ);
  if (u8sd_status == FILE_FOUND) 
  {    
		      //Return of funtion FAT_FileRead indicates how many bytes were read
		      //To read a complete file, this function should be invoked until it returns zero
			  u16file_counter = FAT_FileRead(ag8FATReadBuffer,&RHandler); 
	          //Get BMP header information :
			  memcpy2(&(bmp->header.first_header.sType),&ag8FATReadBuffer[0],sizeof(short));
			  memcpy2(&(bmp->header.first_header.iSize),&ag8FATReadBuffer[2],sizeof(int));
			  memcpy2(&(bmp->header.first_header.sReserved1),&ag8FATReadBuffer[6],sizeof(short));
			  memcpy2(&(bmp->header.first_header.sReserved2),&ag8FATReadBuffer[8],sizeof(short));
			  memcpy2(&(bmp->header.first_header.iOffBits),&ag8FATReadBuffer[10],sizeof(int));
			  memcpy2(&(bmp->header.second_header.iSize),&ag8FATReadBuffer[14],sizeof(int));
			  memcpy2(&(bmp->header.second_header.iWidth),&ag8FATReadBuffer[18],sizeof(int));
			  memcpy2(&(bmp->header.second_header.iHeight),&ag8FATReadBuffer[22],sizeof(int));
			  memcpy2(&(bmp->header.second_header.sPlanes),&ag8FATReadBuffer[26],sizeof(short));
			  memcpy2(&(bmp->header.second_header.sBitCount),&ag8FATReadBuffer[28],sizeof(short));
			  memcpy2(&(bmp->header.second_header.iCompression),&ag8FATReadBuffer[30],sizeof(int));
			  memcpy2(&(bmp->header.second_header.iSizeImage),&ag8FATReadBuffer[34],sizeof(int));
			  memcpy2(&(bmp->header.second_header.iXpelsPerMeter),&ag8FATReadBuffer[38],sizeof(int));
			  memcpy2(&(bmp->header.second_header.iYpelsPerMeter),&ag8FATReadBuffer[42],sizeof(int));
			  memcpy2(&(bmp->header.second_header.iClrUsed),&ag8FATReadBuffer[46],sizeof(int));
			  memcpy2(&(bmp->header.second_header.iClrImportant),&ag8FATReadBuffer[50],sizeof(int));
			
			  if (bmp->header.first_header.sType != 0x424d)
			  {
				  u8sd_status = BAD_FILE_FORMAT;
				  SD_SysHalt();
			  }
			  if (bmp->header.second_header.iCompression != 0)
			  {
				  u8sd_status = UNSUPPORTED_COMPRESSION;
				  SD_SysHalt();
			  }
			
			  	//byteswap est présent dans fat.h	
			  bmp->width = (ByteSwap(bmp->header.second_header.iWidth)) - 1 ; // max 239
			  bmp->height = (ByteSwap(bmp->header.second_header.iHeight)) - 1;  // max 319
			  bmp->width_useless =  (bmp->width+1) % 4; // (bmp->width+1) % 4  //(4 - (((bmp->width+1) * 3) % 4)) & 3
			  bmp->size = (long int)(bmp->width+1) * (bmp->height+1);
			//  SDD1289_STANDBY_ON();
			  DisableInterrupts;   // Disable interrupts	
			  Lcd_W_com_data_4x8(0x00,0x11,0x60,0x10); // registre qui permet de modifier l'orientation de l'écran // ID=01  AM=0
			 Lcd_address_set(0,0,bmp->width,bmp->height);
			 Lcd_Position_Set(_x,bmp->height-_y); //on commence tout en bas à gauche <!>
			 flagColor = Blue;//pour le prochain buffer on commence avec le bleu
			 // bloc de données 
			 //while(SW1){}; //for debug
			 u16buffer_index=0x36;// avant c'est l'entête du fichier *.bmp
			 while(u16buffer_index != u16file_counter) /* tant que la fin du buffer n'est pas atteint*/
					{
				 _Color.blue = (ag8FATReadBuffer[u16buffer_index]);
				 u16buffer_index++;
				 if (u16buffer_index != u16file_counter)
				 		        {
				 		       _Color.green = (ag8FATReadBuffer[u16buffer_index]);
				 		        u16buffer_index++;
				 		        if (u16buffer_index != u16file_counter)
				 		        		{
				 		        			_Color.red = (ag8FATReadBuffer[u16buffer_index]);
				 		        			u16buffer_index++;
				 		        			Lcd_Write_DATA_16(RGB24ToRGB565(_Color.red, _Color.green, _Color.blue));
				 		        			WriteCount++;
				 		        			  count++;
				 		        		}
				 		        		else 
				 		        		{
				 		        			flagColor = Red;//pour le prochain buffer on commence avec le rouge
				 		        			break;
				 		        		}
				 		        		
				 		        }
		        	else 
		        	{
		        		flagColor = Green;//pour le prochain buffer on commence avec le vert
		        		break;
		        	}
				}
			 
			 while ((u16file_counter) && (WriteCount < bmp->size)) // then while buffer have data get data
			      {  
			        //Return of funtion FAT_FileRead indicates how many bytes were read
			        //To read a complete file, this function should be invoked until it returns zero
				 
				 u16file_counter = FAT_FileRead(ag8FATReadBuffer,&RHandler);
			        switch(flagColor) // a t'on envoyé un pixel complet ? sinon on le complete.
			        {
			        case(Blue):
			        	u16buffer_index=0;
			        	 while(u16buffer_index != u16file_counter)
			        		{
			        		 _Color.blue = (ag8FATReadBuffer[u16buffer_index]);
			        		 u16buffer_index++;
			        		 if (u16buffer_index != u16file_counter)
			        		 		{
			        		 		_Color.green = (ag8FATReadBuffer[u16buffer_index]);
			        		 		u16buffer_index++;
			        		 		if (u16buffer_index != u16file_counter)
			        		 				{
			        		 					_Color.red = (ag8FATReadBuffer[u16buffer_index]);
			        		 					u16buffer_index++;
			        		 					Lcd_Write_DATA_16(RGB24ToRGB565(_Color.red, _Color.green, _Color.blue));
			        		 					WriteCount++;
			        		 					  count++;
			        		 					 if (count == bmp->width+1)
			        		 					 		{
			        		 					 			for (x=0;x<bmp->width_useless;x++)
			        		 					 			{
			        		 					 				u16buffer_index++; 
			        		 					 			}
			        		 					 		count = 0;
			        		 					 		}
			        		 				}
			        		 				else 
			        		 				{
			        		 					flagColor = Red;//pour le prochain buffer on commence avec le rouge
			        		 					break;
			        		 				}
			        		 		}
			        			else 
			        			{
			        				flagColor = Green;//pour le prochain buffer on commence avec le vert
			        				break;
			        			}
			        		}
			        break;
			        case(Green):
			        	u16buffer_index=0;
			        flagColor = Blue;//pour le prochain buffer on commence avec le bleu
			        	_Color.green = (ag8FATReadBuffer[u16buffer_index]);
			        	u16buffer_index++;
			        	_Color.red = (ag8FATReadBuffer[u16buffer_index]);
			        	u16buffer_index++;
			        	Lcd_Write_DATA_16(RGB24ToRGB565(_Color.red, _Color.green, _Color.blue));
			        	WriteCount++;
			        	count++;
			        		if (count == bmp->width+1)
			        			{
			        			    for (x=0;x<bmp->width_useless;x++)
			        				    	{
			        			    		 u16buffer_index++; 
			        				    	}
			        			    count = 0;
			        			}
			        	   	 while(u16buffer_index != u16file_counter)
			        		{
			        		 _Color.blue = (ag8FATReadBuffer[u16buffer_index]);
			        		 u16buffer_index++;
			        		 if (u16buffer_index != u16file_counter)
			        		 		{
			        		 		_Color.green = (ag8FATReadBuffer[u16buffer_index]);
			        		 		u16buffer_index++;
			        		 		if (u16buffer_index != u16file_counter)
			        		 				{
			        		 					_Color.red = (ag8FATReadBuffer[u16buffer_index]);
			        		 					u16buffer_index++;
			        		 					Lcd_Write_DATA_16(RGB24ToRGB565(_Color.red, _Color.green, _Color.blue));
			        		 					WriteCount++;
			        		 					  count++;
			        		 					 if (count == bmp->width+1)
			        		 					 		{
			        		 					 			for (x=0;x<bmp->width_useless;x++)
			        		 					 			{
			        		 					 				u16buffer_index++; 
			        		 					 			}
			        		 					 		count = 0;
			        		 					 		}
			        		 				}
			        		 				else 
			        		 				{
			        		 					flagColor = Red;//pour le prochain buffer on commence avec le rouge
			        		 					break;
			        		 				}
			        		 				
			        		 		}
			        			else 
			        			{
			        				flagColor = Green;//pour le prochain buffer on commence avec le vert
			        				break;
			        			}
			        		}
			        break;
			        case(Red):
			        	u16buffer_index=0;
			        flagColor = Blue;//pour le prochain buffer on commence avec le bleu
			        _Color.red = (ag8FATReadBuffer[u16buffer_index]);
			        u16buffer_index++;
			        Lcd_Write_DATA_16(RGB24ToRGB565(_Color.red, _Color.green, _Color.blue));
			        WriteCount++;
			        count++;
			        	if (count == bmp->width+1)
			        		{
			        		    for (x=0;x<bmp->width_useless;x++)
			        			    	{
			        		    		 u16buffer_index++; 
			        			    	}
			        		    count = 0;
			        		}
			        	  while(u16buffer_index != u16file_counter)
			        		{
			        		 _Color.blue = (ag8FATReadBuffer[u16buffer_index]);
			        		 u16buffer_index++;
			        		 if (u16buffer_index != u16file_counter)
			        		 		{
			        		 		_Color.green = (ag8FATReadBuffer[u16buffer_index]);
			        		 		u16buffer_index++;
			        		 		if (u16buffer_index != u16file_counter)
			        		 				{
			        		 					_Color.red = (ag8FATReadBuffer[u16buffer_index]);
			        		 					u16buffer_index++;
			        		 					Lcd_Write_DATA_16(RGB24ToRGB565(_Color.red, _Color.green, _Color.blue));
			        		 					WriteCount++;
			        		 					  count++;
			        		 					 if (count == bmp->width+1)
			        		 					 		{
			        		 					 			for (x=0;x<bmp->width_useless;x++)
			        		 					 			{
			        		 					 				u16buffer_index++; 
			        		 					 			}
			        		 					 		count = 0;
			        		 					 		}
			        		 				}
			        		 				else 
			        		 				{
			        		 					flagColor = Red;//pour le prochain buffer on commence avec le rouge
			        		 					break;
			        		 				}
			        		 		}
			        			else 
			        			{
			        				flagColor = Green;//pour le prochain buffer on commence avec le vert
			        				break;
			        			}
			        		}
			        break;
			        default:
			        	 SD_SysHalt();
			        break;
			       }
			      }
			    //Sets these variables to inactive states
		    u8sd_command = SD_INACTIVE;
		    u16buffer_index = 0;
			Lcd_W_com_data_4x8(0x00,0x11,0x60,0xB0); // ID=11  AM=0
		    EnableInterrupts;
  } 
  else
  {       
    //If the file was not found, the system is halted
	  SD_SysHalt();
  } 
}

void SD_WriteFile(UINT8* buffer) //1er appel à la fonction = preparation à l'écriture, il faut un 2eme appel à la fonction pour écrire dans le fichier.
{
  if (u8sd_command == SD_INACTIVE)
  {
    //If is the first time that fonction is called, indicates that the file will be written
    u8sd_command = SD_FILE_WRITING; 
   // Lcd_print(5,170,"Text will be saved on FILE.TXT",0,0xffff);     
    u16buffer_index = 0;
  }
  else if ( (u8sd_command == SD_FILE_WRITING) || (u16buffer_index >= 512) )
  {    
    //If is the second time that button is pressed or function is called, or the buffer reaches its maximum value
    //the buffer will be written on the file
    u8sd_status = FAT_FileOpen("FILE.TXT",MODIFY); 
    if (u8sd_status == FILE_FOUND) 
    {
     //u16buffer_index = 0, si l'index reste à 0 pas d'écriture.
  	 while(buffer[u16buffer_index] && u16buffer_index <= 512){
  		u16buffer_index++; // incrémentation de l'index du buffer tant qu'on a des données
   	 }
      //Writtes the u8buffer to the file
      FAT_FileWrite(buffer, u16buffer_index);
      LED = ~LED;
      FAT_FileClose(); 
      //Sets these variables to inactive states 
      u16buffer_index = 0;
      u8sd_command = SD_INACTIVE;        
    }
    else
    { 
      //If the file was not found, the system is halted
    	 SD_SysHalt();
    }
  }    
}

void SD_Read16BitsBmpFile(UINT16 _x,UINT16 _y,UINT8 *file,t_bmp *bmp)
{ 
  UINT16 x;
  UINT8 temp;
  UINT8 flag;
  UINT16 count = 0;
  UINT32 WriteCount = 0 ;
  u8sd_command = SD_FILE_READING;
  //Indicates that the file will be read
  u8sd_status = FAT_FileOpen(file,READ);
  if (u8sd_status == FILE_FOUND) 
    {    
      //Return of funtion FAT_FileRead indicates how many bytes were read
      //To read a complete file, this function should be invoked until it returns zero
      u16file_counter = FAT_FileRead(ag8FATReadBuffer,&RHandler); 
      //Get BMP header information :
      memcpy2(&(bmp->header.first_header.sType),&ag8FATReadBuffer[0],sizeof(short));
      memcpy2(&(bmp->header.first_header.iSize),&ag8FATReadBuffer[2],sizeof(int));
      memcpy2(&(bmp->header.first_header.sReserved1),&ag8FATReadBuffer[6],sizeof(short));
      memcpy2(&(bmp->header.first_header.sReserved2),&ag8FATReadBuffer[8],sizeof(short));
      memcpy2(&(bmp->header.first_header.iOffBits),&ag8FATReadBuffer[10],sizeof(int));
      memcpy2(&(bmp->header.second_header.iSize),&ag8FATReadBuffer[14],sizeof(int));
      memcpy2(&(bmp->header.second_header.iWidth),&ag8FATReadBuffer[18],sizeof(int));
      memcpy2(&(bmp->header.second_header.iHeight),&ag8FATReadBuffer[22],sizeof(int));
      memcpy2(&(bmp->header.second_header.sPlanes),&ag8FATReadBuffer[26],sizeof(short));
      memcpy2(&(bmp->header.second_header.sBitCount),&ag8FATReadBuffer[28],sizeof(short));
      memcpy2(&(bmp->header.second_header.iCompression),&ag8FATReadBuffer[30],sizeof(int));
      memcpy2(&(bmp->header.second_header.iSizeImage),&ag8FATReadBuffer[34],sizeof(int));
      memcpy2(&(bmp->header.second_header.iXpelsPerMeter),&ag8FATReadBuffer[38],sizeof(int));
      memcpy2(&(bmp->header.second_header.iYpelsPerMeter),&ag8FATReadBuffer[42],sizeof(int));
      memcpy2(&(bmp->header.second_header.iClrUsed),&ag8FATReadBuffer[46],sizeof(int));
      memcpy2(&(bmp->header.second_header.iClrImportant),&ag8FATReadBuffer[50],sizeof(int));
			
      if (bmp->header.first_header.sType != 0x424d)
	{
	  u8sd_status = BAD_FILE_FORMAT;
	  SD_SysHalt();
	}
		
      //byteswap est présent dans fat.h	
      bmp->width = (ByteSwap(bmp->header.second_header.iWidth)) - 1 ; // max 239
      bmp->height = (ByteSwap(bmp->header.second_header.iHeight)) - 1;  // max 319
      bmp->width_useless =  (bmp->width+1) % 4; // (bmp->width+1) % 4  //(4 - (((bmp->width+1) * 3) % 4)) & 3
      bmp->size = (UINT32)(bmp->width+1) * (bmp->height+1);
      DisableInterrupts;   // Disable interrupts	
      Lcd_W_com_data_4x8(0x00,0x11,0x60,0x10); // registre qui permet de modifier l'orientation de l'écran // ID=01  AM=0
      Lcd_address_set(0,0,bmp->width,bmp->height);
      Lcd_Position_Set(_x,bmp->height-_y); //on commence tout en bas à gauche <!>
      // bloc de données 
      u16buffer_index=0x8A;// avant c'est l'entête du fichier *.bmp
      while(u16buffer_index != u16file_counter) /* tant que la fin du buffer n'est pas atteint*/
	{
	  Lcd_Write_DATA_2x8(ag8FATReadBuffer[u16buffer_index+1],ag8FATReadBuffer[u16buffer_index]);
	  u16buffer_index += 2 ;
	  WriteCount++;
	  count++;     	 
	}
      /*---------------------*/
      if (u16buffer_index != u16file_counter)
	{
	  temp = ag8FATReadBuffer[u16buffer_index];
	  flag = 1;
	}else 
	{
	  flag = 0;
	}
      /*---------------------*/
      while ((u16file_counter) && (WriteCount < bmp->size)) // then while buffer have data get data
	{  
	  //Return of funtion FAT_FileRead indicates how many bytes were read
	  //To read a complete file, this function should be invoked until it returns zero
	  u16file_counter = FAT_FileRead(ag8FATReadBuffer,&RHandler);
	  u16buffer_index=0;
	  while(u16buffer_index != u16file_counter)
	    {
	      if ( flag == 1)
		{
		  Lcd_Write_DATA_2x8(ag8FATReadBuffer[u16buffer_index],temp);
		  u16buffer_index += 1 ;
		  WriteCount++;
		  count++;
		  flag = 0;
		}else 
		{
		  Lcd_Write_DATA_2x8(ag8FATReadBuffer[u16buffer_index+1],ag8FATReadBuffer[u16buffer_index]);
		  u16buffer_index += 2 ; 
		  WriteCount++;
		  count++;
		  if (count == bmp->width+1)
		    {
		      for (x=0;x<bmp->width_useless;x++)
		      	  {
		    	  	  u16buffer_index++; 
		      	  }
		      count = 0;
		    }	
		}	 
	    }
	}
      //Sets these variables to inactive states
      u8sd_command = SD_INACTIVE;
      u16buffer_index = 0;
      Lcd_W_com_data_4x8(0x00,0x11,0x60,0xB0); // ID=11  AM=0
      EnableInterrupts; 
    } 
  else
    {       
      //If the file was not found, the system is halted
      SD_SysHalt();
    } 
}

/*----------------------------------------------------------------------------------*/

const UINT8* Error[] = {"ERROR = ","NO SD CARD!","INIT ERROR!","FILE NOT FOUND!",
		"BAD FILE FORMAT!","INCOMPLETE BUFFER READ!","UNSUPPORTED COMPRESSION!",
		"NO MORE FREE CLUSTER!","GAME OVER - RETRY ? :oD"};

void SD_SysHalt()
{
  /* This funtion sends an error message and blocks the system */
  Lcd_W_com_data_4x8(0x00,0x11,0x60,0xB0); // ID=11  AM=0
  ConsoleClear(&consoleError);
  ConsoleGoToY(&consoleError,100);
  ConsolePrint(&consoleError,"SDCard was removed! or Fatal Error\n");  
  ConsoleGoToY(&consoleError,130);
  ConsolePrint(&consoleError,"System halted, press RESET button\n"); 
  ConsoleGoToY(&consoleError,160);
  switch(u8sd_status)
  {
  case NO_SD_CARD:
	  ConsolePrintf(&consoleError,"%s %s",Error[0],Error[1]);
	  break;
  case INIT_FAILS:
	  ConsolePrintf(&consoleError,"%s %s",Error[0],Error[2]);
	  break;
  case FILE_NOT_FOUND:
	  ConsolePrintf(&consoleError,"%s %s",Error[0],Error[3]);
	  break;
  case BAD_FILE_FORMAT:
	  ConsolePrintf(&consoleError,"%s %s",Error[0],Error[4]);
	  break;
  case INCOMPLETE_BUFFER_READ:
	  ConsolePrintf(&consoleError,"%s %s",Error[0],Error[5]);
	 	  break;
  case UNSUPPORTED_COMPRESSION:
	  ConsolePrintf(&consoleError,"%s %s",Error[0],Error[6]);
	  break;
  case NO_MORE_FREE_CLUSTER:
	  ConsolePrintf(&consoleError,"%s %s",Error[0],Error[7]);
	 	  break;
  default:
	  ConsolePrintf(&consoleError,"%s %s",Error[0],Error[8]);
	break;
  }
  DisableInterrupts;   // Disable interrupts 
  for(;;); // boucle infinie
}



