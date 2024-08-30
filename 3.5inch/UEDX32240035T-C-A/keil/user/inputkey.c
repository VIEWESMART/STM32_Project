#include "main.h"
#include "common.h"
#include "input.h"


extern void guiProcKey(S_INPUT_KEY *skey);

u8 readKey(void){
   if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1) == 0) return KEY_SWKEY;		//SWKEY

   return KEY_NOKEY;
}

static u8 keystatus = 0;
static u8 keyValue = KEY_NOKEY;
static unsigned short keypressTimer = 0;

void procKey(void){
    static u8 lastkey = 0;//0xff;
    u8 value = readKey();
    if(lastkey != value){
        lastkey = value;
        printf("scan key:%x\r\n",value);
		if(lastkey == KEY_NOKEY){
			S_INPUT_KEY skey;
			keystatus = KEYST_UP;
			skey.keystatus = keystatus;
			skey.keyvalue = keyValue;
			printf("proc key up:%d\r\n",keyValue);
			keyValue = KEY_NOKEY;
			keypressTimer = 0;
            guiProcKey(&skey);
			return;
		}
        if(keystatus == KEYST_UP){
			S_INPUT_KEY skey;
	        keyValue = value;
			keystatus = KEYST_DOWN;
			skey.keystatus = KEYST_DOWN;
			skey.keyvalue = keyValue;
			keypressTimer = 0;
			printf("proc key down:%d\r\n",keyValue);
            guiProcKey(&skey);
		}

    }else if(keystatus == KEYST_DOWN){
        keypressTimer++;
        if(keypressTimer == (950/10)){
            S_INPUT_KEY skey;
            skey.keystatus = KEYST_KEEP_1S;
            skey.keyvalue = keyValue;
            printf("proc key keep 1s:%d\r\n",keyValue);
            guiProcKey(&skey);
        }else if(keypressTimer == (1800/10)){
            S_INPUT_KEY skey;
            skey.keystatus = KEYST_KEEP_2S;
            skey.keyvalue = keyValue;
            printf("proc key keep 2s:%d\r\n",keyValue);
            guiProcKey(&skey); 
        }else if(keypressTimer == (2800/10)){
            S_INPUT_KEY skey;
            skey.keystatus = KEYST_KEEP_3S;
            skey.keyvalue = keyValue;
            printf("proc key keep 3s:%d\r\n",keyValue);
            guiProcKey(&skey); 
        }
    }
}


