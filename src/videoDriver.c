//
//  videoDriver.c
//  
//
//  Created by Germán Rodrigo Romarión on 05/11/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "../include/videoDriver.h"
#include "../include/kernel.h"

int virtualCursorRowPosition = 0;
int virtualCursorColumnPosition = 0;
char video[VIDEO_ROWS][VIDEO_COLUMNS];

void clear_virtualScreen() {
    int i;
    for (i = 0; i < VIDEO_ROWS; i++) {
        clearVirtualLine(i);
    }
    setVirtualCursorPosition(0, 0);
}

size_t putc(char c, int fd) {
    switch (fd) {
        case 1:
            video[virtualCursorRowPosition][virtualCursorColumnPosition++] = c;
            checkVirtualCursorPosition();
            break;
        default:
            break;
    }
}

size_t putchar(char c) {
    switch (c) {
        case '\n':
            breakLine();
            return 0;
        case '\b':
            backSpace();
            return 0;
        case '\t':
            tabulate();
            return 0;
        default:
            return putc(c, STDOUT);
            break;
    }
}

void backSpace(void) {
    setVirtualCursorColumnPosition(getVirtualCursorColumnPosition() - 1);
    putchar(' ');
    setVirtualCursorColumnPosition(getVirtualCursorColumnPosition() - 1);
    return;
}

void breakLine(void) {
    if (getVirtualCursorRowPosition() < VIDEO_ROWS - 1) {
        setVirtualCursorRowPosition(getVirtualCursorRowPosition() + 1);
        setVirtualCursorColumnPosition(0);
    } else {
        scrollVirtualPageDown();
    }
}

void tabulate(void) {
    setVirtualCursorColumnPosition(getVirtualCursorColumnPosition() + 8);
    checkVirtualCursorPosition();
}

void checkVirtualCursorPosition(void) {
    if (virtualCursorColumnPosition >= 80) {
        virtualCursorColumnPosition %= VIDEO_COLUMNS;
        if (virtualCursorRowPosition < VIDEO_ROWS - 1) {
            virtualCursorRowPosition++;
        } else {
            scrollVirtualPageDown();
        }
    }
}

void scrollVirtualPageDown(void) {
    int i, j;
    
    for (i = 0; i < VIDEO_ROWS - 1; i++) {
        for (j = 0; j < VIDEO_COLUMNS; j++) {
            video[i][j] = video[i+1][j];
        }
    }
    clearVirtualLine(VIDEO_ROWS - 1);
}

void setVirtualCursorPosition(size_t row, size_t column) {
    setVirtualCursorRowPosition(row);
    setVirtualCursorColumnPosition(column);
}

void setVirtualCursorRowPosition(int row) {
    virtualCursorRowPosition = row;
}

void setVirtualCursorColumnPosition(int column) {
    virtualCursorColumnPosition = column;
}

int getVirtualCursorRowPosition(void) {
    return virtualCursorRowPosition;
}

int getVirtualCursorColumnPosition(void) {
    return virtualCursorColumnPosition;
}

void clearVirtualLine(size_t row) {
    int j;
    setVirtualCursorRowPosition(row);
    setVirtualCursorColumnPosition(j);
    
    for (j = 0; j < VIDEO_COLUMNS; j++) {
        video[row][j] = ' ';
    }
    setVirtualCursorColumnPosition(0);
}

void refreshKernelVideo(void) {
    int i;
    for (i = 0; i < VIDEO_ROWS; i++) {
        __write(1, video[i], VIDEO_COLUMNS);
    }
    setCursorPosition(0);
}