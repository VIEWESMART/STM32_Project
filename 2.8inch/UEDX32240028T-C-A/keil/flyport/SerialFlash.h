#ifndef SERIALFLASH_H
#define SERIALFLASH_H

#include <stdint.h>

void fly_flash_init(void);
uint32_t fy_flash_readid(void);
void fy_flash_read(uint32_t address24, uint8_t* buffer, uint32_t length);
void fy_flash_readdma(uint32_t address24, uint8_t* buffer, uint32_t length);
void fy_flash_erase(void);
void fy_flash_erase_block(uint32_t start,uint32_t sizeOfBitmaps);
void fy_flash_page_write(uint32_t addr,uint8_t* data,uint32_t size);
uint32_t fy_flash_isreceiveing(void);
void fy_flash_waitreceive_done(void);
void fy_flash_dmainit(void);
uint32_t readDeviceId(void);

void SerialFlash_EraseSize(uint32_t startaddr,uint32_t size);
void SerialFlash_ProgramInfo(uint32_t addr,uint8_t* data,uint32_t size);
void SerialFlash_ReadData(uint32_t address24, uint8_t* buffer, uint32_t length);

#endif //SERIALFLASH_H
