/**********************
 kc.h
**********************/
#include "defs.h"

#ifndef _kc_
#define _kc_

#define PURPLE_TXT 0x05 // Atributo de video. Letras purpura, fondo negro
#define MAX_INT_DIGITS 5

/* Muestra la imagen de inicio */
void showSplashScreen();

/* Tiempo de espera */
void wait(int time);

/* Limpia la pantalla */
void k_clear_screen();

/* Inicializa la entrada del IDT */
void setup_IDT_entry (DESCR_INT *item, byte selector, dword offset, byte access,
			 byte cero);

int putc(char c, int fd);

int putchar(char c);

int printf(const char *fmt, ...);

void recursivePrintInt(int value);

void printFloat(float value, int precision);

void printString(char* string);

#endif
