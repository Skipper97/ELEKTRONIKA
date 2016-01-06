/******************************************************************************
*                                                  
*  (c) copyright Freescale Semiconductor 2010
*  ALL RIGHTS RESERVED
*
*  File Name:   Fat.h
*                                                                          
*  Description: Fat16 lite driver 
*                                                                                     
*  Assembler:   Codewarrior for HC(S)08 V6.3
*                                            
*  Version:     1.5 (based on 1.2 from freescale site)                                                         
*                                                                                                                                                         
*  Author:      Jose Ruiz (SSE Americas)
*                                                                                       
*  Location:    Guadalajara,Mexico                                              
*                                                                                                                  
*                                                  
* UPDATED HISTORY:
*
* REV   YYYY.MM.DD  AUTHOR        	DESCRIPTION OF CHANGE
* ---   ----------  ------        	--------------------- 
* 1.0   2008.02.18  Jose Ruiz     	Initial version
* 1.1   2008.05.02  Jose Ruiz     	Initial version
* 1.2   2010.12.13  Santiago L      Corrected problem handling more of 16 files
*                                   Added Modify Function
* 1.3   Sahuc Guillaume 			Change definition
* 1.4   Sahuc Guillaume 			Add Fat32 MBR and LFN support
* 1.5   Sahuc Guillaume 			LFN support
* 1.6   Sahuc Guillaume				FileList
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

#ifndef __Fat__
#define __Fat__

/************************* HIL ****************************/
/**********************************************************/
/* Includes */
#include "FslTypes.h"
#include "SD.h"     // SD Card Driver
#include "FileList.h"

/* Storage HIL */
#define GetPhysicalBlock(A,B)       (void)SD_Read_Block(A,B);     
#define StorePhysicalBLock(A,B)     (void)SD_Write_Block(A,B);
/**********************************************************/
/**********************************************************/

/* Macros */
#define ByteSwap(A)     (A=(A<<8 & 0xff00)+(A>>8 & 0xff))
#define NibbleSwap(A)   (A=(A<<4 & 0xf0 )+(A>>4 & 0x0f))

/* definitions */
#define MASTER_BLOCK        0x00
#define RootEntrySize       32
#define EntriesPerBlock     16          //Block size / RootEntrySize 
#define RHandler_FAT_ENTRIES 8



/*-- Directory Defines --*/
#define FAT_DIRENT_REALLY_0E5            0x05
#define FAT_DIRENT_DIRECTORY_ALIAS       0x2e

#define FILE_AVAILABLE      0x00
#define FILE_USER           0xFF

#define FILE_Erased         0xE5
#define FILE_Clear          0x00

#define AT_READONLY         0x01
#define AT_HIDDEN           0x02
#define AT_SYSTEM           0x04
#define AT_VOLUME           0x08
#define AT_DIRECTORY        0x10
#define AT_ARCHIVE          0x20
#define AT_DEVICE           0x40
#define AT_LFN              (AT_READONLY | \
                                    AT_HIDDEN |    \
                                    AT_SYSTEM |    \
                                    AT_VOLUME) // 0x0F
//    caracteres interdit dans un nom de fichier = \/:*?"<>|
#define FILE_Index_Clear    0x0000

#define CLUSTER_EOF_16 0xFFFF
#define CLUSTER_EOF 0x0FFFFFFF
#define CLUSTER_FREE 0x0000
#define CLUSTER_FIRST 0x0002

#define FAT_CLUSTER_AVAILABLE            (UINT32)0x00000000
#define FAT_CLUSTER_RESERVED             (UINT32)0x0ffffff0
#define FAT_CLUSTER_BAD                  (UINT32)0x0ffffff7
#define FAT_CLUSTER_LAST                 (UINT32)0x0fffffff


enum
{
	_file = 0,
	_directory = 1,
	_longFileNameNOK = 2,
	_LongFileNameOK = 3,
	_error = 4
};

enum
{
	FAT16,
	FAT32
};


enum 
{
    READ,
    CREATE,
    MODIFY,
    DELETE,
    NEXT_ENTRY,
    WRITE_ENTRY,
    OVERWRITE
};

enum 
{
    FILE_FOUND,
    FILE_NOT_FOUND,
    FILE_CREATE_OK,
    NO_FILE_ENTRY_AVAILABLE,
    NO_FAT_ENTRY_AVAILABLE,
    ERROR_IDLE
};


/* typedef */
typedef struct _ReadHandler
{
    UINT16  FAT_Entry;
    UINT16  SectorOffset;
    UINT16  Dir_Entry;
    UINT32  File_Size;
}ReadRHandler;


typedef struct _WriteRHandler
{
    UINT8   FileName[8];
    UINT8   Extension[3];
    UINT16  Dir_Entry;
    UINT32  File_Size;
    UINT16  BaseFatEntry;
    UINT16  CurrentFatEntry;
    UINT16  SectorIndex;
    UINT16  ClusterIndex;
}WriteRHandler;

/* Root Directory Structure */
typedef struct _root_Entries
{
    UINT8   FileName[8];
    UINT8   Extension[3];
    UINT8   Attributes;
    UINT8   _Reserved; // for NT
    UINT8   MiliSeconds;
    UINT16  CreationTime;
    UINT16  CreationDate;
    UINT16  AccessDate;
    UINT16  indexEA;
    UINT16  ModificationTime;
    UINT16  ModificationDate;
    UINT16  FirstClusterNumber;
    UINT32  SizeofFile; 
}root_Entries;


// Long file name directory entry
typedef struct
{
  UINT8 Ordinal;  // Position within LFN
  UINT8 name1[10];  
  UINT8 Attributes;  // Should be equal to AT_LFN
  UINT8 Type;  // Always 0x00
  UINT8 Checksum;  // Checksum of short file name (alias)
  UINT8 Name2[12];
  UINT16 MustBeZero;
  UINT8 Name3[4];
}  DIR_ENT_LFN;

typedef DIR_ENT_LFN *DIRENT_LFN;

#define FAT_LAST_LONG_ENTRY             0x40 // Ordinal field
#define FAT_LONG_NAME_COMP              0x0  // Type field


#define MAX_LFN_CHARACTERS              260
#define MAX_LFN_DIRENTS                 20

typedef struct _Fat16
{
    	 UINT8   IdDisk;
    	 UINT8   ReservedFat16;
    	 UINT8   ExtendedSignature;
    	 UINT32  SerialNumber;
    	 UINT8   VolumeNumber[11];
    	 UINT8   FatName[8];
  //  	 UINT8   BootCode[448];
  //  	 UINT8   BootMarker[2];
}Fat16;

typedef	struct _Fat32
{
		 UINT32 SectorsPerFat32;
		 UINT16 DiskAttribut;
		 UINT8 HighVersionFileSys;
		 UINT8 LowVersionFileSys;
		 UINT32 RootFirstCluster;
		 UINT16 FileSysInfo;
		 UINT16 SectorBootNumber;
		 UINT8 reserved[12];
		 UINT8 IdDisk;
		 UINT8 ReservedFat32;
		 UINT8 SignatureFat32;
		 UINT32 DiskSerialNumber;
		 UINT8 DiskName[11];
		 UINT8 Sysfile[8];
	//	 UINT8 BootCode[420];
}Fat32;



typedef union MBR//FAT16 or FAT32 MBR
{
    Fat16 fat16;
    Fat32 fat32;
}Block;

/* Master Boot Record */
typedef struct _MasterBoot_Entries
{
    UINT8   JMP_BOOT[3];
    UINT8   OEMName[8]; // nom du fabricant
    UINT16  BytesPerSector; // octets par secteur 
    UINT8   SectorsPerCluster; // secteur par cluster
    UINT16  ReservedSectors; 
    UINT8   FatCopies;
    UINT16  RootDirectoryEntries;
    UINT16  SectorsLess32MB;
    UINT8   MediaDescriptor;
    UINT16  SectorsPerFat;
    UINT16  SectorsPerTrack; // secteur par piste
    UINT16  NumberOfHeads;
    UINT32  HiddenSectors;                     
    UINT32  SectorsInPartition;
    Block   block; // union fat16 + fat32
}MasterBoot_Entries;

extern WriteRHandler WHandler;
extern ReadRHandler RHandler;
extern UINT8 ag8FATReadBuffer[512];
extern UINT8 ag8FATWriteBuffer[512]; 
extern UINT8 FileName[MAX_LFN_CHARACTERS];
extern List FList;

/* Prototypes */
UINT32 LWordSwap(UINT32);
void FAT_FileClose(void);
void FAT_Read_Master_Block(void);
UINT8 FAT_FileOpen(UINT8*,UINT8);
void FAT_FileWrite(UINT8*,UINT32);
UINT16 FAT_FileRead(UINT8*,ReadRHandler*);
UINT16 FAT_Entry(UINT16,UINT16,UINT8);
UINT16 FAT_SearchAvailableFAT(UINT16);
UINT8 FAT_LS(void);
void FAT_LS2(void);
void ViewFatInfos(MasterBoot_Entries*);
void ViewGlobalFATVariables(void);
UINT8 FAT_Filename (root_Entries*);
#endif /* __Fat__ */
