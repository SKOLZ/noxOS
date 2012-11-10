#include "../include/kasm.h"
#include "../include/defs.h"
#include "../include/kernel.h"
#include "../include/kc.h"
#include "../include/buffer.h"
#include "../include/keyboard.h"
#include "../include/shell.h"


DESCR_INT idt[0xA];			/* IDT de 10 entradas*/
IDTR idtr;				/* IDTR */

int cursorPosition = 0;
char *vidmem = (char* ) 0xb8000;

void int_08() {
}

size_t __write(size_t fd, const void* buffer, size_t count)
{
    switch(fd) 
    {
        case 1:
            return __writeScreen(buffer, count);
            break;
        /**Faltan los casos 0 (stdin, o sea, Standard Input), y 2 (stderr, o 
         sea, Standard Error)**/
        default :
            break;
    }
}

size_t __read(int fd, void* buffer, size_t count) {
    switch(fd) 
    {
        case STDIN:
            return __readKeyboard(buffer);
            break;
        default :
            break;
    }
}

size_t __readKeyboard(char* buffer){
	*buffer = getFromBuffer();
}
                        
size_t __writeScreen(const char* buffer, size_t count) {
    unsigned int i=0;
    while(i < count)
    {
        if (cursorPosition == 80*25*2) {
            scrollPageDown();
        }
        vidmem[cursorPosition++] = buffer[i++];
        vidmem[cursorPosition++] = PURPLE_TXT;
    }
    return count;
}

void scrollPageDown(void) {
    int i, j;
    
    for (i = 0; i < 24; i++) {
        for (j = 0; j < 80*2; j+=2) {
            vidmem[i*80*2 + j] = vidmem[i*80*2 + j + 80*2];
        }
    }
    __setCursorPosition(cursorPosition - 80*2);
    for (i = 0; i < 80; i++) {
        putchar(' ');
    }
    __setCursorPosition(cursorPosition - 80*2);
}

void __setCursorPosition(int pos) {
    cursorPosition = pos;
}

int __getCursorPosition(void) {
    return cursorPosition;
}


/**********************************************
kmain() 
Punto de entrada de cóo C.
*************************************************/

kmain() 
{

        int i,num;

/* Borra la pantalla. */ 

	k_clear_screen();


/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ0    */

        setup_IDT_entry (&idt[0x08], 0x08, (dword)&_int_08_hand, ACS_INT, 0);

/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ1    */
    
        setup_IDT_entry (&idt[0x09], 0x08, (dword)&_int_09_hand, ACS_INT, 0);
	
/* Carga de IDTR    */

	idtr.base = 0;  
	idtr.base +=(dword) &idt;
	idtr.limit = sizeof(idt)-1;
	
	_lidt (&idtr);	

	_Cli();
/* Habilito interrupcion de timer tick*/

        _mascaraPIC1(0xFC);
        _mascaraPIC2(0xFF);
        
	_Sti();
	
	k_clear_screen();
	cursorPos=0;
	showPrompt();
    Shell();
	
        while(1)
        {
        }
	
}