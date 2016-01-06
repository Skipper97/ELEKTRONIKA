/*
 * text.h
 *
 *  Author: Guillaume Sahuc 
 */

#ifndef TEXT_H_
#define TEXT_H_

typedef struct ScrollText {
	const UINT8 *text;         /* Text to render. */
   struct ScrollText *next;  /* Next line in the linked list. */
} ScrollText;


/* prototypes */
void Insert(ScrollText** List,const UINT8* Text);
void TestScroll(void);
void Scroll_Up(void);
void Scroll_Down(void);
void Scroll_Line_Up(void);
void Scroll_Line_Down(void);


#endif /* TEXT_H_ */
