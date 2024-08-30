/*
 * event.h
 *
 *  Created on: Nov 29, 2020
 *      Author: ZKSWE Develop Team
 */

#ifndef _EVENT_EVENT_H_
#define _EVENT_EVENT_H_

#include "context/common.h"

bool event_init(void);
void event_deinit(void);
bool event_poll(void);

#endif /* _EVENT_EVENT_H_ */
