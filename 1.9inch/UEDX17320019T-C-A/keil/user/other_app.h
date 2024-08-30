/*
 * other_app.c
 *
 *  Created on: Jul 20, 2020
 *      Author: laiyj
 */
#ifndef __OTHER_APP_H__
#define __OTHER_APP_H__

#include "common.h"
#include "devmodule.h"
#include "context/guicontext.h"
#include "ui_page.h"
#include "input.h"

#include "main.h"



//页面定义
#define	PAGE_DEFAULT				UI_PAGE_DEFAULT		//默认页
#define	PAGE_PASSWORD				UI_PAGE_PASSWORD	//登录页
#define	PAGE_SET						UI_PAGE_SET				//设置页	




//运算符枚举
typedef enum{
	OPERATOR_SUB = 0,
	OPERATOR_ADD,
}NUM_OPERATOR;


//菜单枚举
typedef enum{
	MODE_HOT = 1,		//制冷
	MODE_COLD,			//制热
	MODE_WIND,			//新风
		
	MODE_MAXNUM,		//最大个数
}WORK_MODE;


typedef enum{
	NUM_1 = 1,			//1
	NUM_2,				//2
	NUM_3,				//3
	NUM_4,				//4
	NUM_5,				//5
		
	NUM_MAXNUM,		//最大个数
}NUM_MODE;


typedef enum{
	CHOOSE_1 = 1,			//1
	CHOOSE_2,				//2
	CHOOSE_3,				//3
	CHOOSE_4,				//4
	CHOOSE_5,				//5
	CHOOSE_6,				//4
	CHOOSE_7,				//5
		
	CHOOSE_MAXNUM,		//最大个数
}CHOOSE_MODE;



//值范围结构体
typedef struct {
	uint32_t Min;
	uint32_t Max;
}VALUE_RANGE;

//界面旋钮值信息
typedef struct {
	VALUE_RANGE ValRan;	//旋钮值范围
	uint8_t CurVal;		//旋钮当前值
}PAGE_ROTARY_INFO;


typedef struct {
	uint8_t flag;
	uint8_t Bluetooth_sign;
	uint8_t interface;
	uint8_t ope_sign;
	
	uint16_t humidity;			//湿度
	uint16_t temperature;		//获取温度
	uint16_t set_temp;			//设置温度
	
}VALUE_HUM_TEMP;


typedef struct {
	int SlaveAddress;
	int HumCompe;
	int TempCompe;	
	int NTC;
	int NTC_compe;
	int WorkLight;			
	int StandbyLight;		
	int VersionNumber;			
	
}VALUE_SET;


typedef enum{
	LingDu = 1,
	AnDu,
		
	Light_MAXNUM,		//最大个数
}Light_MODE;


//时间结构体
typedef struct {
	uint16_t memory_hum;			//湿度
	uint16_t memory_temp;			//湿度	
}MEMORY_HUM_TEMP;

extern uint8_t open_sign;

//main
extern VALUE_HUM_TEMP hum_temp;
extern MEMORY_HUM_TEMP memory;
extern PAGE_ROTARY_INFO home_mode;
//main01
extern PAGE_ROTARY_INFO func_mode;
extern PAGE_ROTARY_INFO func_mode2;
extern PAGE_ROTARY_INFO func_mode3;
extern PAGE_ROTARY_INFO func_mode4;
//main02
extern PAGE_ROTARY_INFO setfunc_mode;



//设置时间数值设置模式类型
void set_time_num_mode(uint8_t mode);
//uint8_t get_CST812T_id(uint8_t* buf);

//按键处理函数指针
typedef void (*ProcKey)(S_INPUT_KEY *skey);

//字符偏移
void _char_offset(char* ch, char offset);

//按键（旋钮）处理相关函数
void LoadKeyCallbackFunc(ProcKey func);
void guiProcKey(S_INPUT_KEY *skey);

//艺术字控件处理相关函数
void user_draw_imagetext_string(imagetext_t *imagetext, const char * str);

void user_draw_imagetext_numble(imagetext_t *imagetext, uint16_t val);
void user_draw_imagetext_numble_with_offset(imagetext_t *imagetext, uint16_t val, uint8_t offset);

void user_draw_imagetext_numble2(imagetext_t *imagetext, uint16_t val);
void user_draw_imagetext_numble2_with_offset(imagetext_t *imagetext, uint16_t val, uint8_t offset);


//设置艺术字三位数字
void user_draw_imagetext_numble3(imagetext_t *imagetext, uint16_t val);
void user_draw_imagetext_numble3_with_offset(imagetext_t *imagetext, uint16_t val, uint8_t offset);


void user_draw_imagetext_float(imagetext_t *imagetext, float val);
void user_draw_imagetext_value(imagetext_t *imagetext, char val);

void user_draw_imagetext_value_len(imagetext_t *imagetext, char val, char len);
//设置艺术字八位数字
void user_draw_imagetext_numble8(imagetext_t *imagetext, uint16_t val);


//保存数据读写相关函数
uint32_t ReadFlashSaveAddr(void);
void SaveSetData_Program(const uint8_t* data, uint16_t addr, uint16_t size);
uint8_t ReadSetData_Program(uint8_t* data, uint16_t addr, uint16_t size);


extern const S_DEV otherapp;

#endif
