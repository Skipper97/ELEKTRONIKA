
#ifndef __sci_H
#define __sci_H


/* VT100 : Actions sur l'écran d'un terminal */
#define CLEARSCR        "\x1B[2J\x1B[;H"        // Clear SCReen
#define CLEAREOL        "\x1B[K"                // Clear End Of Line
#define CLEAREOS        "\x1B[J"                // Clear End Of Screen
#define CLEARLCR        "\x1B[0K"               // Clear Line Cursor Right
#define CLEARLCL        "\x1B[1K"               // Clear Line Cursor Left
#define CLEARELN        "\x1B[2K"               // Clear Entire LiNe
#define CLEARCDW        "\x1B[0J"               // Clear Curseur DoWn
#define CLEARCUP        "\x1B[1J"               // Clear Curseur UP
#define GOTOYX          "\x1B[%.2d;%.2dH"       // Goto at (y,x)

#define INSERTMOD       "\x1B[4h"               // Mode insertion
#define OVERWRITEMOD    "\x1B[4l"               // Mode de non insertion
#define DELAFCURSOR     "\x1B[K"
#define CRLF            "\r\n"                  // Retour à la ligne

/* VT100 : Actions sur le curseur */
#define CURSON          "\x1B[?25h"             // Curseur visible
#define CURSOFF         "\x1B[?25l"             // Curseur invisible

/* VT100 : Actions sur les caractères affichables */
#define NORMAL          "\x1B[0m"               // Normal
#define GRAS            "\x1B[1m"               // Gras
#define SOULIGNE       "\x1B[4m"               // Souligné
#define CLIGNOTANT        "\x1B[5m"               // Clignotant
#define INVVIDEO        "\x1B[7m"               // Inverse vidéo

/* VT100 : Couleurs */
#define CL_BLACK "\033[22;30m"			// Noir
#define CL_RED "\033[22;31m"			// Rouge
#define CL_GREEN "\033[22;32m"			// Vert
#define CL_BROWN "\033[22;33m"		// Brun
#define CL_BLUE "\033[22;34m"			// Bleu
#define CL_MAGENTA "\033[22;35m"		// Magenta
#define CL_CYAN "\033[22;36m"			// Cyan
#define CL_GRAY "\033[22;37m"			// Gris
#define CL_DARKGRAY "\033[01;30m"		// Gris foncé
#define CL_LIGHTRED "\033[01;31m"		// Rouge clair
#define CL_LIGHTGREEN "\033[01;32m"	// Vert clair
#define CL_YELLOW "\033[01;33m"		// Jaune
#define CL_LIGHTBLUE "\033[01;34m"		// Bleu clair
#define CL_LIGHTMAGENTA "\033[01;35m"	// Magenta clair
#define CL_LIGHTCYAN "\033[01;36m"		// Cyan clair
#define CL_WHITE "\033[01;37m"			// Blanc




void Init_SCI(void); //présent dans le main
void sci_tx(INT8 data);
INT8 sci_rx(void);
void sci_send_msg(INT8 msg[]);
void print_midi(INT8 midi);

#endif /* __sci_H */
