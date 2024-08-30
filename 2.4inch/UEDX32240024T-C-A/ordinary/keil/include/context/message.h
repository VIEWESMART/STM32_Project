/*
 * message.h
 *
 *  Created on: Nov 28, 2020
 *      Author: ZKSWE Develop Team
 */

#ifndef _CONTEXT_MESSAGE_H_
#define _CONTEXT_MESSAGE_H_

#include "common.h"

typedef struct {
	uint32_t type   : 8;
	uint32_t param1 : 24;
	uint32_t param2;
} msg_t;

bool message_init();
void message_deinit();

/**
 * @brief 消息入队
 * @param m 消息数据
 * @return true 成功，false 失败
 */
bool message_enqueue(const msg_t *m);

/**
 * @brief 消息出队
 * @param m 消息数据
 * @return true 成功，false 失败
 */
bool message_dequeue(msg_t *m);

#endif /* _CONTEXT_MESSAGE_H_ */
