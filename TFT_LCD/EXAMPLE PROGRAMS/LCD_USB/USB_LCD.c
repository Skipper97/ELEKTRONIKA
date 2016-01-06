/* 
Rewritten by Huub Smeitink, original version from Dryden

To use the this, connect the lcd like you specify in tft display connections, 
use a 8mhz crystal (or adjust the project settings accordingly)

This program waits on the data from the usb program i wrote, it expects the coordinates and dimensions first,
then the pixel data

You need to adjust the speed in the usb program so that the micrcontroller can keep up (adjes the delay),
6 seems to work fine for 8mhz, 2 for 20mhz

For more information and other projects: HMSProjects.com

*/



#include "lcddriver.c"
#include "USBdsc.c"

// TFT display connections
char TFT_DP_Lo at latB;
char TFT_DP_Hi at latD;
sbit TFT_WR at latA1_bit;
sbit TFT_RD at latA2_bit;
sbit TFT_CS at latA3_bit;
sbit TFT_RS at latA4_bit;
sbit TFT_RST at latA5_bit;

char TFT_DP_Lo_Direction at TRISB;
char TFT_DP_Hi_Direction at TRISD;
sbit TFT_WR_Direction at TRISA1_bit;
sbit TFT_RD_Direction at TRISA2_bit;
sbit TFT_CS_Direction at TRISA3_bit;
sbit TFT_RS_Direction at TRISA4_bit;
sbit TFT_RST_Direction at TRISA5_bit;
// End of TFT display connections

// USB stuf
unsigned char readbuff[64] absolute 0x500;   // Buffers should be in USB RAM, please consult datasheet
unsigned char writebuff[64] absolute 0x540;

void interrupt(){
   USB_Interrupt_Proc();                   // USB servicing is done inside the interrupt
}


// General variables
unsigned int i,j,x_pos,y_pos;
unsigned int height = 0;
unsigned int width = 0;
char cnt;


void main() {

  ADCON0 = 0x0F;           // turn off analog inputs
  ADCON1 = 0x0F;           // turn off analog inputs
  CMCON  |= 7;             // Disable comparators

  TRISA = 0;
  TRISB = 0;
  TRISD = 0;
  TRISE = 0;
  latA = 0x00;
  latB = 0x00;
  latD = 0x00;
  latE = 0x00;

  HID_Enable(&readbuff,&writebuff);       // Enable HID communication

  TFT_Init();
  TFT_Fill(red);


  while(1)
  {

    while(!HID_Read());
    width = (readbuff[1] << 8) | readbuff[0];
    height = (readbuff[3] << 8) | readbuff[2];
    x_pos = (readbuff[5] << 8) | readbuff[4];
    y_pos = (readbuff[7] << 8) | readbuff[6];


    HID_Write(&readbuff,64);



    i = 0;
    j = 0;
    cnt = 0;
    
    while(!HID_Read());
    for(i = 0; i < 64; i++)
    {
       writebuff[i] = 0;
    }
    
    TFT_CS  = 0;
    TFT_Set_Address(0,0,239,319);
    for(i = 0; i < height; i++)
    {
          for(j = 0; j < width; j++)
          {
              if(cnt >= 63)
              {
                cnt = 0;
                while(!HID_Read());
              }

              Write_Data( (readbuff[cnt] << 8) | readbuff[cnt + 1]);   // send the data for the pixel (color: 16bit, r5 g6 b5)

              cnt = cnt + 2;
          }
    }
    TFT_CS  = 1;
  }
}