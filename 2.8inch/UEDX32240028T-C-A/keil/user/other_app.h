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



//ҳ�涨��
#define	PAGE_DEFAULT				UI_PAGE_DEFAULT		//Ĭ��ҳ
#define	PAGE_PASSWORD				UI_PAGE_PASSWORD	//��¼ҳ
#define	PAGE_SET						UI_PAGE_SET				//����ҳ	




//�����ö��
typedef enum{
	OPERATOR_SUB = 0,
	OPERATOR_ADD,
}NUM_OPERATOR;


//�˵�ö��
typedef enum{
	MODE_HOT = 1,		//����
	MODE_COLD,			//����
	MODE_WIND,			//�·�
		
	MODE_MAXNUM,		//������
}WORK_MODE;


typedef enum{
	NUM_1 = 1,			//1
	NUM_2,				//2
	NUM_3,				//3
	NUM_4,				//4
	NUM_5,				//5
		
	NUM_MAXNUM,		//������
}NUM_MODE;


typedef enum{
	CHOOSE_1 = 1,			//1
	CHOOSE_2,				//2
	CHOOSE_3,				//3
	CHOOSE_4,				//4
	CHOOSE_5,				//5
	CHOOSE_6,				//4
	CHOOSE_7,				//5
		
	CHOOSE_MAXNUM,		//������
}CHOOSE_MODE;



//ֵ��Χ�ṹ��
typedef struct {
	uint32_t Min;
	uint32_t Max;
}VALUE_RANGE;

//������ťֵ��Ϣ
typedef struct {
	VALUE_RANGE ValRan;	//��ťֵ��Χ
	uint8_t CurVal;		//��ť��ǰֵ
}PAGE_ROTARY_INFO;


typedef struct {
	uint8_t flag;
	uint8_t Bluetooth_sign;
	uint8_t interface;
	uint8_t ope_sign;
	
	uint16_t humidity;			//ʪ��
	uint16_t temperature;		//��ȡ�¶�
	uint16_t set_temp;			//�����¶�
	
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
		
	Light_MAXNUM,		//������
}Light_MODE;


//ʱ��ṹ��
typedef struct {
	uint16_t memory_hum;			//ʪ��
	uint16_t memory_temp;			//ʪ��	
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



//����ʱ����ֵ����ģʽ����
void set_time_num_mode(uint8_t mode);
//uint8_t get_CST812T_id(uint8_t* buf);

//����������ָ��
typedef void (*ProcKey)(S_INPUT_KEY *skey);

//�ַ�ƫ��
void _char_offset(char* ch, char offset);

//��������ť��������غ���
void LoadKeyCallbackFunc(ProcKey func);
void guiProcKey(S_INPUT_KEY *skey);

//�����ֿؼ�������غ���
void user_draw_imagetext_string(imagetext_t *imagetext, const char * str);

void user_draw_imagetext_numble(imagetext_t *imagetext, uint16_t val);
void user_draw_imagetext_numble_with_offset(imagetext_t *imagetext, uint16_t val, uint8_t offset);

void user_draw_imagetext_numble2(imagetext_t *imagetext, uint16_t val);
void user_draw_imagetext_numble2_with_offset(imagetext_t *imagetext, uint16_t val, uint8_t offset);


//������������λ����
void user_draw_imagetext_numble3(imagetext_t *imagetext, uint16_t val);
void user_draw_imagetext_numble3_with_offset(imagetext_t *imagetext, uint16_t val, uint8_t offset);


void user_draw_imagetext_float(imagetext_t *imagetext, float val);
void user_draw_imagetext_value(imagetext_t *imagetext, char val);

void user_draw_imagetext_value_len(imagetext_t *imagetext, char val, char len);
//���������ְ�λ����
void user_draw_imagetext_numble8(imagetext_t *imagetext, uint16_t val);


//�������ݶ�д��غ���
uint32_t ReadFlashSaveAddr(void);
void SaveSetData_Program(const uint8_t* data, uint16_t addr, uint16_t size);
uint8_t ReadSetData_Program(uint8_t* data, uint16_t addr, uint16_t size);


extern const S_DEV otherapp;

#endif
