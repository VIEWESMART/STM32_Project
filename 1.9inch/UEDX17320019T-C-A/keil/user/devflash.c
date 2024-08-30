#include "devflash.h"
#include "dev_spiflash.h"



static void init(){
    //SerialFlash_DMAInit();
   // SPI_Flash_Init();
}
static void deinit(){

}
static void write(const u8* data,u16 len){

}
static int read(u8* data,u16 len){

}

static void procMsg(int msgtype,int p1,int p2){
    uint32_t id = SPI_FLASH_ReadDeviceID();
    printf(" flash id:%x\n",id);
}
const S_DEV dev_Flash={
    init,
    deinit,
    write,
    read,
    procMsg
};
