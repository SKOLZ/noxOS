#include "../include/keyboard.h"
#include "../include/buffer.h"
#include "../include/kernel.h"
#include "../include/shell.h"

int bufferAmount = 0;
unsigned char shellBuffer[BUFFER_SIZE];
extern int keyboardInterrupt = FALSE;

void showPrompt() {
	printf("nox:~$> ");
}

void Shell(){
   while(1){
	 if(keyboardInterrupt){
		 keyBoardInterrupt = FALSE;
		 unsigned char c;
		 __read(STDIN, &c, 1);
		 if( c == BREAKLINE || bufferAmount == MAX_BUFFER){
			 putc(STDOUT,BREAKLINE);
			 checkCommands();
			 cleanShellBuffer();
			 showPrompt();
		 }
		 else if(c == BACKSPACE){
			 if(bufferAmount>0){
					write(&c,1,STDOUT);
					bufferAmount--;
			 }
		 } else {
			shellBuffer[bufferAmount] = c;
			bufferAmount++;
			putc(STDOUT,c);
		 }
	 }
  } 
}

void checkCommands() {
	shellBuffer[bufferAmount] = '\0';

	if(strcmp(&shellBuffer,"aboutUs")){
		aboutUs();
	}
	else if(strcmp(&shellBuffer, "clear")) {
		clear_screen();
		cursorPos=0;
	}
	else if(strcmp(&shellBuffer,"commands")){
		commands();
	}
	else if(strcmp(&shellBuffer,"help")){
		help();
	}
	else if(strcmp(&shellBuffer,"infoIDT")){
		infoIDT();	
	}
	else if(strcmp(&shellBuffer,"addIDT")){
		addIDT();
	}
	else if(strcmp(&shellBuffer, "removeIDT")){
		removeIDT();
	}
	else if( !strcmp(&stringBuffer,"")){
		printf("%s: invalid command\n",shellBuffer);
	}
}

void cleanShellBuffer(){
	bufferAmount = 0;
}