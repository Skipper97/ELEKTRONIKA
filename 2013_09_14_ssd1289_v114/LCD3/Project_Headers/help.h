/*
 * help.h
 *
 *      Author: Guillaume
 *      fichier non inclus juste pour y mettre des infos utiles 
 */

#ifndef HELP_H_
#define HELP_H_

/*
 *Data   			| Type Size     |Range (unsigned) 				|  Range (signed)
 *--------------------------------------------------------------------------
 *char  		 	| 8 bits        |0 to 255 (UINT8)				|  –128 to 127 (INT8)
 *short int 		| 16 bits 		|0 to 65535 (UINT16)	  		|  –32768 to 32767  (INT16)
 *int    			| 16 bits 		|0 to 65535 (UINT16)	  		|  –32768 to 32767 (INT16)
 *long int 		    | 32 bits 		|0 to 4294967295 (UINT32)		|  –2147483648 to 2147483647 (INT32)
 */


/*
 * operateur logique  : && || 
 */
 

//height = hauteur 
//width = largeur
 /*
 
 http://fr.wikibooks.org/wiki/Programmation_C/Classe_de_stockage = excellent site sur la programmation en C */
 

/*
fat filesystem : ordinal LFN 

letter				the long file name's...				no. of 16 byte lines/size
---------------------------------------------------------------------------------------	
a/41				length is >=001 & <=013				02 lines 032 bytes/020
b/42                length is >=014 & <=026             04 lines 064 bytes/040
c/43                length is >=027 & <=039             06 lines 096 bytes/060
d/44                length is >=040 & <=052             08 lines 128 bytes/080
e/45                length is >=053 & <=065             10 lines 160 bytes/0a0
f/46                length is >=066 & <=078             12 lines 192 bytes/0c0
g/47                length is >=079 & <=091             14 lines 224 bytes/0e0
h/48                length is >=092 & <=104             16 lines 256 bytes/100
i/49                length is >=105 & <=117             18 lines 288 bytes/120
j/4a                length is >=118 & <=130             20 lines 320 bytes/140
k/4b                length is >=131 & <=143             22 lines 352 bytes/160
l/4c                length is >=144 & <=156             24 lines 384 bytes/180
m/4d                length is >=157 & <=169             26 lines 416 bytes/1a0
n/4e                length is >=170 & <=182             28 lines 448 bytes/1c0
o/4f                length is >=183 & <=195             30 lines 480 bytes/1e0
p/50                length is >=196 & <=208             32 lines 512 bytes/200
q/51                length is >=209 & <=221             34 lines 544 bytes/220
r/52                length is >=222 & <=234             36 lines 576 bytes/240
s/53                length is >=235 & <=247             38 lines 608 bytes/260
t/54                length is >=248 & <=260             40 lines 640 bytes/280
	*/
 
#endif /* HELP_H_ */
