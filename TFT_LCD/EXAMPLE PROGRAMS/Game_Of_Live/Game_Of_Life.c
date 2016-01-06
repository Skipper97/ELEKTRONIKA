/*
Game of life, by Huub Smeitink, using a modified library from Dryden

Just connect the screen to the pic as configured in the code, use a 8mhz crystal

For more information: HMSProjects.com
*/


#include "lcddriver.c"

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


// the game array (life cells are 1, dead cells 0)
char game[29][24] =
{
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0},
{0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};


unsigned int game_x,game_y,alive_neighbours,x_relative,y_relative,i,j,q;


void main() {

  ADCON0 = 0x0F;           // turn off analog inputs
  ADCON1 = 0x0F;           // turn off analog inputs
  CMCON  |= 7;                            // Disable comparators

    TRISA = 0;
    TRISB = 0;
    TRISD = 0;
    TRISE = 0;
    latA = 0x00;
    latB = 0x00;
    latD = 0x00;
    latE = 0x00;

   TFT_Init();
   TFT_Fill(black);

   TFT_Text("Conway's",50,20,16,black,white);
   TFT_Text("Game of Life",20,40,16,black,white);

   TFT_Text("H. Smeitink",25,80,16,black,white);
   TFT_Text("HMSProjects.com",60,205,8,black,white);

   delay_ms(8000);

   // bar at the bottom of the screen
   TFT_Fill(d_gray);
   TFT_Box(0,290,239,319,d_gray);
   TFT_Text("HMSProjects.com",0,295,16,white,d_gray);
   TFT_H_Line(0,239,290,l_gray);
   
      // initialize field
      for(game_x = 0; game_x < 24; game_x++)
      {
        for(game_y = 0; game_y < 29; game_y++)
        {
           if(game[game_y][game_x] == 1)
           {
             TFT_Box(game_x * 10,game_y * 10,game_x * 10 + 9,game_y * 10 + 9,yellow);
           }
           TFT_Box(game_x * 10,0,game_x * 10 + 1,289,l_gray);
           TFT_Box(0,game_y * 10,239,game_y * 10 + 1,l_gray);
        }
      }
    // opdate the array acording to the rules of game of life
    while(1)
    {
      for(game_x = 0; game_x < 24; game_x++)
      {
        for(game_y = 0; game_y < 29; game_y++)
        {
           alive_neighbours = 0;
           
           // do nothing if at a side of the screen (put your better code for this here if you want to)
           if(game_x == 0)
           {

           }
           else if(game_x == 23)
           {
           }
           else if(game_y == 0)
           {
           }
           else if(game_y == 28)
           {
           }
           
           // update the cells
           else
           {
             if(game[game_y + 1][game_x] == 1 || game[game_y + 1][game_x] == 3)
             {
                 alive_neighbours++;
             }
             if(game[game_y + 1][game_x + 1] == 1 || game[game_y + 1][game_x + 1] == 3)
             {
                 alive_neighbours++;
             }
             if(game[game_y + 1][game_x - 1] == 1 || game[game_y + 1][game_x - 1] == 3)
             {
                 alive_neighbours++;
             }
             if(game[game_y][game_x + 1] == 1 || game[game_y][game_x + 1] == 3)
             {
                 alive_neighbours++;
             }
             if(game[game_y][game_x - 1] == 1 || game[game_y][game_x - 1] == 3)
             {
                 alive_neighbours++;
             }
             if(game[game_y - 1][game_x] == 1 || game[game_y - 1][game_x] == 3)
             {
                 alive_neighbours++;
             }
             if(game[game_y - 1][game_x + 1] == 1 || game[game_y - 1][game_x + 1] == 3)
             {
                 alive_neighbours++;
             }
             if(game[game_y - 1][game_x - 1] == 1 || game[game_y - 1][game_x - 1] == 3)
             {
                 alive_neighbours++;
             }
           }
           if(alive_neighbours == 3 && game[game_y][game_x] == 0)
           {
             game[game_y][game_x] = 2;
           }
           else if((alive_neighbours > 3 || alive_neighbours < 2) && game[game_y][game_x] == 1)
           {
             game[game_y][game_x] = 3;
           }
        }
      }
      for(game_x = 0; game_x < 24; game_x++)
      {
        for(game_y = 0; game_y < 29; game_y++)
        {
          if(game[game_y][game_x] == 2)      // new living cells are 2
          {
             game[game_y][game_x] = 1;
             TFT_Box(game_x * 10 + 2,game_y * 10 + 2,game_x * 10 + 9,game_y * 10 + 9,cyan);
          }
          else if(game[game_y][game_x] == 3)     // dead cells that lived before are 3 after they just died
          {
             game[game_y][game_x] = 0;
             TFT_Box(game_x * 10 + 2,game_y * 10 + 2,game_x * 10 + 9,game_y * 10 + 9,black);
          }
          else if(game[game_y][game_x] == 1)      // life cells are 1
          {
            TFT_Box(game_x * 10 + 2,game_y * 10 + 2,game_x * 10 + 9,game_y * 10 + 9,yellow);
          }
          else // other cells must are dead for a while (these are 0) (uncomment if you dont want the Black cells to stay Black)
          {
            //TFT_Box(game_x * 10 + 2,game_y * 10 + 2,game_x * 10 + 9,game_y * 10 + 9,d_gray);
          }
        }
      }
    }


}