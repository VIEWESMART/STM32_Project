/*
 * gfx.h
 *
 *  Created on: Nov 11, 2020
 *      Author: ZKSWE Develop Team
 */

#ifndef _GRAPHICS_GFX_H_
#define _GRAPHICS_GFX_H_

#include "misc/rect.h"

#define GL_RGB_R(x)              ((x&0xF800) >> 8)
#define GL_RGB_G(x)              ((x&0x07F0) >> 3)
#define GL_RGB_B(x)              ((x&0x001F) << 3)
#define GL_ARGB_A(x)             (x != COLOR_KEY)

#define GL_RGB(r,g,b)            (((r&0xF8)<<8)|((g&0xFC)<<3)|((b&0xF8)>>3))

#define COLOR_KEY                0x00
#define BG_COLOR                 0x00

#define COLOR_WHITE              0xFFFF
#define COLOR_BLACK              0x0000
#define COLOR_BLUE               0x001F
#define COLOR_BRED               0XF81F
#define COLOR_GRED               0XFFE0
#define COLOR_GBLUE              0X07FF
#define COLOR_RED                0xF800
#define COLOR_MAGENTA            0xF81F
#define COLOR_GREEN              0x07E0
#define COLOR_CYAN               0x7FFF
#define COLOR_YELLOW             0xFFE0
#define COLOR_BROWN              0XBC40
#define COLOR_BRRED              0XFC07
#define COLOR_GRAY               0X8430

#define INVALID_IMG_ID           0xFFFF

typedef struct {
	uint16_t width;
	uint16_t height;

	uint32_t color_table_offset;
	uint32_t color_table_size;

	uint32_t compressed_data_offset;
	uint32_t compressed_data_size;

	uint8_t depth;
	uint8_t reserve[3];
} __attribute__ ((packed)) bmp_info_t;

typedef struct {
	/**
	 * @brief 画点
	 * @param x   x轴坐�?
	 * @param y   y轴坐�?
	 * @param rgb 颜色�?
	 */
	void (*draw_pixel)(int16_t x, int16_t y, uint16_t rgb);

	/**
	 * @brief 填充矩形
	 * @param rc  区域位置
	 * @param rgb 颜色�?
	 */
	void (*fill_rect)(const rect_t *rc, uint16_t rgb);

	/**
	 * @brief 填充bmp
	 * @param x   x轴坐�?
	 * @param y   y轴坐�?
	 * @param rc  对应bmp的区域位置，为NULL则全部绘�?
	 * @param bmpid bmp索引id�?
	 */
	void (*fill_bmp)(int16_t x, int16_t y, const rect_t *rc, uint16_t bmpid);

	/**
	 * @brief 填充bmp过滤关键�?
	 * @param x   x轴坐�?
	 * @param y   y轴坐�?
	 * @param rc  对应bmp的区域位置，为NULL则全部绘�?
	 * @param bmpid bmp索引id�?
	 * @param colorkey 关键�?
	 */
	void (*fill_bmp_with_colorkey)(int16_t x, int16_t y, const rect_t *rc, uint16_t bmpid, uint16_t colorkey);
} gfx_op_t;

extern const gfx_op_t g_gfx_op;

/***
 * ÆÁÄ»LCD¿ØÖÆÆ÷ÊÊÅä½Ó¿Ú£¬ÓÃÓÚ¿Í»§×Ô¼ºÊÊÅäÏÔÊ¾ÆÁµÄ´úÂë¡£
 * */
typedef struct {
	/**
	 * ´úÂë²Î¿¼£¬2a,2b,2c, cs_low
	 * LCD ¿ªÊ¼ÇøÓòË¢ÐÂ£¬²¢ÉèÖÃCSÎªLOW
	 */
	void (*lcd_start_rectfill)(int16_t x, int16_t y,int16_t w, int16_t h);
	/**
	 * LCDÄÚÈÝÌî³ä£¬±ØÐëÏÈÉèÖÃÇøÓò×ø±êºó²ÅÄÜÉèÖÃ
	 */
	void (*lcd_piex_fill)(uint16_t rgb);
	/**
	 * cs ½áÊøÇøÓòË¢ÐÂ£¬À­¸ßÊý¾ÝÏß
	 */
	void (*lcd_end_rectfill)();

	void (*lcd_fill_rect)(int16_t x, int16_t y,int16_t w, int16_t h,uint16_t rgb);
}gfx_cpulcd;

extern const gfx_cpulcd* mlcd_gfx;
void gfx_set_cpulcd(const gfx_cpulcd* lcd);

#endif /* _GRAPHICS_GFX_H_ */
