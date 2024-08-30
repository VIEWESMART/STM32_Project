/*
 * fy_mem.h
 *
 *  Created on: Jan 20, 2021
 *      Author: ZKSWE Develop Team
 */

#ifndef _MISC_FY_MEM_H_
#define _MISC_FY_MEM_H_

#include "context/common.h"

bool fy_mem_init(uint8_t* memptr,int size);
void fy_mem_deinit();

/**
 * @brief 申请内存
 * @param size   内存大小
 * @return 成功返回内存地址指针，失败返回NULL
 */
void* fy_mem_alloc(uint32_t size);

/**
 * @brief 重新分配内存
 * @param ptr    原先内存地址指针，为NULL情况相当于fy_mem_alloc功能
 * @param size   内存大小
 * @return 成功返回内存地址指针，失败返回NULL
 */
void* fy_mem_realloc(void *ptr, uint32_t new_size);

/**
 * @brief 释放内存
 * @param ptr    内存地址指针
 */
void fy_mem_free(void *ptr);

/**
 * @brief 整理内存碎片
 */
void fy_mem_defrag();

#endif /* _MISC_FY_MEM_H_ */
