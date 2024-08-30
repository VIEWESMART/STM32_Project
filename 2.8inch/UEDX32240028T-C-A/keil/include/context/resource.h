/*
 * resource.h
 *
 *  Created on: Nov 22, 2020
 *      Author: ZKSWE Develop Team
 */

#ifndef _CONTEXT_RESOURCE_H_
#define _CONTEXT_RESOURCE_H_

#include "common.h"

#define INVALID_ADDR			0xFFFFFFFF

typedef enum {
	E_RES_TYPE_UI,
	E_RES_TYPE_IMG,
	E_RES_TYPE_FONT,
	E_RES_TYPE_CONST,
	E_RES_TYPE_DATA,
	E_RES_TYPE_MAX,
} res_type_e;

typedef enum {
	E_RES_CONST_TYPE_STRING,
	E_RES_CONST_TYPE_CHARSET,
} res_const_type_e;

bool resource_init();
void resource_deinit();

/**
 * @brief 读取数据
 * @param type   对应res_type_e的值
 * @param pos    偏移位置
 * @param data   数据存储区
 * @param size   数据存储区大小
 * @return true 成功，false 失败
 */
bool resource_read(uint8_t type, uint32_t pos, void *data, uint32_t size);

/**
 * @brief 写数据
 * @param pos    偏移位置
 * @param data   数据存储区
 * @param size   数据存储区大小
 * @return true 成功，false 失败
 */
bool resource_write(uint32_t pos, const void *data, uint32_t size);

/**
 * @brief 加载字符串资源
 * @param index    字符串索引
 * @return 成功返回字符串数据，失败返回NULL
 */
char* resource_load_string(uint16_t index);

#endif /* _CONTEXT_RESOURCE_H_ */
