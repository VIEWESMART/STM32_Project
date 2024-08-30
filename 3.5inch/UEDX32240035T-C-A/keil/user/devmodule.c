
#include "devmodule.h"

const S_DEV* loadDev(const S_DEV* dev){
    if(dev != NULL){
        if(dev->init != NULL){
            dev->init();
        }
    }
    return dev;
}
void unloadDev(const S_DEV* dev){
    if(dev != NULL){
        if(dev->deinit != NULL){
            dev->deinit();
        }
    }
}
