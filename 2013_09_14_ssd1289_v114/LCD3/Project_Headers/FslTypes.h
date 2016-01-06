#ifndef __Definitions__
#define __Definitions__


/* Typedefs */
typedef unsigned char   UINT8;  		/*unsigned 8 bit definition */
typedef unsigned short  UINT16; 		/*unsigned 16 bit definition*/
typedef unsigned long   UINT32; 		/*unsigned 32 bit definition*/
typedef signed char     INT8;   		/*signed 8 bit definition */
typedef short      	  	INT16;  		/*signed 16 bit definition*/
typedef long int      	INT32;  		/*signed 32 bit definition*/

/* Definitions */
#define   _OUT       1
#define   _IN        0
#define TRUE 1 
#define FALSE 0

enum ISR
{
    SCI_Flag,
    ADC_Flag
};

/* Macros */
#define FLAG_SET(BitNumber, Register)        (Register |=(1<<BitNumber))
#define FLAG_CLR(BitNumber, Register)        (Register &=~(1<<BitNumber))
#define FLAG_CHK(BitNumber, Register)        (Register & (1<<BitNumber))


#define    _BGND    asm(BGND)
#define    _NOP     asm(NOP)
#define    _WAIT    asm(WAIT)
#define    False    0x00
#define    True     0x01

/* Types definition */
typedef unsigned char byte;
typedef unsigned int word;
typedef unsigned long dword;
typedef unsigned long dlong[2];


#ifndef Byte
    typedef unsigned char       Byte;
  #endif
  #ifndef sByte
    typedef signed char         sByte;
  #endif
  #ifndef Word
    typedef unsigned int      Word; // était short
  #endif
  #ifndef sWord
    typedef signed int        sWord; // était short
  #endif
  #ifndef LWord
    typedef unsigned long       LWord;
  #endif
  #ifndef sLWord
    typedef signed long         sLWord;
  #endif
  #ifndef DLWord
    typedef unsigned long long  DLWord;
  #endif
  #ifndef sDLWord
    typedef signed long long    sDLWord;
  #endif


#endif /* __Definitions__ */
