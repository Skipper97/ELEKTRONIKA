/*
 *
 *      Author: Sahuc Guillaume
 */

#ifndef FILELIST_H_
#define FILELIST_H_

#include "FslTypes.h"
#include <stdtypes.h>
#include <stddef.h>

extern const UINT8 test1[];
extern const UINT8 test2[];
extern const UINT8 test3[];

typedef struct FileList
{
	UINT16 _Id;
	UINT8 _LongFileName[260]; //MAX_LFN_CHARACTERS
	UINT8 _DosFileName8_3[12];
	UINT8 _Type:1; // directory || file 
	UINT8 Selected :1; // true || false 
	UINT8 Lfn:1; // true || false 
	struct FileList *Next;
}FileList;

typedef struct List
{
	size_t Lenght;
	FileList* first;
}List;


void InitFileList(List* data);
void InsertNewFileDosFileName(List* List,const UINT8* Text);
void InsertNewFileLongFileName(List* List,const UINT8* Text);
void AddDosFileName(List* List,const UINT8* Text);
void SelectNextFile(List* List);
void AddListType(List* List,UINT8 type);
void ViewFileList(List List);
void ClearFileList(List* List);
void TestFileList(void);

#endif /* FILELIST_H_ */
