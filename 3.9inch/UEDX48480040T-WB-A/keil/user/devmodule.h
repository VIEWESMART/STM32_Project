#ifndef __DEV_MOD_H
#define __DEV_MOD_H
#include "common.h"
#include "main.h"

const S_DEV* loadDev(const S_DEV* dev);
void unloadDev(const S_DEV* dev);


extern const S_DEV dev_uartupgrade;
extern const S_DEV dev_uart1;
extern const S_DEV dev_Flash;
extern const S_DEV dev_ResTP;

#define DEVMSG_TIMER10ms  	1
#define DEVMSG_WRITE  		2
#define DEVMSG_TIMER100ms 	3
#define DEVMSG_TIMER50ms  	4
#define DEVMSG_TIMER1S 		5
#define DEVMSG_TIMER3S 		6
#define DEVMSG_TIMER1ms  	7
#define DEVMSG_TIMER5ms     8

#define DEVMSG_FLASH_READID 100


#endif
