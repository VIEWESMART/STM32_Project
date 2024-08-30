/*
 * other_app.c
 *
 *  Created on: Jul 20, 2020
 *      Author: laiyj
 */
#include "main.h"
#include "other_app.h"
#include "flash_save.h"
#include "SerialFlash.h"


//字符偏移
void _char_offset(char* ch, char offset) {
	while((*ch!='\0')&&(ch!=NULL)) {
		*ch++ += offset;
	}
}

/*******************************************************************************/
/******************************按键(旋钮)处理*****************************************/
static ProcKey prockey = NULL;
//加载按键处理函数
void LoadKeyCallbackFunc(ProcKey func) {
	prockey = func;
}
//按键处理
void guiProcKey(S_INPUT_KEY *skey) {	
	static uint8_t last_state = KEYST_DOWN;
	static uint8_t record_page = 255;
	
	//记录按键状态，不可删除
	if(skey->keystatus == KEYST_DOWN) {
		last_state = KEYST_DOWN;
		record_page = gui_context_get_current_page();
		//printf("proc key down \r\n"); 
	} else if(skey->keystatus == KEYST_UP) {
		if(gui_context_get_current_page()!=record_page){
				if(last_state == KEYST_KEEP)return;
		}
		last_state = KEYST_UP;
		//printf("proc key up \r\n"); 
	} else if((skey->keystatus == KEYST_KEEP_1S) ||\
			(skey->keystatus == KEYST_KEEP_2S) || \
			(skey->keystatus == KEYST_KEEP_3S)){
		last_state = KEYST_KEEP;
		//printf("proc key KEEP\n\n");
	} 
	
	//按键处理
	if(prockey != NULL) {
		prockey(skey);
	}
}


/*******************************************************************************/
/***************************艺术字控件显示**************************************/
//设置艺术字字符串
void user_draw_imagetext_string(imagetext_t *imagetext, const char * str) {
	imagetext_set_text(imagetext,str);
}
//设置艺术字一位数字
void user_draw_imagetext_numble(imagetext_t *imagetext, uint16_t val) {
	char buff[5];
	sprintf(buff,"%d",val);
	imagetext_set_text(imagetext,(const char *)buff);
}

//设置艺术字偏移的一位数字
void user_draw_imagetext_numble_with_offset(imagetext_t *imagetext, uint16_t val, uint8_t offset) 
{
	char buff[5];
	sprintf(buff,"%d",val);
	_char_offset(buff, offset);
	imagetext_set_text(imagetext,(const char *)buff);
}


//设置艺术字两位数字
void user_draw_imagetext_numble2(imagetext_t *imagetext, uint16_t val) {
	char buff[5];
	sprintf(buff,"%02d",val);
	imagetext_set_text(imagetext,(const char *)buff);
}


//设置艺术字偏移的两位数字
void user_draw_imagetext_numble2_with_offset(imagetext_t *imagetext, uint16_t val, uint8_t offset) 
{
	char buff[5];
	sprintf(buff,"%02d",val);
	_char_offset(buff, offset);
	imagetext_set_text(imagetext,(const char *)buff);
}


//设置艺术字三位数字
void user_draw_imagetext_numble3(imagetext_t *imagetext, uint16_t val) {
	char buff[5];
	sprintf(buff,"%03d",val);
	imagetext_set_text(imagetext,(const char *)buff);
}


//设置艺术字八位数字
void user_draw_imagetext_numble8(imagetext_t *imagetext, uint16_t val) {
	char buff[9];
	if(val/10 == 0){
		sprintf(buff,"%07d",0);
		sprintf(buff+7,"%d",val);
	}else{
		sprintf(buff,"%06d",0);
		sprintf(buff+6,"%02d",val);
	}
	
	imagetext_set_text(imagetext,(const char *)buff);
}


//设置艺术字偏移的三位数字
void user_draw_imagetext_numble3_with_offset(imagetext_t *imagetext, uint16_t val, uint8_t offset) 
{
	char buff[5];
	sprintf(buff,"%03d",val);
	_char_offset(buff, offset);
	imagetext_set_text(imagetext,(const char *)buff);
}


//设置艺术字浮点数
void user_draw_imagetext_float(imagetext_t *imagetext, float val) {
	char buff[8];
	sprintf(buff,"%.1f",val);
	imagetext_set_text(imagetext,(const char *)buff);
}
//设置艺术字值
void user_draw_imagetext_value(imagetext_t *imagetext, char val) {
//注意：val值范围为 1 - 127
	char buff[3];
	buff[0] = val;
	buff[1] = '\0';
	imagetext_set_text(imagetext,(const char *)buff);
}

//设置len个艺术字值
void user_draw_imagetext_value_len(imagetext_t *imagetext, char val, char len) {
//注意：val值范围为 1 - 127
	char buff[len+1];
	uint8_t i;
	for(i=0;i<len;i++)
		buff[i] = val;
	
	buff[len] = '\0';
	imagetext_set_text(imagetext,(const char *)buff);
}

/*******************************************************************************/

/*******************************************************************************/
/**************************设置参数保存/读取**************************************/
//保存设置数据大小，应<=SAVE_MAXDATASIZE-1
#define SETSAVEDATASZIE	60	
//定义一段保存数据的内存
uint8_t save_data_memory[SETSAVEDATASZIE] = {0};
//读取保存Flash地址
uint32_t ReadFlashSaveAddr(void) {
	//读取Flash型号,依据最低1字节判断Flash内存大小
	//保留最后4K大小，作为存储参数地址
	uint32_t flash_size = 0x1FF000; //2M
	uint8_t flash_id = (uint8_t)readDeviceId();
	switch(flash_id) {
		case 0x15: //25q16 //2M
			flash_size = 0x1FF000;
			break;
		case 0x16: //25q32 //4M
			flash_size = 0x3FF000;
			break;
		case 0x17: //25q64 //8M
			flash_size = 0x7FF000;
			break;
		case 0x18: //25q128 //16M
			flash_size = 0xFFF000;
			break;
		case 0x19: //25q256 //32M
			flash_size = 0x1FFF000;
			break;
		default : 
			break;
	}
	return flash_size;
}
/**
* 函数名：保存设置参数
* 参  数：data: 指针，指向需保存的数据地址
* 		  addr: 内存段save_data_memory的开始位置
*		  size: 数据大小
* 返  回：无
*/
void SaveSetData_Program(const uint8_t* data, uint16_t addr, uint16_t size) {
	if((addr+size) > SETSAVEDATASZIE) return;
	uint32_t startaddr = ReadFlashSaveAddr();
	for(int i = 0; i < size; i++) {
		save_data_memory[addr+i] = data[i];
	}
	save_flashData(startaddr,(const uint8_t*)save_data_memory,SETSAVEDATASZIE);
}
/**
* 函数名：读取设置参数
* 参  数：data: 指针，指向需保存数据地址
* 		  addr: 内存段save_data_memory的开始位置
*		  size: 数据大小
* 返  回：1 成功，0 失败
*/
uint8_t ReadSetData_Program(uint8_t* data, uint16_t addr, uint16_t size) {
	if((addr+size) > SETSAVEDATASZIE) return 0;
	uint32_t startaddr = ReadFlashSaveAddr();
	if(read_flashData(startaddr,save_data_memory,SETSAVEDATASZIE) != 0) {
		for(int i = 0; i < size; i++) {
			data[i] = save_data_memory[addr+i];
		}
		return 1;
	}
	return 0;
}
/*******************************************************************************/


void init_other(void){
	
}
void procOtherMsg(int msgtype,int p1,int p2) {
	switch(msgtype) {
		case DEVMSG_TIMER10ms:
			//按键检测处理
			procKey(); 
			break;
		case DEVMSG_TIMER50ms:
			
			break;
		case DEVMSG_TIMER100ms:
			
			break;
		default :
			break;
	}
}

const S_DEV otherapp = {
		init_other,
		NULL,
		NULL,
		NULL,
		procOtherMsg
};



