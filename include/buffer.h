#ifndef _BUFFER_
#define _BUFFER_

#define BUFFER_SIZE 255
#define EOF -1

int addToBuffer(unsigned char c);

unsigned char getFromBuffer();

void clearBuffer();

#endif