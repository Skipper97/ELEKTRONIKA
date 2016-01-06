/*
 * console.h
 *
 *      Author: Sahuc Guillaume
 *      v1.0 - first release 
 */

#include "stdtypes.h"
#include "fonts.h"

typedef struct _console 
{
	UINT8 _Id;
	UINT8* _Name;
	UINT16 x,y;
	UINT8 dcolor_H,dcolor_L;
	UINT8 bgcolor_H,bgcolor_L;
	UINT8 _Cursor:1; // true | false 
	UINT8 _Orientation:2; // 0,90,180,270
}CONSOLE;

extern CONSOLE consoleError; // fatal error 
extern CONSOLE console; //foreground console


void ConsolePrint(CONSOLE* console,const UINT8* str);
void ConsolePrintf(CONSOLE* console,const UINT8* format,...);
void ConsoleClear(CONSOLE* console);
void ConsoleGoTo(CONSOLE* console,UINT16 _x, UINT16 _y);
void ConsoleGoToX(CONSOLE* console,UINT16 _x);
void ConsoleGoToY(CONSOLE* console,UINT16 _y);
void ConsoleSwapColor(CONSOLE* console);
void ConsoleCursor(CONSOLE* console);
