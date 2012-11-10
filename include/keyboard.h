#ifndef _keyboard_
#define _keyboard_

#define NON_PRINTABLE    0
#define FALSE 0
#define TRUE 1

void int_09(int scanCode);

void setSpecialInput(int scanCode);

int isLetter(int scanCode);

#endif