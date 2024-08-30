#include <stdio.h>
#include "proc_cmd.h"

/*
  The test protocol
  head    cmd    len    data   tail
  2byte | 1byte| 1byte| nbyte| 1byte
  aa 55 |  xx  |  xx  |  xx  |  0a 
*/

#define CMDH0   0xAA
#define CMDH1   0x55

extern void UART_Transmit(const uint8_t* data,uint8_t len);

uint8_t dgus_cmdpro(uint8_t* data,uint8_t len){
	static uint8_t count = 0;
    if(data[0] != CMDH0) {
        printf("cmd len h0 error:%x\n",data[0]);
        return 1;
    } 
    if(data[1] != CMDH1){
        printf("cmd len h1 error:%x\n",data[1]);
        return 2;
    } 
	
    uint16_t cmd = data[2];
	uint8_t datalen = data[3];
    if(len < (datalen+4)){
		count++;
		if(count > 3) {
			count = 0;
			return len;
		}
        printf("cmd len not enough\n");
		printf("##receive data:\n");
		for(int i = 0; i < len;i++) {
			printf("%02X ",data[i]);
		}
		printf("\n");
		return 0;
    } 
	count = 0;
    printf("receive cmd :%02X ,datalen:%02X\n",cmd,datalen);

	switch(cmd) {
		case 0x00:
			printf("This is the test command.\r\n");
			break;
		case 0x01:
			break;
		default :
			//none
			break;
	}
    return (datalen+4);
}
