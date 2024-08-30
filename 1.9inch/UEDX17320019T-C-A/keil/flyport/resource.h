/*
 * resource.h
 *
 *  Created on: Nov 22, 2020
 *      Author: ZKSWE Develop Team
 */

#ifndef _CONTEXT_RESOURCE_H_
#define _CONTEXT_RESOURCE_H_

#include "context/common.h"

typedef enum {
	E_RES_TYPE_UI,
	E_RES_TYPE_IMG,
	E_RES_TYPE_FONT,
	E_RES_TYPE_DATA,
	E_RES_TYPE_MAX,
} res_type_e;

bool resource_init();
void resource_deinit();
bool resource_read(uint8_t type, uint32_t pos, void *data, uint32_t size); 
bool resource_write(uint32_t pos, const void *data, uint32_t size);
bool resource_readFromDMA(uint8_t type, uint32_t pos, void *data, uint32_t size);
bool resource_waitDMAEnd(uint8_t type, uint32_t pos, void *data, uint32_t size);
#endif /* _CONTEXT_RESOURCE_H_ */
