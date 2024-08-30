/*
 * SDL_video.c
 *
 *  Created on: Nov 29, 2020
 *      Author: ZKSWE Develop Team
 */
 
#include "main.h"
#include "graphics/video.h"

#if 1
//RST			
#define RST_LOW()	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_RESET)		
#define RST_HI()	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET)
//BL
#define LED_OFF() 	LCD_BL_OFF()
#define LED_ON() 	LCD_BL_ON()
//RS //D/C
#define SET_CMD()	(GPIOB->BRR = GPIO_PIN_13)
#define SET_DATA()	(GPIOB->BSRR = GPIO_PIN_13)
//CS
#define CLR_CS()	(GPIOB->BRR = GPIO_PIN_12)
#define SET_CS()	(GPIOB->BSRR = GPIO_PIN_12)


#define SWAP(x) (x>>8)|(x<<8)

#define TFT_SPI_Write_Byte(num)		{\
	while(((SPI2->SR) & (SPI_FLAG_TXE)) != (SPI_FLAG_TXE));\
	 *((__IO uint8_t*)&SPI2->DR) = num;\
	 while(((SPI2->SR) & SPI_FLAG_BSY) != RESET);}


#define LCD_WritemutileData16_fast(data)  {\
	while(((SPI2->SR) & (SPI_FLAG_TXE)) != (SPI_FLAG_TXE));\
	SPI2->DR =  SWAP(data);\
}

void LCD_startWriteMutileData(){
	SET_DATA();
	CLR_CS();
}

void LCD_WritemutileData(uint8_t data){
	TFT_SPI_Write_Byte(data);
}

void LCD_endWriteMutileData(){
	SET_CS();
}

void LCD_WR_REG(uint8_t CMD)
{
	CLR_CS();
	SET_CMD();
	TFT_SPI_Write_Byte(CMD);
	SET_CS();
}

void LCD_WR_DATA(uint8_t DATA)
{
	CLR_CS();
	SET_DATA();
	TFT_SPI_Write_Byte(DATA);
	SET_CS();
}
void LCD_WR_DATA16(uint16_t DATA)
{
	SET_DATA();
	CLR_CS();

	//TFT_SPI_Write_16(DATA);
	TFT_SPI_Write_Byte(DATA>>8);
	TFT_SPI_Write_Byte(DATA&0xff);
	SET_CS();
}
#define LCD_ILI9341_CMD 		LCD_WR_REG
#define LCD_ILI9341_Parameter 	LCD_WR_DATA
#define delay_ms 				HAL_Delay
#define Delay					HAL_Delay
#define WriteData				LCD_WR_DATA
#define WriteComm 				LCD_WR_REG

#define LCD_WR_DATA8 				LCD_WR_DATA
#define Lcd_WriteIndex 				LCD_WR_REG
#define Lcd_WriteData_8Bit 			LCD_WR_DATA
#define vTaskDelay					HAL_Delay

#define LCD_DIR 	0	

#if UE019QV_AB40_A001A		//170x320
#define LCD_width 	320
#define LCD_height	240
#endif

#if UE035HV_RB40_A118_ST7796S		//480x320
#define LCD_width 	480
#define LCD_height	320
#endif

#if UE039HV_RB40_A009A_4SPI_3041A			//480x272
#define LCD_width 	480
#define LCD_height	272
#endif

#if	UE024QV_RB40_A038A_9307					//320x240
#define LCD_width 	320
#define LCD_height	240
#endif

#define LCD_wramcmd 0X2C
#define LCD_setxcmd 0X2A
#define LCD_setycmd 0X2B

void LCD_Clear(uint16_t color)
{
	extern void LCD_Fill(uint16_t x,uint16_t y,uint16_t x1,uint16_t y1,uint16_t color);
	if(LCD_DIR == 0)
		LCD_Fill(0,0,LCD_width,LCD_height,color);
	else
		LCD_Fill(0,0,LCD_height,LCD_width,color);
}  

static uint8_t clear_sign = 0;
bool video_init() {
	extern SPI_HandleTypeDef hspi2;
	__HAL_SPI_ENABLE(&hspi2);

  LED_OFF();
	
	RST_LOW();
	delay_ms(20);
	RST_HI();
	delay_ms(20);

#if UE019QV_AB40_A001A
	WriteComm(0xfe);
	WriteComm(0xef);
	WriteComm(0x36);
	WriteData(0x28); 	//ºáÆÁ
	WriteComm(0x3a);
	WriteData(0x05);
	//------------------9307
	//=============		
	WriteComm(0x20);

	WriteComm(0x85);	
	WriteData(0xc0);	
	WriteComm(0x86);	
	WriteData(0x98);
	WriteComm(0x88);
	WriteData(0x02);
	WriteComm(0x89);	
	WriteData(0x33);
	WriteComm(0x8b);	
	WriteData(0x80);	
	WriteComm(0x8d);	
	WriteData(0x3b);
	WriteComm(0x8e);	 
	WriteData(0x0f);	

	WriteComm(0xff);
	WriteData(0x62);

	WriteComm(0x99);	
	WriteData(0x3e);
	WriteComm(0x9d);	
	WriteData(0x4b);
	WriteComm(0x98);	
	WriteData(0x3e);
	WriteComm(0x9c);	
	WriteData(0x4b);

	WriteComm(0xbe);	
	WriteData(0x41);

	WriteComm(0x9b);
	WriteData(0x47);
	WriteComm(0xe1);
	WriteData(0x04);
	WriteData(0x05);

	WriteComm(0xe8);
	WriteData(0x13);
	WriteData(0x40);

	WriteComm(0xec);
	WriteData(0x33);
	WriteData(0x02);
	WriteData(0xff);
	WriteComm(0xed);
	WriteData(0x19);
	WriteData(0x09); 

	WriteComm(0xc9);	
	WriteData(0x05);
	WriteComm(0xc3);	
	WriteData(0x14);
	WriteComm(0xc4);	
	WriteData(0x10);

	WriteComm(0xF0);
	WriteData(0x87);
	WriteData(0x0a);
	WriteData(0x0a);
	WriteData(0x09);
	WriteData(0x05);
	WriteData(0x29);

	WriteComm(0xF1);
	WriteData(0x41);
	WriteData(0x6d);
	WriteData(0x53);
	WriteData(0x2f);
	WriteData(0x31);
	WriteData(0x3a);

	WriteComm(0xF2);
	WriteData(0x46);
	WriteData(0x05);
	WriteData(0x07);
	WriteData(0x08);
	WriteData(0x06);
	WriteData(0x2e);

	WriteComm(0xF3);
	WriteData(0x47);
	WriteData(0xd1);
	WriteData(0x88);
	WriteData(0x30);
	WriteData(0x31);
	WriteData(0x6a); 

	WriteComm(0x11);
	delay_ms(120);
	WriteComm(0x29);
	WriteComm(0x2c);
#endif
//
#if UE035HV_RB40_A118_ST7796S

#if ED_3_5
WriteComm( 0x11);     

Delay(120);                //ms

WriteComm( 0xF0);     
WriteData( 0xC3);   

WriteComm( 0xF0);     
WriteData( 0x96);   

WriteComm( 0x36);     
WriteData( 0x28);   

WriteComm( 0x3A);     
WriteData( 0x55);   

WriteComm( 0xB4);     //1-dot Inversion
WriteData( 0x01);   //00 ÁÐ·­

WriteComm( 0xB7);     
WriteData( 0xC6);

WriteComm( 0xC0);     
WriteData( 0x80);   
WriteData( 0x04); 

WriteComm( 0xC1);     
WriteData( 0x13);  //VOP=4.5V

WriteComm( 0xC2);     
WriteData( 0xA7);   

WriteComm( 0xC5);     
WriteData( 0x16);   //17ÁÐ·­×î¼Ñ

WriteComm( 0xE8);     
WriteData( 0x40);   
WriteData( 0x8a);   
WriteData( 0x00);   
WriteData( 0x00);   
WriteData( 0x29);   
WriteData( 0x19);   
WriteData( 0xA5);   
WriteData( 0x33);  
 
WriteComm( 0xE0);
WriteData( 0xF0);
WriteData( 0x19);
WriteData( 0x20);
WriteData( 0x10);
WriteData( 0x11);
WriteData( 0x0A);
WriteData( 0x46);
WriteData( 0x44);
WriteData( 0x57);
WriteData( 0x09);
WriteData( 0x1A);
WriteData( 0x1B);
WriteData( 0x2A);
WriteData( 0x2D);

WriteComm( 0xE1);
WriteData( 0xF0);
WriteData( 0x12);
WriteData( 0x1A);
WriteData( 0x0A);
WriteData( 0x0C);
WriteData( 0x18);
WriteData( 0x45);
WriteData( 0x44);
WriteData( 0x56);
WriteData( 0x3F);
WriteData( 0x15);
WriteData( 0x11);
WriteData( 0x24);
WriteData( 0x26);

WriteComm( 0xF0);     
WriteData( 0x3C);   

WriteComm( 0xF0);     
WriteData( 0x69);   

WriteComm( 0x21); 

WriteComm( 0x29);     
Delay(50); 

WriteComm( 0x2C); 


#else
WriteComm( 0x11);     
Delay(120);                //Delay 120ms
WriteComm( 0x36);     // Memory Data Access Control MY,MX~~
WriteData( 0x28);   	//ºáÆÁ

WriteComm( 0x3A);     
WriteData( 0x55);   //WriteData( 0x66);

WriteComm( 0xF0);     // Command Set Control
WriteData( 0xC3);   

WriteComm( 0xF0);     
WriteData( 0x96);   

WriteComm( 0xB4);     
WriteData( 0x01);   

WriteComm( 0xB7);     
WriteData( 0xC6);   

WriteComm( 0xB9);     
WriteData( 0x02);
WriteData( 0xE0);

WriteComm( 0xC0);     
WriteData( 0x80);   
WriteData( 0x45);   

WriteComm( 0xC1);     
WriteData( 0x13);   //18  //00

WriteComm( 0xC2);     
WriteData( 0xA7);   

WriteComm( 0xC5);     
WriteData( 0x0A);   

WriteComm( 0xE8);     
WriteData( 0x40);
WriteData( 0x8A);
WriteData( 0x00);
WriteData( 0x00);
WriteData( 0x29);
WriteData( 0x19);
WriteData( 0xA5);
WriteData( 0x33);

WriteComm( 0xE0);
WriteData( 0xD0);
WriteData( 0x08);
WriteData( 0x0F);
WriteData( 0x06);
WriteData( 0x06);
WriteData( 0x33);
WriteData( 0x30);
WriteData( 0x33);
WriteData( 0x47);
WriteData( 0x17);
WriteData( 0x13);
WriteData( 0x13);
WriteData( 0x2B);
WriteData( 0x31);

WriteComm( 0xE1);
WriteData( 0xD0);
WriteData( 0x0A);
WriteData( 0x11);
WriteData( 0x0B);
WriteData( 0x09);
WriteData( 0x07);
WriteData( 0x2F);
WriteData( 0x33);
WriteData( 0x47);
WriteData( 0x38);
WriteData( 0x15);
WriteData( 0x16);
WriteData( 0x2C);
WriteData( 0x32);
 
WriteComm( 0xF0);     
WriteData( 0x3C);   

WriteComm( 0xF0);     
WriteData( 0x69);   

Delay(120);                
WriteComm( 0x21);     
WriteComm( 0x29);
#endif

#endif

//
#if	UE039HV_RB40_A009A_4SPI_3041A	
//---------Start Initial Code ------//
//WriteComm(0xff);
//WriteData(0xa5);
//WriteComm(0xE7); //TE_output_en
//WriteData(0x10);
//WriteComm(0x35); //TE_ interface_en
//WriteData(0x00);//01
//WriteComm(0x36); 
//WriteData(0x00);//c0
//	
//WriteComm(0x3A); 
//WriteData(0x01);//01---565/00---666

//WriteComm(0x40); 
//WriteData(0x01);//01:IPS/00:TN
//WriteComm(0x41); 
//WriteData(0x03);//01--8bit//03--16bit
//WriteComm(0x44); //VBP 
//WriteData(0x15); 

//WriteComm(0x45); //VFP 
//WriteData(0x15); 
//WriteComm(0x7d);//vdds_trim[2:0]
//WriteData(0x03);
// 
//WriteComm(0xc1);//avdd_clp_en avdd_clp[1:0] avcl_clp_en avcl_clp[1:0]
//WriteData(0xbb);//0xbb 88 a2
//WriteComm(0xc2);//vgl_clp_en vgl_clp[2:0]
//WriteData(0x05);
//WriteComm(0xc3);//vgl_clp_en vgl_clp[2:0]
//WriteData(0x10);
//WriteComm(0xc6);//avdd_ratio_sel avcl_ratio_sel vgh_ratio_sel[1:0] vgl_ratio_sel[1:0]
//WriteData(0x3e); 
//WriteComm(0xc7);//mv_clk_sel[1:0] avdd_clk_sel[1:0] avcl_clk_sel[1:0]
//WriteData(0x25); 
//WriteComm(0xc8);// VGL_CLK_sel
//WriteData(0x21); 
//WriteComm(0x7a);// user_vgsp
//WriteData(0x51); //58
//WriteComm(0x6f);// user_gvdd
//WriteData(0x49); //4F 
//WriteComm(0x78);// user_gvcl
//WriteData(0x57); //70 
//WriteComm(0xc9);
//WriteData(0x00); 
//WriteComm(0x67); 
//WriteData(0x11);
////gate_ed
//WriteComm(0x51);//gate_st_o[7:0]
//WriteData(0x0a);
//WriteComm(0x52);//gate_ed_o[7:0]
//WriteData(0x7D); //7A
//WriteComm(0x53);//gate_st_e[7:0]
//WriteData(0x0a);
//WriteComm(0x54);//gate_ed_e[7:0]
//WriteData(0x7D); //7A
////sorce 
//WriteComm(0x46);//fsm_hbp_o[5:0]
//WriteData(0x0a);
// 
//WriteComm(0x47);//fsm_hfp_o[5:0]
//WriteData(0x2a);
//WriteComm(0x48);//fsm_hbp_e[5:0]
//WriteData(0x0a);
//WriteComm(0x49);//fsm_hfp_e[5:0]
//WriteData(0x1a);
//WriteComm(0x44); //VBP 
//WriteData(0x15); 
//WriteComm(0x45); //VFP 
//WriteData(0x15); 
//WriteComm(0x73);
//WriteData(0x08);
//WriteComm(0x74);
//WriteData(0x10); //0A

//WriteComm(0x56);//src_ld_wd[1:0] src_ld_st[5:0]
//WriteData(0x43);
//WriteComm(0x57);//pn_cs_en src_cs_st[5:0]
//WriteData(0x42);
//WriteComm(0x58);//src_cs_p_wd[6:0]
//WriteData(0x3c);
//WriteComm(0x59);//src_cs_n_wd[6:0]
//WriteData(0x64); 
//WriteComm(0x5a);//src_pchg_st_o[6:0]
//WriteData(0x41); 
//WriteComm(0x5b);//src_pchg_wd_o[6:0]
//WriteData(0x3C); 
//WriteComm(0x5c);//src_pchg_st_e[6:0]
//WriteData(0x02);
//WriteComm(0x5d);//src_pchg_wd_e[6:0]
//WriteData(0x3c);
//WriteComm(0x5e);//src_pol_sw[7:0]
//WriteData(0x1f);
//WriteComm(0x60);//src_op_st_o[7:0]
//WriteData(0x80);

//WriteComm(0x61);//src_op_st_e[7:0]
//WriteData(0x3f);
//WriteComm(0x62);//src_op_ed_o[9:8] src_op_ed_e[9:8]
//WriteData(0x21);
//WriteComm(0x63);//src_op_ed_o[7:0]
//WriteData(0x07);
//WriteComm(0x64);//src_op_ed_e[7:0]
//WriteData(0xe0);
//WriteComm(0x65);//chopper
//WriteData(0x02);
//WriteComm(0xca); //avdd_mux_st_o[7:0]
//WriteData(0x20);
//WriteComm(0xcb); //avdd_mux_ed_o[7:0]
//WriteData(0x52);
//WriteComm(0xcc); //avdd_mux_st_e[7:0]
//WriteData(0x10);
//WriteComm(0xcD); //avdd_mux_ed_e[7:0]
//WriteData(0x42);
//WriteComm(0xD0); //avcl_mux_st_o[7:0]
//WriteData(0x20);
//WriteComm(0xD1); //avcl_mux_ed_o[7:0]
//WriteData(0x52);
//WriteComm(0xD2); //avcl_mux_st_e[7:0]
//WriteData(0x10);
//WriteComm(0xD3); //avcl_mux_ed_e[7:0]
//WriteData(0x42);
//WriteComm(0xD4); //vgh_mux_st[7:0]
//WriteData(0x0a);
//WriteComm(0xD5); //vgh_mux_ed[7:0]
//WriteData(0x32);
////gammma boe4.3 
//WriteComm(0x80); //gam_vrp0
//WriteData(0x00); 
//WriteComm(0xA0); //gam_VRN0
//WriteData(0x00);
//WriteComm(0x81); //gam_vrp1
//WriteData(0x06);//07
//WriteComm(0xA1); //gam_VRN1
//WriteData(0x08);//06

//WriteComm(0x82); //gam_vrp2
//WriteData(0x03);//02
//WriteComm(0xA2); //gam_VRN2
//WriteData(0x03);//01
//WriteComm(0x86); //gam_prp0
//WriteData(0x14); //11
//WriteComm(0xA6); //gam_PRN0
//WriteData(0x14); //10
//WriteComm(0x87); //gam_prp1
//WriteData(0x2C); //27
//WriteComm(0xA7); //gam_PRN1
//WriteData(0x26); //27
//WriteComm(0x83); //gam_vrp3
//WriteData(0x37);
//WriteComm(0xA3); //gam_VRN3
//WriteData(0x37);
//WriteComm(0x84); //gam_vrp4 
//WriteData(0x35);
//WriteComm(0xA4); //gam_VRN4
//WriteData(0x35);
//WriteComm(0x85); //gam_vrp5 
//WriteData(0x3f);
//WriteComm(0xA5); //gam_VRN5
//WriteData(0x3f);
//WriteComm(0x88); //gam_pkp0 
//WriteData(0x0A); //0b
//WriteComm(0xA8); //gam_PKN0
//WriteData(0x0A); //0b
//WriteComm(0x89); //gam_pkp1 
//WriteData(0x13); //14
//WriteComm(0xA9); //gam_PKN1
//WriteData(0x12); //13
//WriteComm(0x8a); //gam_pkp2 
//WriteData(0x18); //1a
//WriteComm(0xAa); //gam_PKN2
//WriteData(0x19); //1a
//WriteComm(0x8b); //gam_PKP3 
//WriteData(0x0a);
//WriteComm(0xAb); //gam_PKN3
//WriteData(0x0a);
//WriteComm(0x8c); //gam_PKP4 
//WriteData(0x17);//14
//WriteComm(0xAc); //gam_PKN4
//WriteData(0x0B);//08
//WriteComm(0x8d); //gam_PKP5
//WriteData(0x1A);//17

//WriteComm(0xAd); //gam_PKN5
//WriteData(0x09);//07
//WriteComm(0x8e); //gam_PKP6
//WriteData(0x1A); //16 //16
//WriteComm(0xAe); //gam_PKN6
//WriteData(0x08); //06 //13
//WriteComm(0x8f); //gam_PKP7
//WriteData(0x1F); //1B
//WriteComm(0xAf); //gam_PKN7
//WriteData(0x00); //07
//WriteComm(0x90); //gam_PKP8 
//WriteData(0x08);//04
//WriteComm(0xB0); //gam_PKN8
//WriteData(0x00);//04
//WriteComm(0x91); //gam_PKP9
//WriteData(0x10);//0A
//WriteComm(0xB1); //gam_PKN9
//WriteData(0x06);//0A
//WriteComm(0x92); //gam_PKP10
//WriteData(0x19);//16
//WriteComm(0xB2); //gam_PKN10
//WriteData(0x15);//15
//WriteComm(0xff);
//WriteData(0x00); 

//WriteComm(0x11);

//Delay(520);	
//WriteComm(0x29);
//Delay(20);	

//---------Start Initial Code ------//
WriteComm(0xff);
WriteData(0xa5);
WriteComm(0xE7); //TE_output_en
WriteData(0x10);
WriteComm(0x35); //TE_ interface_en
WriteData(0x00);//01
WriteComm(0x36); 
WriteData(0xc0);//c0
WriteComm(0x3A); 
WriteData(0x01);//01---565/00---666
WriteComm(0x40); 
WriteData(0x01);//01:IPS/00:TN
WriteComm(0x41); 
WriteData(0x03);//01--8bit//03--16bit
WriteComm(0x44); //VBP 
WriteData(0x15); 

WriteComm(0x45); //VFP 
WriteData(0x15); 
WriteComm(0x7d);//vdds_trim[2:0]
WriteData(0x03);
 
WriteComm(0xc1);//avdd_clp_en avdd_clp[1:0] avcl_clp_en avcl_clp[1:0]
WriteData(0xbb);//0xbb 88 a2
WriteComm(0xc2);//vgl_clp_en vgl_clp[2:0]
WriteData(0x05);
WriteComm(0xc3);//vgl_clp_en vgl_clp[2:0]
WriteData(0x10);
WriteComm(0xc6);//avdd_ratio_sel avcl_ratio_sel vgh_ratio_sel[1:0] vgl_ratio_sel[1:0]
WriteData(0x3e); 
WriteComm(0xc7);//mv_clk_sel[1:0] avdd_clk_sel[1:0] avcl_clk_sel[1:0]
WriteData(0x25); 
WriteComm(0xc8);// VGL_CLK_sel
WriteData(0x21); 
WriteComm(0x7a);// user_vgsp
WriteData(0x51); //58
WriteComm(0x6f);// user_gvdd
WriteData(0x49); //4F 
WriteComm(0x78);// user_gvcl
WriteData(0x57); //70 
WriteComm(0xc9);
WriteData(0x00); 
WriteComm(0x67); 
WriteData(0x11);
//gate_ed
WriteComm(0x51);//gate_st_o[7:0]
WriteData(0x0a);
WriteComm(0x52);//gate_ed_o[7:0]
WriteData(0x7D); //7A
WriteComm(0x53);//gate_st_e[7:0]
WriteData(0x0a);
WriteComm(0x54);//gate_ed_e[7:0]
WriteData(0x7D); //7A
//sorce 
WriteComm(0x46);//fsm_hbp_o[5:0]
WriteData(0x0a);
 
WriteComm(0x47);//fsm_hfp_o[5:0]
WriteData(0x2a);
WriteComm(0x48);//fsm_hbp_e[5:0]
WriteData(0x0a);
WriteComm(0x49);//fsm_hfp_e[5:0]
WriteData(0x1a);
WriteComm(0x44); //VBP 
WriteData(0x15); 
WriteComm(0x45); //VFP 
WriteData(0x15); 
WriteComm(0x73);
WriteData(0x08);
WriteComm(0x74);
WriteData(0x10); //0A

///test mode
//WriteComm(0xf8); 
//WriteData(0x16);
//WriteComm(0xf9); 
//WriteData(0x20);

WriteComm(0x56);//src_ld_wd[1:0] src_ld_st[5:0]
WriteData(0x43);
WriteComm(0x57);//pn_cs_en src_cs_st[5:0]
WriteData(0x42);
WriteComm(0x58);//src_cs_p_wd[6:0]
WriteData(0x3c);
WriteComm(0x59);//src_cs_n_wd[6:0]
WriteData(0x64); 
WriteComm(0x5a);//src_pchg_st_o[6:0]
WriteData(0x41); 
WriteComm(0x5b);//src_pchg_wd_o[6:0]
WriteData(0x3C); 
WriteComm(0x5c);//src_pchg_st_e[6:0]
WriteData(0x02);
WriteComm(0x5d);//src_pchg_wd_e[6:0]
WriteData(0x3c);
WriteComm(0x5e);//src_pol_sw[7:0]
WriteData(0x1f);
WriteComm(0x60);//src_op_st_o[7:0]
WriteData(0x80);

WriteComm(0x61);//src_op_st_e[7:0]
WriteData(0x3f);
WriteComm(0x62);//src_op_ed_o[9:8] src_op_ed_e[9:8]
WriteData(0x21);
WriteComm(0x63);//src_op_ed_o[7:0]
WriteData(0x07);
WriteComm(0x64);//src_op_ed_e[7:0]
WriteData(0xe0);
WriteComm(0x65);//chopper
WriteData(0x02);
WriteComm(0xca); //avdd_mux_st_o[7:0]
WriteData(0x20);
WriteComm(0xcb); //avdd_mux_ed_o[7:0]
WriteData(0x52);
WriteComm(0xcc); //avdd_mux_st_e[7:0]
WriteData(0x10);
WriteComm(0xcD); //avdd_mux_ed_e[7:0]
WriteData(0x42);
WriteComm(0xD0); //avcl_mux_st_o[7:0]
WriteData(0x20);
WriteComm(0xD1); //avcl_mux_ed_o[7:0]
WriteData(0x52);
WriteComm(0xD2); //avcl_mux_st_e[7:0]
WriteData(0x10);
WriteComm(0xD3); //avcl_mux_ed_e[7:0]
WriteData(0x42);
WriteComm(0xD4); //vgh_mux_st[7:0]
WriteData(0x0a);
WriteComm(0xD5); //vgh_mux_ed[7:0]
WriteData(0x32);
//gammma boe4.3 
WriteComm(0x80); //gam_vrp0
WriteData(0x00); 
WriteComm(0xA0); //gam_VRN0
WriteData(0x00);
WriteComm(0x81); //gam_vrp1
WriteData(0x06);//07
WriteComm(0xA1); //gam_VRN1
WriteData(0x08);//06

WriteComm(0x82); //gam_vrp2
WriteData(0x03);//02
WriteComm(0xA2); //gam_VRN2
WriteData(0x03);//01
WriteComm(0x86); //gam_prp0
WriteData(0x14); //11
WriteComm(0xA6); //gam_PRN0
WriteData(0x14); //10
WriteComm(0x87); //gam_prp1
WriteData(0x2C); //27
WriteComm(0xA7); //gam_PRN1
WriteData(0x26); //27
WriteComm(0x83); //gam_vrp3
WriteData(0x37);
WriteComm(0xA3); //gam_VRN3
WriteData(0x37);
WriteComm(0x84); //gam_vrp4 
WriteData(0x35);
WriteComm(0xA4); //gam_VRN4
WriteData(0x35);
WriteComm(0x85); //gam_vrp5 
WriteData(0x3f);
WriteComm(0xA5); //gam_VRN5
WriteData(0x3f);
WriteComm(0x88); //gam_pkp0 
WriteData(0x0A); //0b
WriteComm(0xA8); //gam_PKN0
WriteData(0x0A); //0b
WriteComm(0x89); //gam_pkp1 
WriteData(0x13); //14
WriteComm(0xA9); //gam_PKN1
WriteData(0x12); //13
WriteComm(0x8a); //gam_pkp2 
WriteData(0x18); //1a
WriteComm(0xAa); //gam_PKN2
WriteData(0x19); //1a
WriteComm(0x8b); //gam_PKP3 
WriteData(0x0a);
WriteComm(0xAb); //gam_PKN3
WriteData(0x0a);
WriteComm(0x8c); //gam_PKP4 
WriteData(0x17);//14
WriteComm(0xAc); //gam_PKN4
WriteData(0x0B);//08
WriteComm(0x8d); //gam_PKP5
WriteData(0x1A);//17

WriteComm(0xAd); //gam_PKN5
WriteData(0x09);//07
WriteComm(0x8e); //gam_PKP6
WriteData(0x1A); //16 //16
WriteComm(0xAe); //gam_PKN6
WriteData(0x08); //06 //13
WriteComm(0x8f); //gam_PKP7
WriteData(0x1F); //1B
WriteComm(0xAf); //gam_PKN7
WriteData(0x00); //07
WriteComm(0x90); //gam_PKP8 
WriteData(0x08);//04
WriteComm(0xB0); //gam_PKN8
WriteData(0x00);//04
WriteComm(0x91); //gam_PKP9
WriteData(0x10);//0A
WriteComm(0xB1); //gam_PKN9
WriteData(0x06);//0A
WriteComm(0x92); //gam_PKP10
WriteData(0x19);//16
WriteComm(0xB2); //gam_PKN10
WriteData(0x15);//15
WriteComm(0xff);
WriteData(0x00); 
WriteComm(0x11);
delay_ms(120);
WriteComm(0x29);
delay_ms(20);


#endif
//
#if	UE024QV_RB40_A038A_9307
	WriteComm(0xfe);
	WriteComm(0xef);
	WriteComm(0x36);
	WriteData(0x28); 
	WriteComm(0x3a);
	WriteData(0x05);
	//------------------9307


	//=============		
	WriteComm(0x20);

	WriteComm(0x85);	
	WriteData(0xc0);	
	WriteComm(0x86);	
	WriteData(0x98);
	WriteComm(0x88);
	WriteData(0x02);
	WriteComm(0x89);	
	WriteData(0x33);
	WriteComm(0x8b);	
	WriteData(0x80);	
	WriteComm(0x8d);	
	WriteData(0x3b);
	WriteComm(0x8e);	 
	WriteData(0x0f);	



	WriteComm(0xff);
	WriteData(0x62);

	WriteComm(0x99);	
	WriteData(0x3e);
	WriteComm(0x9d);	
	WriteData(0x4b);
	WriteComm(0x98);	
	WriteData(0x3e);
	WriteComm(0x9c);	
	WriteData(0x4b);


	WriteComm(0xbe);	
	WriteData(0x41);

	WriteComm(0x9b);
	WriteData(0x47);
	WriteComm(0xe1);
	WriteData(0x04);
	WriteData(0x05);

	WriteComm(0xe8);
	WriteData(0x13);
	WriteData(0x40);

	WriteComm(0xec);
	WriteData(0x33);
	WriteData(0x02);
	WriteData(0xff);
	WriteComm(0xed);
	WriteData(0x19);
	WriteData(0x09); 

	WriteComm(0xc9);	
	WriteData(0x05);
	WriteComm(0xc3);	
	WriteData(0x14);
	WriteComm(0xc4);	
	WriteData(0x10);

	WriteComm(0xF0);
	WriteData(0x87);
	WriteData(0x0a);
	WriteData(0x0a);
	WriteData(0x09);
	WriteData(0x05);
	WriteData(0x29);

	WriteComm(0xF1);
	WriteData(0x41);
	WriteData(0x6d);
	WriteData(0x53);
	WriteData(0x2f);
	WriteData(0x31);
	WriteData(0x3a);

	WriteComm(0xF2);
	WriteData(0x46);
	WriteData(0x05);
	WriteData(0x07);
	WriteData(0x08);
	WriteData(0x06);
	WriteData(0x2e);

	WriteComm(0xF3);
	WriteData(0x47);
	WriteData(0xd1);
	WriteData(0x88);
	WriteData(0x30);
	WriteData(0x31);
	WriteData(0x6a); 


	WriteComm(0x11);
	delay_ms(120);
	WriteComm(0x29);
	WriteComm(0x2c);
#endif
//

if(clear_sign != 0){
	LCD_Clear(0);
}
clear_sign++;
	return true;
}

void video_deinit() {
}

void video_flip() {
	
}
#endif

