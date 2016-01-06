#ifndef __SPI__
#define __SPI__

/* Includes */

#include "FslTypes.h"
#include "derivative.h"


/* definitions */

#define SPI_SS    SDCARD_CS      /* Slave Select 1 */                      
//#define _SPI_SS   PTADD_PTADD0    

//#define SPI_SS    PTCD_PTCD3      /* Slave Select 2 */
//#define _SPI_SS   PTCDD_PTCDD3    



#define ENABLE    0
#define DISABLE   1

/* Global Variables */

/* Prototypes */
void SPI_Init(void);
void SPI_Send_byte(UINT8 u8Data);
UINT8 SPI_Receive_byte(void);
void SPI_High_rate(void);
void SPI_Low_rate(void);


#endif /* __SPI__ */
