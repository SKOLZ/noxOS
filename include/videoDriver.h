//
//  videoDriver.h
//  
//
//  Created by Germán Rodrigo Romarión on 05/11/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//
#include "../include/kernel.h"
#include "../include/kc.h"
#ifndef _videoDriver_h
#define _videoDriver_h

#define VIDEO_ROWS 25
#define VIDEO_COLUMNS 80


size_t putc(char c, int fd);

size_t putchar(char c);

void clear_vitualScreen();

size_t writeVirualScreen(const char* buffer, size_t count);

void setVirtualCursorPosition(size_t row, size_t column);

void setVirtualCursorRowPosition(int row);

void setVirtualCursorColumnPosition(int column);

void scrollVirtualPageDown(void);

size_t getVirtualCursorRowPosition(void);

size_t getVirtualCursorColumnPosition(void);

void checkVirtualCursorPosition(void);

void removeVirtualCursor();

void clearVirtualLine(size_t row);

void backSpace(void);

void breakLine(void);

void tabulate(void);

void refreshKernelVideo();

#endif