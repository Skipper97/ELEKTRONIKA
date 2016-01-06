/******************************************************************************
*                                                  
*  (c) copyright Freescale Semiconductor 2011
*  ALL RIGHTS RESERVED
*
*  File Name:   Fat.c
*                                                                          
*  Description: Fat16 lite driver 
*                                                                                     
*  Version:     1.7( based on 1.3 from freescale site )                                                         
*                                                                                                                                                        
*  Author:      Jose Ruiz (SSE Americas)
*                                                                                       
*  Location:    Guadalajara,Mexico                                              
*                                                                                                                  
*                                                  
* UPDATED HISTORY:
  *
  * REV   AUTHOR        	DESCRIPTION OF CHANGE
  * ---   ------        	--------------------- 
  * 1.0   Jose Ruiz     	Initial version
  * 1.1   Jose Ruiz     	Initial version
  * 1.2   Santiago L    	Corrected problem handling more of 16 files
  *                       	Added Modify Function
  * 1.3   Carlos C.         Corrected problem handling large-size files
  * 1.4   Sahuc Guillaume   change function FAT_LS
  * 1.5   Sahuc Guillaume   Bugfix function FAT_LS and add color argument in function
  * 1.6   Sahuc Guillaume	LFN Support
  * 1.7	  Sahuc Guillaume   FileList
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
#pragma MESSAGE DISABLE C2705 /*desactive les messages d'erreur */
  /* Includes */
#include "Fat.h"
#include "board.h"
#include <ctype.h>
#include <string.h>
#include "main.h"
#include "fonts.h"
#include "console.h"

/* File Handlers */
WriteRHandler WHandler;
ReadRHandler RHandler;

/* File Buffers */
UINT8 ag8FATReadBuffer[512];
UINT8 ag8FATWriteBuffer[512];

/* Global Variables */
UINT32 u32FAT_SectorsPerFAT;
UINT32 u32FAT_Size;
UINT32 u32FAT_SectorsInPartition;
UINT16 u16FAT_Sector_Size;
UINT16 u16FAT_Cluster_Size;
UINT16 u16FAT_FAT_BASE;
UINT16 u16FAT_Root_BASE;
UINT16 u16FAT_Data_BASE;
UINT16 u16Main_Offset=0;
UINT16 u16FAT_Last_Cluster;


/***************************************************************************************/
UINT32 LWordSwap(UINT32 u32DataSwap)
{
  UINT32 u32Temp;
  u32Temp= (u32DataSwap & 0xFF000000) >> 24;
  u32Temp+=(u32DataSwap & 0xFF0000)   >> 8;
  u32Temp+=(u32DataSwap & 0xFF00)     << 8;
  u32Temp+=(u32DataSwap & 0xFF)       << 24;
  return(u32Temp);    
}

/***************************************************************************************/
void FAT_Read_Master_Block()
{
  MasterBoot_Entries* pMasterBoot;
    
  while(ag8FATReadBuffer[0]!= 0xEB && ag8FATReadBuffer[1]!=0x3C && ag8FATReadBuffer[2]!=0x90) 
    {
      GetPhysicalBlock(u16Main_Offset++,&ag8FATReadBuffer[0]);
    }
  u16Main_Offset--;
  pMasterBoot = (MasterBoot_Entries*)ag8FATReadBuffer;
  ByteSwap(pMasterBoot->NumberOfHeads);
  ByteSwap(pMasterBoot->BytesPerSector);
  ByteSwap(pMasterBoot->SectorsPerFat);
  if (!pMasterBoot->SectorsPerFat)
    {
      u32FAT_SectorsPerFAT = pMasterBoot->block.fat32.SectorsPerFat32;
    }
  else 
    {
      u32FAT_SectorsPerFAT = pMasterBoot->SectorsPerFat;
    }
  ByteSwap(pMasterBoot->SectorsPerTrack);
  ByteSwap(pMasterBoot->RootDirectoryEntries);
  ByteSwap(pMasterBoot->ReservedSectors);
  pMasterBoot->HiddenSectors = LWordSwap(pMasterBoot->HiddenSectors);
  pMasterBoot->SectorsInPartition = LWordSwap(pMasterBoot->SectorsInPartition);
  u32FAT_SectorsInPartition = pMasterBoot->SectorsInPartition;
  u16FAT_Cluster_Size = pMasterBoot->SectorsPerCluster;
  u16FAT_Sector_Size = pMasterBoot->BytesPerSector;
  u16FAT_FAT_BASE = u16Main_Offset + pMasterBoot->ReservedSectors;
  u16FAT_Root_BASE = (u32FAT_SectorsPerFAT * pMasterBoot->FatCopies)  + u16FAT_FAT_BASE;
  u16FAT_Data_BASE = (pMasterBoot->RootDirectoryEntries * sizeof(root_Entries) / u16FAT_Sector_Size ) + u16FAT_Root_BASE;
  u32FAT_Size = (u32FAT_SectorsInPartition - u16FAT_Data_BASE) * u16FAT_Sector_Size;
  u16FAT_Last_Cluster = (u32FAT_SectorsInPartition - u16FAT_Data_BASE) / pMasterBoot->SectorsPerCluster;
  //FOR DEBUG
  ViewFatInfos(pMasterBoot);
  while(SW1){ } // wait push switch1  // attente appuie sur bouton 1
}
/***************************************************************************************/

void ViewFatInfos(MasterBoot_Entries* data)
{
	ConsoleClear(&console);
  /*View FAT information */
  ConsolePrintf(&console,"OEM NAME = %s\n",data->OEMName);
  ConsolePrintf(&console,"BytesPerSector = %d\n",data->BytesPerSector);
  ConsolePrintf(&console,"SectorsPerCluster = %d\n",data->SectorsPerCluster);
  ConsolePrintf(&console,"ReservedSectors = %d\n",data->ReservedSectors);
  ConsolePrintf(&console,"FatCopies = %d\n",data->FatCopies);
  ConsolePrintf(&console,"RootDirectoryEntries = %d\n",data->RootDirectoryEntries);
  ConsolePrintf(&console,"SectorsLess32MB = %d\n",data->SectorsLess32MB);
  ConsolePrintf(&console,"MediaDescriptor = %d\n",data->MediaDescriptor);
  ConsolePrintf(&console,"SectorsPerFat = %d\n",data->SectorsPerFat);
  ConsolePrintf(&console,"SectorsPerTrack = %d\n",data->SectorsPerTrack);
  ConsolePrintf(&console,"NumberOfHeads = %d\n",data->NumberOfHeads);
  ConsolePrintf(&console,"HiddenSectors = %d\n",data->HiddenSectors);
  /*----------------*/
  ViewGlobalFATVariables();
     
}

void ViewGlobalFATVariables()
{
	ConsolePrintf(&console,"FAT_Cluster_Size = %d\n",u16FAT_Cluster_Size);
	ConsolePrintf(&console,"FAT_Sector_Size = %d\n",u16FAT_Sector_Size);
	ConsolePrintf(&console,"FAT_FAT_BASE = %d\n",u16FAT_FAT_BASE);
	ConsolePrintf(&console,"FAT_Root_BASE = %d\n",u16FAT_Root_BASE);
	ConsolePrintf(&console,"FAT_Data_BASE = %d\n",u16FAT_Data_BASE);
	/*----------------*/
	ConsolePrintf(&console,"SectorsInPartition = %ld\n",u32FAT_SectorsInPartition);
	ConsolePrintf(&console,"SectorsPerFAT = %ld\n",u32FAT_SectorsPerFAT);
	ConsolePrintf(&console,"FAT_Size = %ld\n",u32FAT_Size);
	/*----------------*/
	ConsoleGoToY(&console,300);
	ConsolePrint(&console,Touch1);
}

/****************************************************************************************/
UINT8 FAT_LS()
{
  UINT8 u8Counter;
  UINT16 u16Index;
  UINT16 u16Block;
  UINT16 u16BlockNum=u16FAT_Data_BASE-u16FAT_Root_BASE;
  UINT8  u8ErrorCode=ERROR_IDLE;
  root_Entries* sFileStructure;                                   
  ConsoleClear(&console);
  u16Block=0;
  while(u16Block < u16BlockNum && u8ErrorCode==ERROR_IDLE)
    {
      GetPhysicalBlock(u16FAT_Root_BASE+u16Block,ag8FATReadBuffer);
      sFileStructure = (root_Entries*)ag8FATReadBuffer;
      u16Index=0;
      while(u16Index<u16FAT_Sector_Size && u8ErrorCode==ERROR_IDLE)    
	{
	  while(sFileStructure->FileName[0]!=FILE_Clear)  
	    {
	      if((sFileStructure->FileName[0]!=FILE_Erased)  && isalpha(sFileStructure->FileName[0]) && ((sFileStructure->Attributes==AT_ARCHIVE) || (sFileStructure->Attributes==AT_DIRECTORY || sFileStructure->Attributes==AT_READONLY) ))
		{ 
		  ConsolePrint(&console,"\n");
		  for(u8Counter=0;u8Counter<8;u8Counter++)
		    {
		      if ((sFileStructure->FileName[u8Counter]!= 0x00) && (sFileStructure->FileName[u8Counter]!= 0x20))
		      	  {
		    	  	  ConsolePrintf(&console,"%c",sFileStructure->FileName[u8Counter]);
		      	  }
		    } 
		  if (sFileStructure->Attributes == AT_DIRECTORY)//si c'est un dossier 
		    {
		      ConsolePrint(&console,"  <DIR>");
		    }
		  else // sinon c'est un fichier => affiche l'extension
		    {
		      ConsolePrint(&console,".");
		      for(u8Counter=0;u8Counter<3;u8Counter++)
			{
			  if ((sFileStructure->FileName[u8Counter]!= 0x00) && (sFileStructure->FileName[u8Counter]!= 0x20))
			    {
				  ConsolePrintf(&console,"%c",sFileStructure->Extension[u8Counter]);
			    }	
			}
		      ConsoleGoToX(&console,150);
		      ConsolePrintf(&console,"%ld",LWordSwap(sFileStructure->SizeofFile));
		    }
		}
	      sFileStructure++; 
	      ConsoleGoToX(&console,0);
	    }
	  u16Index+=RootEntrySize;
	}
      u16Block++;
    } 
  if(u16BlockNum==u16Block)
    u8ErrorCode=NO_FILE_ENTRY_AVAILABLE;
  ConsoleGoToY(&console,300);
  ConsolePrint(&console,Touch1);	
  while(SW1){ } // attente appuie sur bouton 1
  return(u8ErrorCode);
}




/****************************************************************************************/
UINT8 FileName[MAX_LFN_CHARACTERS];
List FList;

void FAT_LS2()
{
  UINT16 u16Index;
  UINT16 u16Block=0;
  UINT16 u16BlockNum=u16FAT_Data_BASE-u16FAT_Root_BASE;
  UINT8  u8ErrorCode=ERROR_IDLE;
  root_Entries* sFileStructure;   
  UINT8	type;
  UINT8 LfnFlag = FALSE;
  InitFileList(&FList);

  while(u16Block < u16BlockNum && u8ErrorCode==ERROR_IDLE)
    {
      GetPhysicalBlock(u16FAT_Root_BASE+u16Block,ag8FATReadBuffer);
      sFileStructure = (root_Entries*)ag8FATReadBuffer;
      u16Index=0;
      while(u16Index<(u16FAT_Sector_Size/sizeof(root_Entries)) && u8ErrorCode==ERROR_IDLE)    
      	  	  {	  
  	  	  		type = FAT_Filename(sFileStructure);
  	  	  		switch(type)
  	  	  		{
  	  	  		case _file:
  	  	  			if(LfnFlag == TRUE)
  	  	  			{
  	  	  				AddDosFileName(&FList,FileName);
  	  	  				LfnFlag = FALSE;
  	  	  			}else
  	  	  			{
  	   	  	  		 InsertNewFileDosFileName(&FList,FileName);
  	   	  	  		 AddListType(&FList,_file);
  	  	  			}
  	  	  	  	  	    break;
  	  	  		case _directory:
 	   	  	  		 InsertNewFileDosFileName(&FList,FileName);
 	   	  	  		 AddListType(&FList,_directory);
  	  	  				break;
  	  	  		case _LongFileNameOK:
  	  	  			InsertNewFileLongFileName(&FList,FileName);
  	  	  	  	   	AddListType(&FList,_file);
  	  	  			LfnFlag = TRUE;
  	  	  				break;
  	  	  	case _longFileNameNOK:
  	  		        //continue
  	  	  	  	  	 break;
  	  	  		case _error:
  	  	  			//continue
  	  	  				break;
  	  	  		default:
  	  	  			ConsolePrint(&console,"unknow type\n");
  	  	  			break;
  	  	  		}
  	  	  		u16Index++;
  	  	  		sFileStructure++;
      	  	  }
      u16Block++;
    } 
  ConsoleClear(&console);
  ViewFileList(FList);
}


/***************************************************************************************/
void FAT_FileClose(void)
{
  root_Entries *sFileStructure;
  UINT16 *pu16FATPointer;
  UINT8 u8Counter;
  UINT32 u32Sector;
  UINT16 u16Offset;
    
  /* Directory Entry*/
  u32Sector=u16FAT_Root_BASE + WHandler.Dir_Entry/(u16FAT_Sector_Size>>5);
  u16Offset=WHandler.Dir_Entry%(u16FAT_Sector_Size>>5);
    
  GetPhysicalBlock(u32Sector,ag8FATReadBuffer);
  sFileStructure=(root_Entries*)ag8FATReadBuffer;
  sFileStructure+=u16Offset;

  // FileName
  for(u8Counter=0;u8Counter<8;u8Counter++)
    sFileStructure->FileName[u8Counter]=WHandler.FileName[u8Counter];

  // Entension
  for(u8Counter=0;u8Counter<3;u8Counter++)
    sFileStructure->Extension[u8Counter]=WHandler.Extension[u8Counter];


  // Attributes
  sFileStructure->Attributes=0x20;
  sFileStructure->_Reserved=0x18;
  sFileStructure->MiliSeconds=0xC6;
    
  // Date & Time Information
  sFileStructure->CreationTime=0x2008;
  sFileStructure->CreationDate=0x2136;
  sFileStructure->AccessDate=0x2136;
  sFileStructure->ModificationTime=0x2008;
  sFileStructure->ModificationDate=0x2136;
    
  // Fat entry and file Size
  sFileStructure->FirstClusterNumber=ByteSwap(WHandler.BaseFatEntry);
    
  sFileStructure->SizeofFile=LWordSwap(WHandler.File_Size); 

  StorePhysicalBLock(u32Sector,ag8FATReadBuffer)
    
    /* FAT Table */
    u32Sector=u16FAT_FAT_BASE + WHandler.CurrentFatEntry/(u16FAT_Sector_Size>>1);
  u16Offset=WHandler.CurrentFatEntry%(u16FAT_Sector_Size>>1);

  GetPhysicalBlock(u32Sector,ag8FATReadBuffer);
    
  pu16FATPointer=(UINT16*)ag8FATReadBuffer;
  pu16FATPointer+=u16Offset;
  *pu16FATPointer=0xFFFF;     // Write Final Cluster    

  StorePhysicalBLock(u32Sector,ag8FATReadBuffer)
    }

/***************************************************************************************/
UINT16 FAT_SearchAvailableCluster(UINT16 u16CurrentCluster)
{

  UINT16 *pu16DataPointer;
  UINT16 u16FatEntry=0;
  UINT16 u16Sector=0;
  UINT16 u16byteSector;
    
  u16Sector=u16FAT_FAT_BASE;
  while(u16Sector < (((u16FAT_Root_BASE-u16FAT_FAT_BASE)>>1)+u16Main_Offset))
    {        GetPhysicalBlock(u16Sector++,ag8FATReadBuffer);
      pu16DataPointer=(UINT16*)ag8FATReadBuffer;
      u16byteSector=0;
        
      while(u16byteSector<u16FAT_Sector_Size)
        {
	  if(*pu16DataPointer==CLUSTER_FREE)
	    if(u16FatEntry!=u16CurrentCluster)
	      return(u16FatEntry);
	  pu16DataPointer++;
	  u16FatEntry++;
	  u16byteSector++;
        }
    }
  return(0);  // Return 0 if no more FAT positions available
}

/***************************************************************************************/
UINT16 FAT_Entry(UINT16 u16FatEntry,UINT16 u16FatValue, UINT8 u8Function)
{
  UINT16 *pu16DataPointer;
  UINT16 u16Block;
  UINT16 NextCluster;
  UINT8 u8Offset;
    
  u16Block = u16FAT_FAT_BASE + ((u16FatEntry<<1) / u16FAT_Sector_Size);
  u8Offset = (UINT8)(u16FatEntry % (u16FAT_Sector_Size >>1));

  GetPhysicalBlock(u16Block,ag8FATReadBuffer);
  pu16DataPointer=(UINT16*)ag8FATReadBuffer;
  pu16DataPointer+=u8Offset;

  if(u8Function==NEXT_ENTRY)
    {      
      NextCluster = ByteSwap(*pu16DataPointer);
      if(NextCluster >= 0xFFF7)
    	{
	  NextCluster = CLUSTER_EOF_16;
    	}
      return(NextCluster);
    }
       
    
  if(u8Function==WRITE_ENTRY)
    {
      *pu16DataPointer=ByteSwap(u16FatValue);
      StorePhysicalBLock(u16Block,ag8FATReadBuffer);
      return(0x00);
    }
                
}
/***************************************************************************************/
void FAT_FileWrite(UINT8* pu8DataPointer,UINT32 u32Size)
{  
  UINT32 u32SectorToWrite;
  UINT8 *pu8ArrayPointer;
  UINT16 u16TempFat;
  UINT8  u8ChangeSector=1;

  while(u32Size)
    {
      if(u8ChangeSector)
        {
	  u32SectorToWrite= u16FAT_Data_BASE + WHandler.ClusterIndex + (WHandler.CurrentFatEntry-2)*u16FAT_Cluster_Size;
	  GetPhysicalBlock(u32SectorToWrite,ag8FATWriteBuffer); 
	  pu8ArrayPointer=ag8FATWriteBuffer+WHandler.SectorIndex;
	  u8ChangeSector=0;
        }
        
      while(WHandler.SectorIndex<u16FAT_Sector_Size  &&  u32Size)
        {
	  u32Size--;  
	  WHandler.SectorIndex++;
	  WHandler.File_Size++;
	  *pu8ArrayPointer++=*pu8DataPointer++;    
        }
        
      StorePhysicalBLock(u32SectorToWrite,ag8FATWriteBuffer);     // Write Buffer to Sector
    
      /* Check Sector Size */
      if(WHandler.SectorIndex == u16FAT_Sector_Size)
        {
	  WHandler.SectorIndex=0;
	  WHandler.ClusterIndex++;    
	  u8ChangeSector=1;
        }
    
      /* Check Cluster Size */
      if(WHandler.ClusterIndex == u16FAT_Cluster_Size)
        {
	  WHandler.ClusterIndex=0;
	  u16TempFat=FAT_SearchAvailableCluster(WHandler.CurrentFatEntry);
	  if(!u16TempFat)// no more fat available
            {
	      u8sd_status = NO_MORE_FREE_CLUSTER;
	      SD_SysHalt();
            }
	  (void)FAT_Entry(WHandler.CurrentFatEntry,u16TempFat,WRITE_ENTRY);
	  WHandler.CurrentFatEntry=u16TempFat;
	  u8ChangeSector=1;
        }
    }
}

/***************************************************************************************/
UINT16 FAT_FileRead(UINT8 *pu8UserBuffer, ReadRHandler* RHandler)
{
  UINT32 u32SectorToRead; 
  UINT16 u16BufferSize;
  static UINT8 u8ChangeCluster = FALSE;
 
  if(RHandler->File_Size==0)
    return(0);
  
  if (u8ChangeCluster == TRUE)
    {
      RHandler->SectorOffset=0;
      RHandler->FAT_Entry = FAT_Entry(RHandler->FAT_Entry,0,NEXT_ENTRY); // Get Next FAT Entry
      u8ChangeCluster = FALSE;
    }
    
  u32SectorToRead= u16FAT_Data_BASE + ((RHandler->FAT_Entry-2)*u16FAT_Cluster_Size) + RHandler->SectorOffset;
  GetPhysicalBlock(u32SectorToRead,pu8UserBuffer);

  if(RHandler->File_Size > u16FAT_Sector_Size) //if file size > 512
    {
      RHandler->File_Size -= u16FAT_Sector_Size;
      u16BufferSize=512;  // return 512
    }
  else
    {
      u16BufferSize = RHandler->File_Size; // return file_size always < 512
      RHandler->File_Size = 0;
    }
    
  if(RHandler->SectorOffset < (u16FAT_Cluster_Size)-1) 
    RHandler->SectorOffset++;        
  else // sectorOffset = u16FAT_Cluster_Size - 1
    {
      u8ChangeCluster = TRUE;
    }
  return(u16BufferSize);   // return file_size always < or = 512 
}


/***************************************************************************************/

void FAT_FileNameOrganizer(UINT8 *pu8FileName,UINT8 *pu8Destiny)
{
  UINT8 u8Counter=0;    
    
  while(u8Counter<12)
    {
      if(*pu8FileName != '.')
	*pu8Destiny++=*pu8FileName++;
      else
        {
	  if(u8Counter<8)
	    *pu8Destiny++=0x20;
	  else
	    pu8FileName++;    
        }
      u8Counter++;
    }
}

/***************************************************************************************/
UINT8 FAT_FileOpen(UINT8 *pu8FileName,UINT8 u8Function)
{
    
  UINT16 u16Temporal;
  UINT8  u8FileName[11];
  UINT8  u8Counter=0;
  UINT8  u8Flag=False;
  UINT16 u16Index;
  UINT16 u16Block;
  UINT16 u16BlockNum=u16FAT_Data_BASE-u16FAT_Root_BASE;
  UINT8  u8ErrorCode=ERROR_IDLE;
  UINT8  *pu8Pointer;
  UINT16 *pu16FATPointer;
  UINT32 u32Sector;
  UINT16 u16Offset;
  root_Entries *sFileStructure;                                   
    
  FAT_FileNameOrganizer(pu8FileName,&u8FileName[0]);
    
  u16Block=0;
    
  while(u16Block < u16BlockNum && u8ErrorCode==ERROR_IDLE)
    {
    
      GetPhysicalBlock(u16FAT_Root_BASE+u16Block,ag8FATReadBuffer);
      sFileStructure = (root_Entries*)ag8FATReadBuffer;

      u16Index=0;
      while(u16Index<u16FAT_Sector_Size && u8ErrorCode==ERROR_IDLE)    
        {
	  /* If Read or Modify Function */
	  if(u8Function==READ || u8Function==MODIFY|| u8Function==DELETE || u8Function==OVERWRITE)
            {
	      if(sFileStructure->FileName[0]==FILE_Clear) 
		u8ErrorCode=FILE_NOT_FOUND;
        
	      if(sFileStructure->FileName[0] == u8FileName[0])
                {
		  u8Flag=True;
		  u8Counter=0;
		  while(u8Flag==True && u8Counter < 10)
                    {
		      u8Counter++;
		      if(sFileStructure->FileName[u8Counter] != u8FileName[u8Counter])
			u8Flag=False;    
                    }
		  if(u8Flag==True)
                    {
		      /* If Read Function */
		      if(u8Function==READ)
                        {
			  RHandler.Dir_Entry=(u16Block*EntriesPerBlock)+((u16Index)/RootEntrySize);
			  RHandler.File_Size=LWordSwap(sFileStructure->SizeofFile);
			  RHandler.FAT_Entry=ByteSwap(sFileStructure->FirstClusterNumber);
			  RHandler.SectorOffset=0;
			  u8ErrorCode=FILE_FOUND;
                        } 
		      /*If Delete Function //Leandro Martinez*/     
		      else if(u8Function==DELETE)
                        {
			  WHandler.FileName[0] = FILE_Erased;
			  if(WHandler.BaseFatEntry != 0)
                            {
			      u16Temporal=WHandler.BaseFatEntry;
			      do
                                {
				  WHandler.CurrentFatEntry=WHandler.BaseFatEntry;
				  WHandler.BaseFatEntry=FAT_Entry(WHandler.CurrentFatEntry,0,NEXT_ENTRY);
				  u32Sector=u16FAT_FAT_BASE + (WHandler.CurrentFatEntry/(u16FAT_Sector_Size>>1));
				  u16Offset=WHandler.CurrentFatEntry%(u16FAT_Sector_Size>>1);

				  GetPhysicalBlock(u32Sector,ag8FATReadBuffer);
    
				  pu16FATPointer=(UINT16*)ag8FATReadBuffer;
				  pu16FATPointer+=u16Offset;
				  *pu16FATPointer=CLUSTER_FREE;     // clear FAT entry    

				  StorePhysicalBLock(u32Sector,ag8FATReadBuffer)                                
                                
				    }while(WHandler.BaseFatEntry!=CLUSTER_EOF_16);
			      WHandler.BaseFatEntry=u16Temporal;
                                
			      u32Sector=u16FAT_FAT_BASE + (WHandler.CurrentFatEntry/(u16FAT_Sector_Size>>1));
			      u16Offset=WHandler.CurrentFatEntry%(u16FAT_Sector_Size>>1);

			      GetPhysicalBlock(u32Sector,ag8FATReadBuffer);
    
			      pu16FATPointer=(UINT16*)ag8FATReadBuffer;
			      pu16FATPointer+=u16Offset;
			      *pu16FATPointer=CLUSTER_FREE;     // clear FAT entry    

			      StorePhysicalBLock(u32Sector,ag8FATReadBuffer)                                               
				}
                        }       
		      /* If Overwrite Function */
		      else if (u8Function==OVERWRITE)
                        {
			  pu8Pointer=WHandler.FileName;
			  for(u8Counter=0;u8Counter<11;u8Counter++)
			    *pu8Pointer++=u8FileName[u8Counter];
			  WHandler.Dir_Entry=(u16Block*EntriesPerBlock)+((u16Index)/RootEntrySize);
			  WHandler.File_Size=LWordSwap(sFileStructure->SizeofFile);
			  WHandler.BaseFatEntry=ByteSwap(sFileStructure->FirstClusterNumber);
                            
			  if(WHandler.BaseFatEntry != 0)
                            {
			      u16Temporal=WHandler.BaseFatEntry;
			      do
                                {
				  WHandler.CurrentFatEntry=WHandler.BaseFatEntry;
				  WHandler.BaseFatEntry=FAT_Entry(WHandler.CurrentFatEntry,0,NEXT_ENTRY);
                                }while(WHandler.BaseFatEntry!=CLUSTER_EOF_16);
			      WHandler.BaseFatEntry=u16Temporal;
                            } 
			  else
                            {
			      WHandler.BaseFatEntry=FAT_SearchAvailableCluster(0);
			      WHandler.CurrentFatEntry=WHandler.BaseFatEntry;
                            }
			  /*****************/
			  /* Double Check */
			  /*****************/
                            
			  u8Counter=0;
			  u8ErrorCode=u16FAT_Cluster_Size;
			  while(u8ErrorCode != 0x01)
                            {
			      u8Counter++;
			      u8ErrorCode=u8ErrorCode>>1;
                            }
                            
			  u16Temporal=(UINT16)WHandler.File_Size % (u16FAT_Sector_Size<<u8Counter);
			  WHandler.ClusterIndex= u16Temporal/u16FAT_Sector_Size;
			  WHandler.SectorIndex=  0;//u16Temporal%u16FAT_Sector_Size;
			  u8ErrorCode=FILE_FOUND;
                        }
                        
		      /* If Modify Function */
		      else
                        {
			  pu8Pointer=WHandler.FileName;
			  for(u8Counter=0;u8Counter<11;u8Counter++)
			    *pu8Pointer++=u8FileName[u8Counter];
			  WHandler.Dir_Entry=(u16Block*EntriesPerBlock)+((u16Index)/RootEntrySize);
			  WHandler.File_Size=LWordSwap(sFileStructure->SizeofFile);
			  WHandler.BaseFatEntry=ByteSwap(sFileStructure->FirstClusterNumber);
                            
			  if(WHandler.BaseFatEntry != 0)
                            {
			      u16Temporal=WHandler.BaseFatEntry;
			      do
                                {
				  WHandler.CurrentFatEntry=WHandler.BaseFatEntry;
				  WHandler.BaseFatEntry=FAT_Entry(WHandler.CurrentFatEntry,0,NEXT_ENTRY);
                                }while(WHandler.BaseFatEntry!=CLUSTER_EOF_16);
			      WHandler.BaseFatEntry=u16Temporal;
                            } 
			  else
                            {
			      WHandler.BaseFatEntry=FAT_SearchAvailableCluster(0);
			      WHandler.CurrentFatEntry=WHandler.BaseFatEntry;
                            }
			  /*****************/
			  /* Double Check */
			  /*****************/
                            
			  u8Counter=0;
			  u8ErrorCode = u16FAT_Cluster_Size;
			  while(u8ErrorCode != 0x01)
                            {
			      u8Counter++;
			      u8ErrorCode=u8ErrorCode>>1;
                            }
                            
			  u16Temporal=(UINT16)WHandler.File_Size % (u16FAT_Sector_Size<<u8Counter);
			  WHandler.ClusterIndex= u16Temporal/u16FAT_Sector_Size;
			  WHandler.SectorIndex=  u16Temporal%u16FAT_Sector_Size;
			  u8ErrorCode=FILE_FOUND;
                        }
                    }
                }
            }

	  /* If Write function */
	  if(u8Function==CREATE)
            {
	      if(sFileStructure->FileName[0]==FILE_Clear || sFileStructure->FileName[0]==FILE_Erased) 
                {
                    
		  pu8Pointer=WHandler.FileName;
		  for(u8Counter=0;u8Counter<11;u8Counter++)
		    *pu8Pointer++=u8FileName[u8Counter];

		  WHandler.Dir_Entry=(u16Block*EntriesPerBlock)+((u16Index)/RootEntrySize);
		  WHandler.File_Size=0;
		  WHandler.BaseFatEntry=FAT_SearchAvailableCluster(0);
		  WHandler.CurrentFatEntry=WHandler.BaseFatEntry;
		  WHandler.ClusterIndex=0;
		  WHandler.SectorIndex=0;
        
		  if(WHandler.BaseFatEntry)
		    u8ErrorCode=FILE_CREATE_OK;
		  else
		    u8ErrorCode=NO_FAT_ENTRY_AVAILABLE;
                }
            }
	  sFileStructure++;
	  u16Index+=RootEntrySize;
        }
      u16Block++;
    }
  if(u16BlockNum==u16Block)
    u8ErrorCode=NO_FILE_ENTRY_AVAILABLE;
    
  return(u8ErrorCode);

}

const UINT8 GetChar[13] = { 1, 3, 5, 7, 9, 14, 16, 18, 20, 22, 24, 28, 30};
UINT8 FAT_Filename(root_Entries* dirEntry)
{
  UINT8 i=0;
  UINT8 j=0;
  DIR_ENT_LFN* pDirEnt = (DIR_ENT_LFN*)dirEntry;
  UINT8* u8ptr_Dirent = (UINT8*)dirEntry;
  static UINT8 index = 0;
  FileName[0] = '\0';
  
if(dirEntry->FileName[0]!=FILE_Clear)  
  	{
		if((dirEntry->FileName[0]!=FILE_Erased)  && ((dirEntry->Attributes==AT_ARCHIVE) || (dirEntry->Attributes==AT_DIRECTORY) || (dirEntry->Attributes==AT_READONLY) || (dirEntry->Attributes==AT_LFN)))  								
			{ 
			if(dirEntry->Attributes==AT_LFN)
			{
				if ((pDirEnt->Ordinal>0x40))
				{
					index = (((pDirEnt->Ordinal) - 0x41)*13);  // help.h
					FileName[index+13] = '\0';
				}else 
				{
					index -= 13;
				}
				for( i=0;(i<=12) && (u8ptr_Dirent[GetChar[i]]!= 0xff) ;i++)
					{
						FileName[index+i] = u8ptr_Dirent[GetChar[i]];
					}
				if(index!=0)
				{
					return(_longFileNameNOK);   //le nom n'est pas complet
				}
				else 
				{
					return(_LongFileNameOK);
				}
			}
			else// if (isalpha(dirEntry->FileName[0]))
			{
				for(i=0;(i<8) && (dirEntry->FileName[i]!=0x20);i++)
				{
						{
							FileName[i] = dirEntry->FileName[i];
						}
				}
	  			if (dirEntry->Attributes == AT_DIRECTORY)//si c'est un dossier 
	  				{
	  					FileName[i++] = '\\';
	  					FileName[i] = '\0';
	  					return(_directory);
	  				}
	  			else // sinon c'est un fichier => affiche l'extension
	  				{
	  					FileName[i++] = '.';
	  					for(j=0;j<3;j++)
	  					{
	  						FileName[i++] = dirEntry->Extension[j]; 
	  					}
	  					FileName[i] = '\0';
	  					return (_file);
	  				}
			}
  		}
  	}
return (_error);
}
