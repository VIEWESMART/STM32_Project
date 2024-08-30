#ifndef __COMMOON_H__
#define __COMMOON_H__

typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned char u8;

#ifndef NULL
#define NULL (void*)0
#endif

typedef struct{
    void (*init)(void);
    void (*deinit)(void);
    void (*write)(const u8* data,u16 len);
    u16 (*read)(u16 cmd,u8* data,u16 len);
    void (*procMsg)(int msgtype,int p1,int p2);
}S_DEV;

typedef struct{
    void (*init)(void);
    void (*deinit)(void);
    void (*apploop)();
}S_APP;

#define SD_CARD     0
#define NOR_FLASH   0x01

//extern const S_DEV otherapp;

#endif
