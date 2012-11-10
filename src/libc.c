#include "../include/kc.h"
#include "../include/kernel.h"
#include <stdarg.h>


/***************************************************************
*k_clear_screen
*
* Borra la pantalla en modo texto color.
****************************************************************/

void k_clear_screen() 
{
	unsigned int i=0;
	while(i < (80*25))
	{
		putchar(' ');
        i++;
	}
    __setCursorPosition(0);
}

int putc(char c, int fd) {
    __write(fd, &c, 1);
}

/**int getc(void* ) {
    
}**/

int putchar(char c) {
    return putc(c, STDOUT);
}

int printf(const char *fmt, ...)
{
	const char *p;
    va_list varList; /** Is a special pointer type which allows to manipulate a
                   variable-length argument list **/
    int i;
    char *s;
    
    va_start(varList, fmt); /** va_start() begins the processing of an argument 
                          list **/
    
	for(p = fmt; *p != '\0'; p++)
    {
		if(*p != '%')
			putchar(*p);
		else	{
            p++;
            switch (*p) {
                case 'c':
                    putchar(va_arg(varList, int));
                    break;
                case 'd':
                    recursivePrintInt(va_arg(varList, int));
                    break;
                case 'f':
                    printFloat(va_arg(varList, double), FLOAT_MAX_PRECISION);
                case 's':
                    printString(va_arg(varList, char*));
                    break;
                default:
                    break;
            }
        }
    }
}

void printString(char* string) {
    
    const char *p;
    for (p = string; *p != '\0'; p++) {
        putchar(*p);
    }
    return;
}

void recursivePrintInt(int value) {
    if (value/10 == 0) {
        putchar('0' + value);
        return;
    }
    recursivePrintInt(value/10);
    putchar('0' + value%10);
    return;
}
                                      
void printFloat(float value, int precision)
{
    int floatToInt;
    if (value<0) {
        putchar('-');
        value =- value;
    }
    floatToInt = value;
    recursivePrintInt(floatToInt);
    putchar('.');
    while (precision--) {
        value = (value - floatToInt) * 10;
        floatToInt = value;
        putchar('0'+floatToInt);
    }
}



/***************************************************************
*setup_IDT_entry
* Inicializa un descriptor de la IDT
*
*Recibe: Puntero a elemento de la IDT
*	 Selector a cargar en el descriptor de interrupcion
*	 Puntero a rutina de atencion de interrupcion	
*	 Derechos de acceso del segmento
*	 Cero
****************************************************************/

void setup_IDT_entry (DESCR_INT *item, byte selector, dword offset, byte access,
			 byte cero) {
  item->selector = selector;
  item->offset_l = offset & 0xFFFF;
  item->offset_h = offset >> 16;
  item->access = access;
  item->cero = cero;
}
