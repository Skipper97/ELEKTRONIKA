/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2008, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

#ifndef COLOR24BITS_H
#define COLOR24BITS_H

//------------------------------------------------------------------------------
/// RGB 24 Bpp
/// RGB 888
/// R7R6R5R4 R3R2R1R0 G7G6G5G4 G3G2G1G0 B7B6B5B4 B3B2B1B0
//------------------------------------------------------------------------------
#define COLOR_24BITS_BLACK          0x000000
#define COLOR_24BITS_WHITE          0xFFFFFF

#define COLOR_24BITS_BLUE           0x0000FF
#define COLOR_24BITS_GREEN          0x00FF00
#define COLOR_24BITS_RED            0xFF0000

#define COLOR_24BITS_NAVY           0x000080
#define COLOR_24BITS_DARKBLUE       0x00008B
#define COLOR_24BITS_DARKGREEN      0x006400
#define COLOR_24BITS_DARKCYAN       0x008B8B
#define COLOR_24BITS_CYAN           0x00FFFF
#define COLOR_24BITS_TURQUOISE      0x40E0D0
#define COLOR_24BITS_INDIGO         0x4B0082
#define COLOR_24BITS_DARKRED        0x800000
#define COLOR_24BITS_OLIVE          0x808000
#define COLOR_24BITS_GRAY           0x808080
#define COLOR_24BITS_SKYBLUE        0x87CEEB
#define COLOR_24BITS_BLUEVIOLET     0x8A2BE2
#define COLOR_24BITS_LIGHTGREEN     0x90EE90
#define COLOR_24BITS_DARKVIOLET     0x9400D3
#define COLOR_24BITS_YELLOWGREEN    0x9ACD32
#define COLOR_24BITS_BROWN          0xA52A2A
#define COLOR_24BITS_DARKGRAY       0xA9A9A9
#define COLOR_24BITS_SIENNA         0xA0522D
#define COLOR_24BITS_LIGHTBLUE      0xADD8E6
#define COLOR_24BITS_GREENYELLOW    0xADFF2F
#define COLOR_24BITS_SILVER         0xC0C0C0
#define COLOR_24BITS_LIGHTGREY      0xD3D3D3
#define COLOR_24BITS_LIGHTCYAN      0xE0FFFF
#define COLOR_24BITS_VIOLET         0xEE82EE
#define COLOR_24BITS_AZUR           0xF0FFFF
#define COLOR_24BITS_BEIGE          0xF5F5DC
#define COLOR_24BITS_MAGENTA        0xFF00FF
#define COLOR_24BITS_TOMATO         0xFF6347
#define COLOR_24BITS_GOLD           0xFFD700
#define COLOR_24BITS_ORANGE         0xFFA500
#define COLOR_24BITS_SNOW           0xFFFAFA
#define COLOR_24BITS_YELLOW         0xFFFF00



typedef struct colorRGB_24bits
{
	UINT8	red;
	UINT8	green;
	UINT8	blue;
} Color_RGB;

// Convert 24bits color to 16bits color 
#define RGB24ToRGB16(color) (((color >> 8) & 0xF800) | ((color >> 5) & 0x7E0) | \
    ((color >> 3) & 0x1F))

//color convertion BMP 24 bits format to LCD 16 bits format (565)
#define RGB24ToRGB565(r,g,b) ((r / 8) << 11) | ((g / 4) << 5) | (b / 8)

#endif // #define COLOR24BITS_H
