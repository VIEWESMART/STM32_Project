#include "ext_flythings/draw_point.h"


#if USE_DRAW_POINT
static point_t point = {
	.x = 0,
	.y = 0,
	.size = 2,
	.color = 0xf800
};

//画点函数
void draw_point(const point_t *point) {
	uint16_t e_x = point->x + point->size;
	uint16_t e_y = point->y + point->size;
	LCD_Fill(point->x,point->y,e_x,e_y,point->color);
}

void set_point_x(uint16_t x) {
	point.x = x;
}
void set_point_y(uint16_t y) {
	point.y = y;
}
void set_point_size(uint16_t size) {
	point.size = size;
}
void set_point_color(uint16_t color) {
	point.color = color;
}

point_t *get_point(void) {
	return &point;
}


/* 函数名：测试画曲线(只是验证画曲线功能)
 * 参  数：star_x：X轴基准点坐标
 *         star_y：Y轴基准点坐标
 *         data  ：打点数据
 *         size  ：buff数据量    
 * 返 回：无
 */
void wave_drawpoint(uint16_t star_x, uint16_t star_y, uint8_t *data, uint16_t size) {
	int i;
	point_t *p_point;
	uint16_t x;
	uint16_t y;
	uint16_t last_y;
	
	p_point = get_point();
	x = star_x;
	y = star_y - data[0];
	last_y = y;
	for(i = 1; i < size; i++) {
		if((last_y - y) > 1) { //上升
			LCD_Fill(x,y,x+p_point->size,last_y+p_point->size,p_point->color);
		} else if((y - last_y) > 1) { //下降
			LCD_Fill(x,last_y,x+p_point->size,y+p_point->size,p_point->color);
		} else {
			//p_point->x = x;
			//p_point->y = y;
			//draw_point(p_point);
			LCD_Fill(x,y,x+p_point->size,y+p_point->size,p_point->color);
		}
		last_y = y;
		x = x + p_point->size;
		y = star_y - data[i];
	}
}
#endif
