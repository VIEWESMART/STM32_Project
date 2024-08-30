#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <stdint.h>

typedef enum{
	KEY_LIGHT1= 0,
	
	KEY_SWKEY,
	
	KEY_NOKEY = 0xff
}E_KEY;

#define KEYST_UP    0
#define KEYST_DOWN 1
#define KEYST_KEEP  2
#define KEYST_KEEP_1S   3
#define KEYST_KEEP_2S   4
#define KEYST_KEEP_3S   5
#define KEYST_KEEP_5S   6

typedef struct{
	uint8_t keystatus;
	uint8_t keyvalue;

	uint8_t ButtonSR;
	uint8_t touch_id;			//´¥Ãþ°´¼üID
}S_INPUT_KEY;

void procKey(void);


#endif 
