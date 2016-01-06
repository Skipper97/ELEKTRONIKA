/*
 * FileList.c
 *
 *      Author: Sahuc Guillaume
 *      v1 = Insert / Length / Clear / View.
 */


#include "FileList.h"
#include "console.h"
#include <stdlib.h> /* pour malloc realloc qsort*/
#include "sd.h"
#include "board.h"
#include "Fat.h"
#include "main.h"
#include <string.h>

static UINT16 Id = 0;
const UINT8 test1[] = "file1";
const UINT8 test2[] = "file2";
const UINT8 test3[] = "file3";

void InitFileList(List* List)
{
	List->Lenght = 0;
	List->first = NULL;
}


void InsertNewFileDosFileName(List* List,const UINT8* Text)
{
	FileList* NewFile = (struct FileList *) malloc(sizeof(FileList));
	if (!NewFile) { SD_SysHalt(); }
	NewFile->_Id = Id;	Id++;
	strcpy(NewFile->_DosFileName8_3,Text);
	NewFile->Next = List->first;
	NewFile->Lfn = FALSE;
	NewFile->Selected = FALSE;
	NewFile->_Type = 0;
	List->first = NewFile;
	List->Lenght++;
}

void InsertNewFileLongFileName(List* List,const UINT8* Text)
{
	FileList* NewFile = (struct FileList *)malloc(sizeof(FileList));
	if (!NewFile) { SD_SysHalt(); }
	NewFile->_Id = Id;	Id++;
	strcpy(NewFile->_LongFileName,Text);
	NewFile->Lfn = TRUE;
	NewFile->Selected = FALSE;
	NewFile->_Type = 0;
	NewFile->Next = List->first;
	List->first = NewFile;
	List->Lenght++;
}

void AddDosFileName(List* List,const UINT8* Text)
{
	strcpy(List->first->_DosFileName8_3,Text);
}

void AddListType(List* List,UINT8 type)
{
	List->first->_Type = type;
}

void ClearFileList(List* List)
{
	FileList* File;
	while(List->first != NULL)
	{
		File = List->first;
		List->first = File->Next;
		free(File);
	}
	List->Lenght =0;
	Id = 0;
}

void ViewFileList(List List)
{
	FileList* File;
	File = List.first;
	while(File)
	{
		if( File->Selected != TRUE)
		{
			if (File->Lfn == TRUE)
			{
				ConsolePrintf(&console,"%s\n",File->_LongFileName);
			}else 
			{
				ConsolePrintf(&console,"%s\n",File->_DosFileName8_3);
			}
		}else 
		{
			if (File->Lfn == TRUE)
					{
						ConsoleSwapColor(&console);
						ConsolePrintf(&console,"%s\n",File->_LongFileName);
					}else 
					{
						ConsoleSwapColor(&console);
						ConsolePrintf(&console,"%s\n",File->_DosFileName8_3);
					}
			ConsoleSwapColor(&console);
		}
		File = File->Next;	
	}
	ConsolePrintf(&console,"%u element(s) in List.\n",List.Lenght);
	//ConsoleGoToY(&console,300);
	//ConsolePrint(&console,Touch1);	
	//while(SW1){ } // attente appuie sur bouton 1
}

void  SelectFile(List* List)
{
	List->first->Selected = TRUE;
}

void SelectNextFile(List* List)
{
	while(List->first)
	{
		if (List->first->Selected == TRUE)
		{
			List->first->Selected = FALSE;
			List->first = List->first->Next;
			List->first->Selected = TRUE;
			break;
		}else
		{
			List->first = List->first->Next;
		}
	}
}

void TestFileList(void)
{
	List L;
    InitFileList(&L);
    InsertNewFileDosFileName(&L,test1);
    InsertNewFileDosFileName(&L,test2);
    //InsertNewFileDosFileName(&L,test3); don't work if more than 2 files on HCS08, not enough memory.( can be higher without Lfn )
    ViewFileList(L);
    ClearFileList(&L);
    ViewFileList(L);
}
