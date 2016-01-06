/* 16 bits color */

#ifndef COLOR16BITS_H
#define COLOR16BITS_H



//--------------------------------------------------
// RGB 16 Bpp
// RGB 565
// R4R3R2R1 R0G5G4G3 G2G1G0B4 B3B2B1B0
//--------------------------------------------------
#define COLOR_16BITS_BLACK    		0x0000 // noir
#define COLOR_16BITS_BLUE     		0x001F // Bleu
#define COLOR_16BITS_RED      		0xF800 // Rouge 
#define COLOR_16BITS_GREEN    		0x07E0 // Vert
#define COLOR_16BITS_CYAN     		0x07FF // Cyan 
#define COLOR_16BITS_MAGENTA  		0xF81F // Magenta
#define COLOR_16BITS_YELLOW   		0xFFE0 // Jaune
#define COLOR_16BITS_WHITE    		0xFFFF // Blanc
#define COLOR_16BITS_NAVY           0x0010
#define COLOR_16BITS_DARKBLUE       0x0011
#define COLOR_16BITS_DARKGREEN      0x0320
#define COLOR_16BITS_DARKCYAN       0x0451
#define COLOR_16BITS_TURQUOISE      0x471A
#define COLOR_16BITS_INDIGO         0x4810
#define COLOR_16BITS_DARKRED        0x8000
#define COLOR_16BITS_OLIVE          0x8400
#define COLOR_16BITS_GRAY           0x8410
#define COLOR_16BITS_SKYBLUE        0x867D
#define COLOR_16BITS_BLUEVIOLET     0x895C
#define COLOR_16BITS_LIGHTGREEN     0x9772
#define COLOR_16BITS_DARKVIOLET     0x901A
#define COLOR_16BITS_YELLOWGREEN    0x9E66
#define COLOR_16BITS_BROWN          0xA145
#define COLOR_16BITS_DARKGRAY       0xAD55
#define COLOR_16BITS_SIENNA         0xA285
#define COLOR_16BITS_LIGHTBLUE      0xAEDC
#define COLOR_16BITS_GREENYELLOW    0xAFE5
#define COLOR_16BITS_SILVER         0xC618
#define COLOR_16BITS_LIGHTGREY      0xD69A
#define COLOR_16BITS_LIGHTCYAN      0xE7FF
#define COLOR_16BITS_VIOLET         0xEC1D
#define COLOR_16BITS_AZUR           0xF7FF
#define COLOR_16BITS_BEIGE          0xF7BB
#define COLOR_16BITS_TOMATO         0xFB08
#define COLOR_16BITS_GOLD           0xFEA0
#define COLOR_16BITS_ORANGE         0xFD20
#define COLOR_16BITS_SNOW           0xFFDF

/* 2 x 8 bits*/
#define COLOR_2x8BITS_BLACK    		 0x00,0x00 // noir
#define COLOR_2x8BITS_BLUE     		 0x00,0x1F // Bleu
#define COLOR_2x8BITS_RED      		 0xF8,0x00 // Rouge 
#define COLOR_2x8BITS_GREEN    		 0x07,0xE0 // Vert
#define COLOR_2x8BITS_CYAN     		 0x07,0xFF // Cyan 
#define COLOR_2x8BITS_MAGENTA  		 0xF8,0x1F // Magenta
#define COLOR_2x8BITS_YELLOW   		 0xFF,0xE0 // Jaune
#define COLOR_2x8BITS_WHITE    		 0xFF,0xFF // Blanc
#define COLOR_2x8BITS_NAVY           0x00,0x10
#define COLOR_2x8BITS_DARKBLUE       0x00,0x11
#define COLOR_2x8BITS_DARKGREEN      0x03,0x20
#define COLOR_2x8BITS_DARKCYAN       0x04,0x51
#define COLOR_2x8BITS_TURQUOISE      0x47,0x1A
#define COLOR_2x8BITS_INDIGO         0x48,0x10
#define COLOR_2x8BITS_DARKRED        0x80,0x00
#define COLOR_2x8BITS_OLIVE          0x84,0x00
#define COLOR_2x8BITS_GRAY           0x84,0x10
#define COLOR_2x8BITS_SKYBLUE        0x86,0x7D
#define COLOR_2x8BITS_BLUEVIOLET     0x89,0x5C
#define COLOR_2x8BITS_LIGHTGREEN     0x97,0x72
#define COLOR_2x8BITS_DARKVIOLET     0x90,0x1A
#define COLOR_2x8BITS_YELLOWGREEN    0x9E,0x66
#define COLOR_2x8BITS_BROWN          0xA1,0x45
#define COLOR_2x8BITS_DARKGRAY       0xAD,0x55
#define COLOR_2x8BITS_SIENNA         0xA2,0x85
#define COLOR_2x8BITS_LIGHTBLUE      0xAE,0xDC
#define COLOR_2x8BITS_GREENYELLOW    0xAF,0xE5
#define COLOR_2x8BITS_SILVER         0xC6,0x18
#define COLOR_2x8BITS_LIGHTGREY      0xD6,0x9A
#define COLOR_2x8BITS_LIGHTCYAN      0xE7,0xFF
#define COLOR_2x8BITS_VIOLET         0xEC,0x1D
#define COLOR_2x8BITS_AZUR           0xF7,0xFF
#define COLOR_2x8BITS_BEIGE          0xF7,0xBB
#define COLOR_2x8BITS_TOMATO         0xFB,0x08
#define COLOR_2x8BITS_GOLD           0xFE,0xA0
#define COLOR_2x8BITS_ORANGE         0xFD,0x20
#define COLOR_2x8BITS_SNOW           0xFF,0xDF

// R4R3R2R1 R0G5G4G3 G2G1G0B4 B3B2B1B0
typedef union {
	 unsigned int Word; //16bits
	 struct {
    union {
    	unsigned char Byte;
      	  struct {
    		unsigned char GREEN3     :1;      /* GREEN Bit 3 */
    		unsigned char GREEN4     :1;      /* GREEN Bit 4 */
    		unsigned char GREEN5     :1;      /* GREEN Bit 5 */
    		unsigned char RED0       :1;      /* RED Bit 0 */
    		unsigned char RED1       :1;      /* RED Bit 1 */
    		unsigned char RED2       :1;      /* RED Bit 2 */
    		unsigned char RED3       :1;      /* RED Bit 3 */
    		unsigned char RED4       :1;      /* RED Bit 4 */
      	  	  	  }Bits;
      	  } MSB_COLOR; 
#define COLOR2 _COLOR16BITS.Overlap.MSB_COLOR.Byte
#define RED4 _COLOR16BITS.Overlap.MSB_COLOR.Bits.RED4
#define RED3 _COLOR16BITS.Overlap.MSB_COLOR.Bits.RED3
#define RED2 _COLOR16BITS.Overlap.MSB_COLOR.Bits.RED2
#define RED1 _COLOR16BITS.Overlap.MSB_COLOR.Bits.RED1
#define RED0 _COLOR16BITS.Overlap.MSB_COLOR.Bits.RED0
#define GREEN5 _COLOR16BITS.Overlap.MSB_COLOR.Bits.GREEN5
#define GREEN4 _COLOR16BITS.Overlap.MSB_COLOR.Bits.GREEN4
#define GREEN3 _COLOR16BITS.Overlap.MSB_COLOR.Bits.GREEN3
   	   union {
      		unsigned char Byte; //8bits
   	     struct {
      			unsigned char BLUE0      :1;         /* BLUE Bit 0 */
      			unsigned char BLUE1      :1;         /* BLUE Bit 1 */
      			unsigned char BLUE2      :1;         /* BLUE Bit 2 */
      			unsigned char BLUE3      :1;         /* BLUE Bit 3 */
      			unsigned char BLUE4      :1;         /* BLUE Bit 4 */
      			unsigned char GREEN0     :1;         /* GREEN Bit 0 */
      			unsigned char GREEN1     :1;         /* GREEN Bit 1 */
      			unsigned char GREEN2     :1;         /* GREEN Bit 2 */
   	      } Bits;
   	    } LSB_COLOR;
#define COLOR1 _COLOR16BITS.Overlap.LSB_COLOR.Byte
#define GREEN2 _COLOR16BITS.Overlap.LSB_COLOR.Bits.GREEN2  
#define GREEN1 _COLOR16BITS.Overlap.LSB_COLOR.Bits.GREEN1
#define GREEN0 _COLOR16BITS.Overlap.LSB_COLOR.Bits.GREEN0
#define BLUE4 _COLOR16BITS.Overlap.LSB_COLOR.Bits.BLUE4
#define BLUE3 _COLOR16BITS.Overlap.LSB_COLOR.Bits.BLUE3
#define BLUE2 _COLOR16BITS.Overlap.LSB_COLOR.Bits.BLUE2
#define BLUE1 _COLOR16BITS.Overlap.LSB_COLOR.Bits.BLUE1
#define BLUE0 _COLOR16BITS.Overlap.LSB_COLOR.Bits.BLUE0
	  }Overlap;
	 struct {
		  unsigned char BLUE :5;
		  unsigned char GREEN :6;
		  unsigned char RED :5;
  	  	  	 } MergedBits;
#define RED _COLOR16BITS.MergedBits.RED
#define GREEN _COLOR16BITS.MergedBits.GREEN
#define BLUE _COLOR16BITS.MergedBits.BLUE
  	  	  	 
}RGB16;
volatile RGB16 _COLOR16BITS;

#endif // #define COLOR16BITS_
