#include "../include/keyboard.h"
#include "../include/kernel.h"
#include "../include/shell.h"

static unsigned buffer;
static int empty=TRUE;


int addToBuffer(unsigned char c){
	if(empty){
		buffer=c;
		empty = FALSE;
		return 1;
	}else
		return 0;
}

unsigned char getFromBuffer(){
	if(!empty){
		unsigned char c=buffer;
		empty = TRUE;
		return c;
	}
	else
		return EOF;
}

void clearBuffer(){
	empty = TRUE;
}