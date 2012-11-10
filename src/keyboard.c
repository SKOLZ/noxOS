#include "../include/keyboard.h"
#include "../include/kernel.h"

static int shift;
static int capsLock;
static int restart = FALSE;

unsigned char keyboard[][2]= {

/*0x00*/  {NON_PRINTABLE,NON_PRINTABLE},
/*0x01*/  {NON_PRINTABLE,NON_PRINTABLE}, //Esc
/*0x02*/  {'1','!'}, 
/*0x03*/  {'2','@'}, 
/*0x04*/  {'3','#'}, 
/*0x05*/  {'4','$'}, 
/*0x06*/  {'5','%'}, 
/*0x07*/  {'6','^'}, 
/*0x08*/  {'7','&'}, 
/*0x09*/  {'8','*'}, 
/*0x0A*/  {'9','('}, 
/*0x0B*/  {'0',')'}, 
/*0x0C*/  {'-','_'}, 
/*0x0D*/  {'=','+'}, 
/*0x0E*/  {'\b','\b'},
/*0x0F*/  {NON_PRINTABLE,NON_PRINTABLE}, //Tab
/*0x10*/  {'q','Q'}, 
/*0x11*/  {'w','W'}, 
/*0x12*/  {'e','E'}, 
/*0x13*/  {'r','R'}, 
/*0x14*/  {'t','T'}, 
/*0x15*/  {'y','Y'}, 
/*0x16*/  {'u','U'}, 
/*0x17*/  {'i','I'}, 
/*0x18*/  {'o','O'}, 
/*0x19*/  {'p','P'}, 
/*0x1A*/  {'[','{'}, 
/*0x1B*/  {']','}'}, 
/*0x1C*/  {'\n','\n'},
/*0x1D*/  {NON_PRINTABLE,NON_PRINTABLE}, //Left Ctrl
/*0x1E*/  {'a','A'}, 
/*0x1F*/  {'s','S'}, 
/*0x20*/  {'d','D'}, 
/*0x21*/  {'f','F'}, 
/*0x22*/  {'g','G'}, 
/*0x23*/  {'h','H'}, 
/*0x24*/  {'j','J'}, 
/*0x25*/  {'k','K'}, 
/*0x26*/  {'l','L'}, 
/*0x27*/  {';',':'},  
/*0x28*/  {'\'','"'}, 
/*0x29*/  {'`','~'}, 
/*0x2A*/  {NON_PRINTABLE,NON_PRINTABLE}, //Left Shift
/*0x2B*/  {'\\','|'}, 
/*0x2C*/  {'z','Z'}, 
/*0x2D*/  {'x','X'}, 
/*0x2E*/  {'c','C'}, 
/*0x2F*/  {'v','V'}, 
/*0x30*/  {'b','B'}, 
/*0x31*/  {'n','N'}, 
/*0x32*/  {'m','M'}, 
/*0x33*/  {',','<'}, 
/*0x34*/  {'.','>'}, 
/*0x35*/  {'/','?'}, 
/*0x36*/  {NON_PRINTABLE,NON_PRINTABLE}, //Right Shift
/*0x37*/  {'*','*'},
/*0x38*/  {NON_PRINTABLE,NON_PRINTABLE}, //Left Alt
/*0x39*/  {' ',' '}, 
/*0x3A*/  {NON_PRINTABLE,NON_PRINTABLE}, //Caps Lock
/*0x3B*/  {NON_PRINTABLE,NON_PRINTABLE}, //F1
/*0x3C*/  {NON_PRINTABLE,NON_PRINTABLE}, //F2
/*0x3D*/  {NON_PRINTABLE,NON_PRINTABLE}, //F3
/*0x3E*/  {NON_PRINTABLE,NON_PRINTABLE}, //F4
/*0x3F*/  {NON_PRINTABLE,NON_PRINTABLE}, //F5
/*0x40*/  {NON_PRINTABLE,NON_PRINTABLE}, //F6
/*0x41*/  {NON_PRINTABLE,NON_PRINTABLE}, //F7
/*0x42*/  {NON_PRINTABLE,NON_PRINTABLE}, //F8
/*0x43*/  {NON_PRINTABLE,NON_PRINTABLE}, //F9
/*0x44*/  {NON_PRINTABLE,NON_PRINTABLE}, //F10
/*0x45*/  {NON_PRINTABLE,NON_PRINTABLE}, //Num Lock
/*0x46*/  {NON_PRINTABLE,NON_PRINTABLE}, //Scroll Lock
/*0x47*/  {NON_PRINTABLE,NON_PRINTABLE}, //Keypad 7
/*0x48*/  {NON_PRINTABLE,NON_PRINTABLE}, //Keypad 8 OR Up-Arrow
/*0x49*/  {NON_PRINTABLE,NON_PRINTABLE}, //Keypad 9
/*0x4A*/  {NON_PRINTABLE,NON_PRINTABLE}, //Keypad -
/*0x4B*/  {NON_PRINTABLE,NON_PRINTABLE}, //Keypad 4
/*0x4C*/  {NON_PRINTABLE,NON_PRINTABLE}, //Keypad 5
/*0x4D*/  {NON_PRINTABLE,NON_PRINTABLE}, //Keypad 6
/*0x4E*/  {NON_PRINTABLE,NON_PRINTABLE}, //Keypad +
/*0x4F*/  {NON_PRINTABLE,NON_PRINTABLE}, //Keypad 1
/*0x50*/  {NON_PRINTABLE,NON_PRINTABLE}, //Keypad 2 OR Down-Arrow
/*0x51*/  {NON_PRINTABLE,NON_PRINTABLE}, //Keypad 3
/*0x52*/  {NON_PRINTABLE,NON_PRINTABLE}, //Keypad 0
/*0x53*/  {NON_PRINTABLE,NON_PRINTABLE}, //Keypad . // Supr
/*0x54*/  {NON_PRINTABLE,NON_PRINTABLE}, //Sys Req (AT)
/*0x55*/  {'+','*'}, 
/*0x56*/  {'+','*'}, 
/*0x57*/  {NON_PRINTABLE,NON_PRINTABLE}, //F11
/*0x58*/  {NON_PRINTABLE,NON_PRINTABLE}}; //F12
 
void int_09(int scanCode){

	setSpecialInput(scanCode);
 	
	if( (scanCode>= 0x01 && scanCode <= 0x58 ) && keyboard[scanCode][0] != NON_PRINTABLE){ 
		if(capsLock){
			if(isLetter(scanCode)){
				if(shift){	
					addToBuffer(keyboard[scanCode][0]);
				} else {
					addToBuffer(keyboard[scanCode][1]);
				}
			} else {
				addToBuffer(keyboard[scanCode][0]);
			}
		} 
		else if(shift){
			addToBuffer(keyboard[scanCode][1]);
		}
		else{
			addToBuffer(keyboard[scanCode][0]);
		}
		keyboardInterrupt = TRUE;
	}
}

void setSpecialInput(int scanCode){
	switch(scanCode){
		case 0x2A:
		case 0x36:
			shift =1;
			break;
		case 0x2A+0x80:
		case 0x36+0x80:
			shift = 0;
			break;
		case 0x3A:
			capsLock = !capsLock;
			break;
		default:
			break;
	}
}

int isLetter(int scanCode){
	if( (scanCode>=0x10 && scanCode<=0x19) || (scanCode>=0x1E && scanCode<=0x26) || (scanCode>=0x2C && scanCode<=0x32)){
		return 1;
	}
	return 0;
}