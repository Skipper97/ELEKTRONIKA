// source inspiration : http://www.cppfrance.com/codes/LIBBMP_11114.aspx

#ifndef _LIBBMP_H_
#define _LIBBMP_H_

#include "FslTypes.h"

typedef	struct	s_bmp_fh
{
	INT16		sType;				// Deux caractères B et M
	INT16		iSize;				// Taille total du fichier
	INT16		sReserved1;			// 0
	INT16		sReserved2;			// 0
	INT16		iOffBits;			// Offset des bits du bitmap dans le fichier

} t_bmp_fh;


typedef	struct	s_bmp_sh
{
	INT16		iSize;				// Taille de cette structure en octets
	INT16		iWidth;				// Largeur du bitmap en pixel
	INT16		iHeight;			// Hauteur du bitmap en pixel
	INT16		sPlanes;			// 1
	INT16 		sBitCount;			// Bits couleurs par pixel
	INT16		iCompression;		// Schéma de compactage (0 pour aucun)
	INT16		iSizeImage;			// Taille de l’image en octets (utile pour le compactage)
	INT16		iXpelsPerMeter;		// Résolution horizontale en pixels par mètre
	INT16		iYpelsPerMeter;		// Résolution verticale en pixels par mètre
	INT16		iClrUsed;			// Nombre de couleurs utilisées dans l’image
	INT16		iClrImportant;		// Nombre de couleurs importantes

} t_bmp_sh;


typedef	struct	s_bmp_header
{
	t_bmp_fh	first_header;
	t_bmp_sh	second_header;

} t_bmp_header;


typedef struct		s_bmp
{
	t_bmp_header	header;
	INT16			width;
	INT16			width_useless;
	INT16			height;
	INT32 			size; //width * height
//	t_rgb			**data;

} t_bmp;

enum Pixelcolor
{ 
	Red,
	Green,
	Blue
};


#endif
