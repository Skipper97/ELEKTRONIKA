/*
 * backup.h
 *
 *      Author: Guillaume Sahuc
 *      fichier non inclus juste pour sauvegarde/backup de code 
 *      this file is not compiled !
 */

#ifndef BACKUP_H_
#define BACKUP_H_

/*test ecriture sdcard*/
     fp = fopen("FILE.TXT","w");
     if(fp == NULL)
     {
    	 Lcd_print(0,0,"pas de fichier file.txt",0x0000,0xffff);
     }else 
     {
    	 Lcd_print(0,0,"fichier file ouvert",0x0000,0xffff);
    	 fputs("tata",fp);
    	 fprintf(fp,"toto %s",tata);
    	 printf("...");
     }
 	fclose(fp);
 	 Lcd_print(0,20,"fichier file ferme",0x0000,0xffff);
 	while(SW1){ }
 	SD_ReadFile("FILE.TXT");
 	/*fin test ecriture sdcard*/




/*
unsigned const char image[] = { 
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBE,0xF7,0x7D,0xEF,
0xBA,0xD6,0xB6,0xB5,0xF3,0x9C,0xB2,0x94,0xB3,0x9C,0xB2,0x94,0x34,0xA5,0xF7,0xBD,
0xFB,0xDE,0x7D,0xEF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBE,0xF7,0xFB,0xDE,0xF3,0x9C,0xCB,0x5A,
0xC7,0x39,0x04,0x21,0x82,0x10,0x42,0x10,0x42,0x10,0x41,0x08,0x83,0x18,0x45,0x29,
0xC7,0x39,0x0C,0x63,0x75,0xAD,0x3C,0xE7,0xBE,0xF7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3C,0xE7,0xB2,0x94,0x08,0x42,0xC3,0x18,0x82,0x10,
0x04,0x21,0x45,0x29,0x86,0x31,0x86,0x31,0x86,0x31,0x86,0x31,0x45,0x29,0x04,0x21,
0x82,0x10,0x41,0x08,0xC3,0x18,0x08,0x42,0xF3,0x9C,0x3C,0xE7,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFB,0xDE,0x0C,0x63,0xC3,0x18,0xC3,0x18,0x45,0x29,0xC7,0x39,
0x08,0x42,0x08,0x42,0x08,0x42,0x08,0x42,0x08,0x42,0x08,0x42,0xC7,0x39,0xC7,0x39,
0x86,0x31,0x86,0x31,0x04,0x21,0x41,0x08,0x82,0x10,0xCB,0x5A,0xBA,0xD6,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFB,0xDE,0xCB,0x5A,0x82,0x10,0x45,0x29,0xC7,0x39,0x08,0x42,0x08,0x42,
0x09,0x4A,0x49,0x4A,0x49,0x4A,0x49,0x4A,0x49,0x4A,0x49,0x4A,0x08,0x42,0xC7,0x39,
0xC7,0x39,0xC7,0x39,0x86,0x31,0x45,0x29,0x83,0x18,0x00,0x00,0xC8,0x41,0x38,0xC6,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x7D,0xEF,0x8E,0x73,0x82,0x10,0x45,0x29,0xC7,0x39,0x08,0x42,0x09,0x4A,0x8A,0x52,
0x30,0x84,0xCF,0x7B,0x8A,0x52,0x49,0x4A,0x4A,0x52,0x49,0x4A,0xCB,0x5A,0xCF,0x7B,
0x0C,0x63,0x08,0x42,0xC7,0x39,0x86,0x31,0x45,0x29,0xC3,0x18,0x00,0x00,0x49,0x4A,
0xBA,0xD6,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xF3,0x9C,0xC3,0x18,0x04,0x21,0xC7,0x39,0x08,0x42,0x49,0x4A,0x49,0x4A,0x72,0x94,
0x7D,0xEF,0x7D,0xEF,0xB2,0x94,0x4A,0x52,0x49,0x4A,0x8A,0x52,0x75,0xAD,0xBE,0xF7,
0xBA,0xD6,0x4D,0x6B,0xC7,0x39,0xC7,0x39,0x86,0x31,0x45,0x29,0xC3,0x18,0x41,0x08,
0xCF,0x7B,0x7C,0xE7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBA,0xD6,
0x08,0x42,0x82,0x10,0xC7,0x39,0x08,0x42,0x49,0x4A,0x49,0x4A,0x8E,0x73,0xFB,0xDE,
0xFF,0xFF,0xBE,0xF7,0xBA,0xD6,0x8E,0x73,0x08,0x42,0x30,0x84,0x3C,0xE7,0x7D,0xEF,
0xFF,0xFF,0xB6,0xB5,0x49,0x4A,0xC7,0x39,0x86,0x31,0x45,0x29,0x04,0x21,0x41,0x08,
0x45,0x29,0xB6,0xB5,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBE,0xF7,0x71,0x8C,
0x41,0x08,0x45,0x29,0x08,0x42,0x49,0x4A,0x49,0x4A,0x4A,0x52,0xB2,0x94,0xBE,0xF7,
0xBE,0xF7,0xB2,0x94,0xCF,0x7B,0xCF,0x7B,0x49,0x4A,0xB6,0xB5,0xF3,0x9C,0x0C,0x63,
0x38,0xC6,0xBA,0xD6,0x0C,0x63,0x87,0x39,0xC7,0x39,0x86,0x31,0x45,0x29,0xC3,0x18,
0x41,0x08,0x30,0x84,0x7D,0xEF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3C,0xE7,0xCB,0x5A,
0x41,0x08,0xC7,0x39,0x08,0x42,0x49,0x4A,0x4A,0x52,0x8A,0x52,0xF3,0x9C,0xFF,0xFF,
0x7D,0xEF,0xC7,0x39,0xC3,0x18,0x0C,0x63,0xCB,0x5A,0xB6,0xB5,0xB2,0x94,0xCB,0x5A,
0x75,0xAD,0xFA,0xD6,0x4D,0x6B,0x87,0x39,0xC7,0x39,0x86,0x31,0x45,0x29,0x04,0x21,
0x41,0x08,0x8A,0x52,0x79,0xCE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x38,0xC6,0x86,0x31,
0x04,0x21,0xC8,0x41,0x49,0x4A,0x49,0x4A,0x4A,0x52,0x49,0x4A,0xB1,0x8C,0xBE,0xF7,
0xBE,0xF7,0xB2,0x94,0xCF,0x7B,0xCF,0x7B,0x49,0x4A,0x74,0xA5,0x7D,0xEF,0x7C,0xE7,
0xBE,0xF7,0x79,0xCE,0x0C,0x63,0xC7,0x39,0xC7,0x39,0x86,0x31,0x45,0x29,0x04,0x21,
0x82,0x10,0x45,0x29,0x75,0xAD,0xBE,0xF7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x34,0xA5,0x82,0x10,
0x86,0x31,0x08,0x42,0x49,0x4A,0x49,0x4A,0x8A,0x52,0x49,0x4A,0x4D,0x6B,0xBA,0xD6,
0xFF,0xFF,0xFF,0xFF,0x79,0xCE,0x0D,0x63,0xC7,0x39,0xCF,0x7B,0x7D,0xEF,0xFF,0xFF,
0xFF,0xFF,0x75,0xAD,0x08,0x42,0x86,0x31,0xC7,0x39,0x86,0x31,0x45,0x29,0x45,0x29,
0xC3,0x18,0xC3,0x18,0xB2,0x94,0x7D,0xEF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBE,0xF7,0xB2,0x8C,0x41,0x08,
0xC7,0x39,0x08,0x42,0x49,0x4A,0x49,0x4A,0x8A,0x52,0x8A,0x52,0x4A,0x4A,0xD0,0x7B,
0x7A,0xC6,0x7B,0xBE,0x90,0x6B,0xC9,0x39,0x88,0x31,0xC9,0x39,0xB3,0x84,0xBB,0xC6,
0xF8,0xB5,0xCC,0x5A,0x86,0x31,0xC7,0x39,0xC7,0x39,0x86,0x31,0x45,0x29,0x45,0x29,
0xC4,0x20,0x41,0x08,0x30,0x84,0x3C,0xE7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3C,0xE7,0x8A,0x4A,0xC3,0x10,
0xC7,0x39,0x08,0x42,0x49,0x4A,0x49,0x4A,0x4A,0x4A,0x4A,0x42,0x09,0x3A,0x08,0x4A,
0x09,0x6B,0x49,0x7B,0xC6,0x7A,0x05,0x83,0x46,0x83,0xC5,0x7A,0xC6,0x72,0x09,0x7B,
0x48,0x5A,0x87,0x31,0x88,0x21,0x88,0x29,0x86,0x31,0x86,0x31,0x45,0x29,0x45,0x29,
0x04,0x21,0x41,0x08,0x4A,0x4A,0xBA,0xD6,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF7,0xC5,0x82,0x50,0x05,0x41,
0xC7,0x29,0x08,0x42,0x49,0x4A,0x4A,0x42,0x49,0x4A,0x09,0x7B,0x88,0x9B,0xC6,0xB3,
0x21,0xD4,0xA0,0xDC,0xE1,0xE4,0x61,0xED,0x61,0xED,0x21,0xED,0xA0,0xE4,0x20,0xDC,
0x80,0xCB,0x43,0xAB,0xC4,0x82,0x06,0x5A,0x47,0x21,0x46,0x29,0x45,0x29,0x04,0x29,
0x04,0x19,0x82,0x10,0x82,0x18,0xF3,0x9C,0x7D,0xEF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7D,0xEF,0x4D,0x93,0x00,0xA0,0x82,0xB8,
0xC7,0x31,0x09,0x32,0x49,0x4A,0x86,0x7A,0x43,0xC3,0x6B,0xED,0xF4,0xF6,0xEB,0xFD,
0x20,0xFD,0x20,0xFD,0x60,0xFD,0xA0,0xFD,0xA0,0xFD,0x60,0xFD,0x60,0xFD,0x20,0xFD,
0xE0,0xFC,0xA0,0xFC,0x60,0xF4,0xC1,0xDB,0x83,0x9A,0xC5,0x49,0x45,0x29,0x04,0x19,
0xC4,0x20,0x82,0x38,0x00,0x50,0xCB,0x6A,0xBA,0xD6,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFB,0xEE,0x04,0xA1,0x00,0xC0,0x00,0xF0,
0xC3,0xA0,0xC8,0x41,0x49,0x42,0x05,0x9B,0x20,0xFC,0xA4,0xFC,0x69,0xFD,0xE8,0xFD,
0x63,0xFD,0x20,0xFD,0x60,0xFD,0x60,0xFD,0x60,0xFD,0x20,0xFD,0x20,0xFD,0xE0,0xFC,
0xE0,0xFC,0xA0,0xFC,0x60,0xFC,0x20,0xFC,0x41,0xD3,0xC5,0x49,0x45,0x19,0xC4,0x38,
0x82,0x68,0x41,0x88,0x00,0x70,0x49,0x5A,0x79,0xCE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFB,0xF6,0x82,0xC0,0x00,0xD0,0x86,0xC1,
0x46,0xF1,0x41,0xC8,0x45,0x79,0x89,0x52,0x88,0x62,0x86,0x6A,0xC6,0x7A,0xC4,0xBB,
0xE1,0xFC,0x60,0xFD,0x60,0xFD,0xA0,0xFD,0xA0,0xFD,0x60,0xFD,0x60,0xFD,0xE0,0xFC,
0x60,0xE4,0x03,0x93,0x84,0x72,0x44,0x6A,0xC5,0x41,0x45,0x29,0xC3,0x58,0x41,0xA8,
0x40,0x98,0x00,0xB0,0x00,0x60,0x0C,0x6B,0x79,0xCE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7D,0xEF,0xCE,0x83,0x82,0x88,0x00,0xF8,0xC4,0xD8,
0x0C,0xF3,0x8A,0xFA,0x82,0xE8,0x82,0xB0,0x45,0x69,0xC7,0x51,0x08,0x42,0x08,0x3A,
0x86,0x5A,0x83,0x9B,0xA2,0xBC,0x22,0xCD,0x21,0xCD,0xA1,0xC4,0x22,0xB4,0xC4,0x7A,
0x06,0x3A,0x86,0x29,0x45,0x29,0x05,0x31,0xC4,0x50,0x41,0x90,0x00,0xC0,0x00,0xA8,
0x00,0xA0,0x00,0xA8,0x00,0x30,0x4A,0x4A,0xBA,0xD6,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0x7D,0xEF,0x8E,0x73,0xC3,0x18,0x05,0x39,0x82,0xA8,0x00,0xF8,
0xC3,0xF8,0x4D,0xFB,0x4D,0xFB,0xC7,0xF9,0xC3,0xF0,0x82,0xD8,0xC3,0xB0,0x04,0x81,
0x45,0x61,0x46,0x51,0x86,0x49,0x86,0x49,0x46,0x41,0x45,0x41,0x45,0x41,0x45,0x41,
0x05,0x49,0x04,0x61,0x82,0x90,0x41,0xB0,0x00,0xD0,0x00,0xC8,0x00,0xA8,0x00,0xA8,
0x00,0xB8,0x41,0x58,0x82,0x10,0x82,0x10,0xB2,0x94,0xBE,0xF7,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xBE,0xF7,0xCF,0x7B,0x82,0x10,0x04,0x21,0x86,0x29,0x86,0x41,0x04,0x99,
0x40,0xE8,0x41,0xF8,0x86,0xF9,0xCB,0xFA,0x49,0xFA,0x82,0xF8,0x00,0xF8,0x00,0xF0,
0x00,0xE8,0x41,0xD8,0x41,0xD0,0x41,0xC0,0x41,0xC0,0x41,0xC0,0x41,0xC0,0x41,0xC8,
0x00,0xD0,0x00,0xE0,0x00,0xE0,0x00,0xD8,0x00,0xD0,0x00,0xB8,0x00,0xA8,0x41,0x88,
0x82,0x48,0x82,0x10,0x82,0x10,0x00,0x00,0x45,0x29,0x79,0xCE,0xFF,0xFF,0xFF,0xFF,
0xBE,0xF7,0xF3,0x9C,0x82,0x10,0xC3,0x18,0x45,0x29,0x86,0x31,0xC7,0x31,0x30,0x7C,
0xF3,0xDC,0x86,0xE1,0x00,0xF0,0x00,0xF8,0x41,0xF8,0x41,0xF8,0x00,0xF8,0x00,0xF8,
0x00,0xF8,0x00,0xF8,0x00,0xF8,0x00,0xF8,0x00,0xF8,0x00,0xF8,0x00,0xF8,0x00,0xF8,
0x00,0xE8,0x00,0xE0,0x00,0xE0,0x00,0xD8,0x00,0xC8,0x41,0xA0,0x8A,0x9A,0x0C,0x63,
0x04,0x11,0x82,0x10,0x82,0x10,0x41,0x08,0x00,0x00,0x4D,0x6B,0x7D,0xEF,0xFF,0xFF,
0xFB,0xDE,0x08,0x42,0x42,0x10,0x45,0x29,0x86,0x31,0x86,0x31,0x49,0x4A,0x38,0xBE,
0xFF,0xFF,0x38,0xD6,0x86,0xA9,0x00,0xC8,0x00,0xE0,0x00,0xF0,0x00,0xF8,0x00,0xF8,
0x00,0xF8,0x00,0xF8,0x00,0xF8,0x00,0xF8,0x00,0xF8,0x00,0xF8,0x00,0xF0,0x00,0xF0,
0x00,0xE8,0x00,0xE0,0x00,0xD0,0xC3,0x98,0x8A,0x8A,0xB2,0xA4,0xBA,0xC6,0xF7,0xB5,
0x08,0x42,0x41,0x08,0x82,0x10,0x41,0x08,0x00,0x00,0x45,0x29,0xF7,0xBD,0xFF,0xFF,
0x71,0x8C,0x41,0x08,0x04,0x21,0x45,0x29,0x86,0x31,0x86,0x31,0x0C,0x63,0x3C,0xE7,
0xFF,0xFF,0x79,0xD6,0x46,0xB9,0x00,0xE0,0x42,0xC8,0x82,0xA8,0x82,0xB0,0x41,0xD8,
0x82,0xE8,0x82,0xF0,0x41,0xE8,0x41,0xE8,0x41,0xE8,0x41,0xF0,0x41,0xE8,0x41,0xD8,
0x04,0xC1,0x08,0x92,0x4D,0x8B,0x34,0xA5,0xFB,0xC6,0xFB,0xD6,0xBA,0xCE,0x3C,0xE7,
0x30,0x84,0xC3,0x18,0x41,0x08,0x41,0x08,0x00,0x00,0x41,0x08,0xCF,0x7B,0x7D,0xEF,
0x49,0x4A,0x00,0x00,0x04,0x21,0x45,0x29,0x46,0x31,0x86,0x31,0x30,0x84,0xFF,0xFF,
0xFF,0xF7,0xF7,0xDD,0x09,0xDA,0x83,0xF8,0x01,0xF0,0x42,0xC0,0x82,0x98,0x49,0x9A,
0xF3,0xB4,0xF3,0xCC,0x71,0xBC,0x8E,0xBB,0x8E,0xBB,0x30,0xBC,0x71,0xBC,0xF3,0xBC,
0xB6,0xBD,0xFB,0xCE,0xBE,0xE7,0x7D,0xE7,0x3B,0xDF,0xBA,0xD6,0x79,0xCE,0xFB,0xDE,
0x75,0xAD,0x86,0x31,0x41,0x08,0x41,0x08,0x00,0x00,0x00,0x00,0x49,0x4A,0xFB,0xDE,
0x04,0x21,0x41,0x08,0x04,0x21,0x45,0x29,0x45,0x29,0x87,0x39,0xB2,0x94,0xFF,0xFF,
0xBE,0xF7,0x34,0xDD,0x0C,0xEB,0x09,0xFA,0x00,0xF0,0x01,0xD8,0x00,0xD8,0x8B,0xD2,
0x7D,0xE7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xBE,0xFF,0x7D,0xEF,0xFB,0xDE,0xFB,0xDE,0xBA,0xD6,0x79,0xCE,0xBA,0xD6,
0x78,0xC6,0xC7,0x39,0x00,0x00,0x41,0x08,0x00,0x00,0x00,0x00,0xC7,0x39,0x79,0xCE,
0x00,0x00,0x82,0x10,0xC3,0x18,0x04,0x21,0x05,0x29,0x86,0x31,0xB3,0x9C,0xFF,0xFF,
0xFF,0xF7,0x75,0xDD,0xC7,0xE9,0xC7,0xF9,0x01,0xF8,0x01,0xF0,0x00,0xE8,0x49,0xE2,
0xFB,0xEE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xBE,0xF7,0x7D,0xEF,0xFB,0xDE,0xFB,0xDE,0xBA,0xD6,0x79,0xCE,0xBA,0xD6,
0xB9,0xCE,0x08,0x42,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC7,0x39,0x38,0xC6,
0x00,0x00,0x82,0x10,0x82,0x10,0x04,0x21,0x04,0x21,0x45,0x29,0x30,0x84,0xFF,0xFF,
0xFF,0xFF,0x38,0xDE,0xC4,0xD0,0x00,0xF0,0x01,0xF8,0x00,0xF8,0x00,0xF0,0x08,0xD2,
0xFB,0xE6,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xBE,0xF7,0x7D,0xEF,0xFB,0xDE,0xBA,0xD6,0x79,0xCE,0x79,0xCE,0xBA,0xD6,
0x79,0xCE,0xC7,0x39,0x41,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x86,0x31,0x38,0xC6,
0x00,0x00,0x00,0x00,0xC3,0x18,0xCB,0x5A,0x86,0x31,0xC3,0x18,0xCB,0x5A,0x7D,0xEF,
0xFF,0xFF,0x7D,0xEF,0xCF,0xBB,0xC3,0xB0,0x41,0xD0,0x41,0xD0,0x82,0xB8,0x4D,0xB3,
0x7D,0xE7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xBE,0xF7,0xBE,0xF7,0x3D,0xEF,0xFB,0xDE,0xBA,0xD6,0x79,0xCE,0x79,0xCE,0xFA,0xD6,
0xF7,0xBD,0x04,0x21,0x86,0x31,0x04,0x21,0x00,0x00,0x00,0x00,0x86,0x31,0x38,0xC6,
0x86,0x31,0xC3,0x18,0xCB,0x5A,0x75,0xAD,0xCF,0x7B,0x41,0x08,0x86,0x31,0xF7,0xBD,
0xFF,0xFF,0xFF,0xFF,0xBE,0xEF,0x74,0xB5,0x30,0x9C,0x30,0x9C,0x72,0xA4,0xBB,0xD6,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xBE,0xF7,0x7D,0xEF,0x3C,0xE7,0xFB,0xDE,0xBA,0xD6,0x79,0xCE,0x79,0xCE,0x3C,0xE7,
0x71,0x8C,0x81,0x08,0x0C,0x63,0xCF,0x7B,0x82,0x10,0x00,0x00,0x8A,0x52,0x38,0xC6,
0x75,0xAD,0x71,0x8C,0xB6,0xB5,0x3C,0xE7,0xFB,0xDE,0xC7,0x39,0x00,0x00,0xCF,0x73,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBE,0xF7,
0x7D,0xEF,0x7D,0xEF,0x3B,0xDF,0xFA,0xD6,0x79,0xCE,0x79,0xCE,0xFB,0xDE,0xB9,0xCE,
0xC7,0x39,0xC4,0x20,0x71,0x8C,0xBA,0xD6,0x71,0x8C,0xCB,0x5A,0xB2,0x94,0xBA,0xD6,
0xFF,0xFF,0x7D,0xEF,0x7D,0xEF,0xFF,0xFF,0xFF,0xFF,0xB6,0xB5,0x46,0x29,0x05,0x19,
0x75,0xA5,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBE,0xF7,
0x7D,0xEF,0x3C,0xE7,0xFB,0xDE,0xBA,0xD6,0x79,0xCE,0xBA,0xD6,0xFC,0xDE,0x4E,0x63,
0x42,0x08,0x0C,0x63,0xF7,0xBD,0xBE,0xF7,0xFF,0xFF,0xFB,0xDE,0xFB,0xDE,0xBE,0xF7,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF4,0x9C,0x04,0x21,
0x05,0x21,0xB6,0xA5,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBE,0xF7,0xBE,0xF7,0x7D,0xEF,
0x3C,0xE7,0xFB,0xDE,0xBA,0xD6,0x79,0xCE,0xFB,0xDE,0xBB,0xD6,0xD1,0x73,0x83,0x18,
0x86,0x39,0x34,0x9D,0xBD,0xEF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBE,0xFF,0x35,0xD6,0xEB,0xCC,0x43,0xB3,
0x40,0x51,0x05,0x19,0xF5,0x8C,0xBE,0xEF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBE,0xF7,0xBE,0xF7,0x7D,0xEF,0x7D,0xEF,0x3C,0xE7,
0xFB,0xDE,0xBA,0xDE,0xBA,0xD6,0x3C,0xDF,0x3A,0xBE,0x4F,0x63,0x82,0x49,0x40,0xA3,
0x23,0xB4,0xCC,0x83,0x3A,0xBE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBF,0xF7,0xB5,0xBD,0x82,0x92,0x20,0xF4,0xA0,0xFC,
0x60,0xE4,0x40,0x82,0x84,0x41,0x8F,0x6B,0x77,0xAD,0x3D,0xE7,0xFF,0xFF,0xFF,0xFF,
0xFE,0xFF,0xBE,0xF7,0xBE,0xF7,0xBE,0xF7,0x7D,0xEF,0x7D,0xEF,0x3C,0xE7,0xFB,0xDE,
0xFB,0xDE,0x3D,0xE7,0xBB,0xCE,0x36,0x9D,0x0B,0x6B,0x41,0x6A,0x60,0xC4,0x20,0xFE,
0x60,0xF5,0x00,0x8B,0xC7,0x6A,0x38,0xC6,0xBE,0xF7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7D,0xEF,0x4B,0x7B,0x80,0xB2,0xA0,0xFC,0xA0,0xFC,
0xE0,0xFC,0xE0,0xFC,0xC0,0xCB,0xC1,0x8A,0x45,0x62,0x4D,0x6B,0xB3,0x94,0xF7,0xBD,
0x3D,0xDF,0xFF,0xF7,0xFF,0xFF,0xBE,0xF7,0x7D,0xEF,0x7D,0xEF,0x7D,0xE7,0x3D,0xDF,
0xBA,0xC6,0x75,0xA5,0x8D,0x7B,0x84,0x7A,0x40,0xB3,0xE0,0xEC,0xE0,0xFD,0xE0,0xFD,
0x60,0xF5,0x20,0xE5,0xA0,0xD4,0x0A,0x6B,0xFB,0xDE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7D,0xEF,0xCC,0x93,0x40,0xEB,0x60,0xFC,0xA0,0xFC,
0xE0,0xFC,0x20,0xFD,0x60,0xFD,0x20,0xF5,0xA0,0xD4,0xC0,0xBB,0x42,0x9B,0x45,0x8B,
0x6B,0x9C,0xAE,0x9C,0x71,0x8C,0xB3,0x94,0x33,0x9D,0x34,0xA5,0xF2,0xA4,0xF0,0xB4,
0xCA,0x9B,0x04,0x9B,0x40,0xBB,0x20,0xE4,0x20,0xFD,0xA0,0xFD,0xA0,0xFD,0xE0,0xFD,
0xE0,0xFD,0xE0,0xFD,0x20,0xC4,0x88,0x5A,0x38,0xBE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x78,0xD6,0x46,0xAB,0x40,0xDB,0x20,0xF4,
0x60,0xFC,0xA0,0xFC,0xE0,0xFC,0x60,0xFD,0xA0,0xFD,0x60,0xFD,0x20,0xF5,0xA0,0xDC,
0xC0,0xB3,0xC0,0x51,0x86,0x29,0x0D,0x63,0x8F,0x7B,0x0D,0x5B,0xC7,0x41,0x01,0x82,
0x00,0xC3,0xC0,0xE3,0x60,0xFC,0xA0,0xFC,0xE0,0xFC,0xE0,0xFC,0x60,0xF5,0x60,0xF5,
0x20,0xE5,0x80,0x9B,0x86,0x62,0x30,0x84,0x79,0xCE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x38,0xC6,0x2D,0x9C,0x05,0x93,
0x43,0xA3,0x82,0xB3,0xC2,0xBB,0xC2,0xBB,0x22,0xB4,0x82,0xA3,0x42,0x93,0xC3,0x7A,
0x85,0x62,0x0B,0x63,0x71,0x84,0xB6,0xB5,0x79,0xCE,0x79,0xC6,0xB5,0xAD,0x70,0x94,
0x4A,0x8B,0x06,0x83,0x04,0x93,0x04,0x9B,0x43,0x9B,0x43,0x9B,0x43,0x93,0x04,0x83,
0x08,0x73,0x8D,0x73,0xB3,0x94,0x79,0xCE,0x7D,0xEF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3C,0xDF,0x38,0xBE,
0x75,0xB5,0x33,0xA5,0x33,0xA5,0xF3,0x9C,0xF3,0x9C,0xF3,0x9C,0xF3,0x94,0xF3,0x9C,
0x35,0xA5,0xF8,0xBD,0xFB,0xDE,0xBE,0xF7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7E,0xEF,
0xBB,0xD6,0xF8,0xBD,0xB6,0xAD,0x75,0xAD,0x34,0xA5,0x33,0x9D,0x34,0x9D,0x35,0xA5,
0xB7,0xAD,0x79,0xC6,0x3C,0xE7,0xBE,0xF7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
};
*/


/*	for(k=0;k<8;k++){
		for(j=0;j<6;j++){	
			Lcd_address_set(40*j,40*k,40*j+39,40*k+39);		
			for(i=0;i<1600;i++){
					Lcd_write_color(image[i*2+1],image[i*2]);	 								
				}
		}
	}	
DelayMs(1000);*/



void TouchPanelRead(void){
	UINT8 MSB_X,LSB_X,MSB_Y,LSB_Y; // 8 bits data from ADS7843
	INT16 TP_X,TP_Y;	//touch panel X & Y  12 bits from MSB + LSB  
//	while(TOUCH_BUSY){}  //pas nécessaire
/*----------------------------------------------------------------------------------------*/
			TP_Y = SPI1D; // lecture factice
			/*------------------------------------
			 * RECEIVE Y TOUCH PANEL ( portrait mode = vertical otherwise it's X in landscape mode = horizontal )
			------------------------------------*/
			while(!SPI1S_SPTEF){} //data send ready ? 
			SPI1D = 0x90;//Y REQUEST 
			while(!SPI1S_SPRF){} //data read ready ? 
			TP_Y = SPI1D; // lecture factice
			while(!SPI1S_SPTEF){} //data send ready ? 
			SPI1D = 0x00; // ecriture factice
			while(!SPI1S_SPRF){} //data read ready ?
			MSB_Y = SPI1D; // lecture Y MSB  
			while(!SPI1S_SPTEF){} //data send ready ? 
			SPI1D = 0xD0;// X REQUEST  
			while(!SPI1S_SPRF){}
			LSB_Y = SPI1D; // lecture Y LSB 
			/*------------------------------------
			 * RECEIVE X TOUCH PANEL ( portrait mode = vertical otherwise it's Y in landscape mode = horizontal  )
			------------------------------------*/
			while(!SPI1S_SPTEF){} //data send ready ? 
			SPI1D = 0x00;// ecriture factice
			while(!SPI1S_SPRF){} //data read ready ?   
			MSB_X = SPI1D; // lecture factice 
			while(!SPI1S_SPTEF){} //data send ready ? 
			SPI1D = 0x00; // ecriture factice
			while(!SPI1S_SPRF){} //data read ready ?
			LSB_X = SPI1D; // lecture X MSB
/*----------------------------------------------------------------------------------------*/
			TP_X = ((MSB_X<<8) | (LSB_X))>>3; // 12 bits data from ADS7843
			TP_Y = ((MSB_Y<<8) | (LSB_Y))>>3; // 12 bits data from ADS7843
				//debug RAW
				IntToStr(TP_X,ss);
				Lcd_print(10,270,"X:",0xf800,0xffff);
				Lcd_print(25,270,ss,0xf800,0xffff);
				//sprintf(ss,"%d",TP_Y);
				IntToStr(TP_Y,ss);
				Lcd_print(80,270,"Y:",0xf800,0xffff);
				Lcd_print(95,270,ss,0xf800,0xffff);
			
			CalibrateXPT2046(&TP_X,&TP_Y);
			
				//debug Calibration
				IntToStr(TP_X,ss);
				Lcd_print(10,305,"X:",0xf800,0xffff);
				Lcd_print(25,305,ss,0xf800,0xffff);
				IntToStr(TP_Y,ss);
				Lcd_print(80,305,"Y:",0xf800,0xffff);
				Lcd_print(95,305,ss,0xf800,0xffff);
				LCD_setPixel(TP_X,TP_Y,0xffff); // for drawing

}


#endif /* BACKUP_H_ */
