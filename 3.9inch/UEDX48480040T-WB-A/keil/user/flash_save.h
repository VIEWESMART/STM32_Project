#ifndef _FLASH_SAVE_H
#define _FLASH_SAVE_H
#include "main.h"


#define SAVE_MAXDATASIZE	64 //���ɶ���4096���ֽ�

void save_flashData(uint32_t startaddr,const uint8_t* SETDATA_STRUCTINFO,uint16_t size);
char read_flashData(uint32_t startaddr,uint8_t* SETDATA_STRUCTINFO,uint16_t size);

#endif
