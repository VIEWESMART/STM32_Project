/*
 * common.h
 *
 *  Created on: Nov 24, 2020
 *      Author: ZKSWE Develop Team
 */

#ifndef _CONTEXT_COMMON_H_
#define _CONTEXT_COMMON_H_

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef NULL
#define NULL (void *) 0
#endif

#ifndef bool
#define bool	uint8_t
#define true	1
#define false	0
#endif

#ifndef MAX
#define MAX(x, y)               (((x) > (y))?(x):(y))
#endif

#ifndef MIN
#define MIN(x, y)               (((x) < (y))?(x):(y))
#endif

#define ALIGN_MASK              0x3
#define ALIGN_UP(s)             ((s + ALIGN_MASK) & (~ALIGN_MASK))

#define TABLE_SIZE(t)			(sizeof(t)/sizeof(t[0]))

#define LOWORD(l)           	((uint16_t)(l))
#define HIWORD(l)           	((uint16_t)(l >> 16) & 0xFFFF)
#define MAKEDWORD(low, high)	(low | ((uint32_t) high << 16))

/**
 * @brief 触摸类型
 */
typedef enum {
	E_TOUCH_DOWN,
	E_TOUCH_UP,
	E_TOUCH_MOVE
} touch_type_e;

/**
 * @brief 消息类型，用户自定义消息请定义于 E_MSG_TYPE_USER 之后的值
 */
typedef enum {
	E_MSG_TYPE_CREATE,
	E_MSG_TYPE_DESTROY,
	E_MSG_TYPE_DRAW,
	E_MSG_TYPE_TOUCHEVENT,
	E_MSG_TYPE_TIMER,
	E_MSG_TYPE_OPEN_PAGE,
	E_MSG_TYPE_UPDATE_REG,

	E_MSG_TYPE_USER = 0x7F,
} msg_type_e;

#endif /* _CONTEXT_COMMON_H_ */
