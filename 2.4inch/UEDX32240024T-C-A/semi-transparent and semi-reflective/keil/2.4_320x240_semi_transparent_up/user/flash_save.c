/*
 8M(Byte) (128块(Block),每块64K字节,
 每块16个扇区(Sector),每个扇区4K字节
*/
#include "stdlib.h"
#include "flash_save.h"
#include "SerialFlash.h"


#define MAXDATASIZE	SAVE_MAXDATASIZE //最大可定义4096个字节


void save_flashData(uint32_t startaddr,const uint8_t* SETDATA_STRUCTINFO,uint16_t size) {
	uint8_t *save_flashdata = malloc(MAXDATASIZE);
	uint32_t writesize = 0x1000;	//4k
	uint32_t endaddr = 0;
	endaddr = startaddr+MAXDATASIZE;

	save_flashdata[MAXDATASIZE-1] = 0xFE;	//用作存储标志，表示数据有效
	for(int i = 0; i< size; i++) {
		save_flashdata[i] = SETDATA_STRUCTINFO[i];
	}

	SerialFlash_EraseSize(startaddr, writesize);	//擦除指定地址大小
	while(startaddr < endaddr) {
		if(((endaddr-startaddr) / 256) >=1) {
			SerialFlash_ProgramInfo(startaddr, save_flashdata,  256);
			startaddr+=256;
		} else {
			SerialFlash_ProgramInfo(startaddr, save_flashdata,  (endaddr-startaddr));
			startaddr+=(endaddr-startaddr);
		}
	}
	free(save_flashdata);
}

char read_flashData(uint32_t startaddr,uint8_t* SETDATA_STRUCTINFO,uint16_t size) {
	char res = 0;
	uint8_t *save_flashdata = malloc(MAXDATASIZE);
	SerialFlash_ReadData(startaddr, save_flashdata, MAXDATASIZE);
	if(save_flashdata[MAXDATASIZE-1] == 0xFE) {	//判断save_flashdata有上次开机的数据
		res = 1;
		for(int i = 0; i< size ; i++) {
			SETDATA_STRUCTINFO[i] = save_flashdata[i];
		}
	}
	free(save_flashdata);
	return res;
}

