/*
 * rect.h
 *
 *  Created on: Nov 24, 2020
 *      Author: ZKSWE Develop Team
 */

#ifndef _MISC_RECT_H_
#define _MISC_RECT_H_

#include "context/common.h"

typedef struct {
	int16_t x;
	int16_t y;
	uint16_t w;
	uint16_t h;
} rect_t;

bool rect_is_hit(const rect_t *rt, int16_t x, int16_t y);
bool rect_is_equal(const rect_t *rt1, const rect_t *rt2);
bool rect_does_intersect(const rect_t *r1, const rect_t *r2);
bool rect_intersect(const rect_t *r1, const rect_t *r2, rect_t *dst);

#endif /* _MISC_RECT_H_ */
