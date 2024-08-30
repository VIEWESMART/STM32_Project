#ifndef _DRAW_POINT_H_
#define _DRAW_POINT_H_

//画点功能	0:不使用 1:使用
#define USE_DRAW_POINT	0

#if USE_DRAW_POINT

#include "main.h"

extern void LCD_Fill(uint16_t x,uint16_t y,uint16_t x1,uint16_t y1,uint16_t color);

typedef struct {
	uint16_t x;
	uint16_t y;
	uint8_t size;
	uint16_t color;
} point_t;



void draw_point(const point_t *point);

void set_point_x(uint16_t x);
void set_point_y(uint16_t y);
void set_point_size(uint16_t size);
void set_point_color(uint16_t color);
point_t *get_point(void);

//test
void wave_drawpoint(uint16_t star_x, uint16_t star_y, uint8_t *data, uint16_t size);

#endif

#endif
