/*
使用方法：

*/



#ifndef SEGGEROP_H
#define SEGGEROP_H
#pragma execution_character_set("utf-8")

#include <QThread>
#include <QDebug>
#include <QMutex>
#include <QLibrary>
#include <QDateTime>
#include <QTimer>
#include <QMap>
#include <QString>
#include "gfifo.h"



typedef bool     (*JLINKARM_IsHalted)(void);
typedef bool     (*JLINKARM_Halt)(void);//令MCU的程序暂停
typedef void     (*JLINKARM_Reset)();
typedef void     (*JLINKARM_Open)(void);
typedef void     (*JLINKARM_Close)(void);
typedef bool     (*JLINKARM_IsOpen)(void);
typedef uint32_t (*JLINKARM_GetSN)(void);
typedef uint32_t (*JLINKARM_GetId)(void);//MCU的id
typedef uint32_t (*JLINKARM_GetDLLVersion)(void);
typedef uint32_t (*JLINKARM_GetSpeed)(void);
typedef uint32_t (*JLINKARM_GetHardwareVersion)();//jlink的固件版本
typedef uint32_t (*JLINKARM_ReadDCC)(uint32_t *buf, uint32_t size, int32_t timeout);
typedef uint32_t (*JLINKARM_WriteDCC)(const uint32_t *buf, uint32_t size, int32_t timeout);
typedef uint32_t (*JLINKARM_ReadDCCFast)(uint32_t *buf, uint32_t size, int32_t timeout);
typedef uint32_t (*JLINKARM_WriteDCCFast)(const uint32_t *buf, uint32_t size, int32_t timeout);
typedef uint32_t (*JLINKARM_WaitDCCRead)(uint32_t timeout);
typedef int      (*JLINKARM_WriteMem)(unsigned addr, unsigned size, const unsigned char *buf);
typedef void     (*JLINKARM_SetSpeed)(uint32_t spd);//设置jlink的速度，0为自动调整
typedef uint32_t (*JLINKARM_ExecCommand)(const char* cmd,uint32_t a,uint32_t b);
typedef void     (*JLINKARM_WriteU8)(uint32_t addr, uint8_t dat);
typedef void     (*JLINKARM_WriteU16)(uint32_t addr, uint16_t dat);
typedef void     (*JLINKARM_WriteU32)(uint32_t addr, uint32_t dat);
typedef uint32_t (*JLINKARM_ReadMemU8)(uint32_t addr, uint32_t leng, uint8_t *buf, uint8_t *status);
typedef uint32_t (*JLINKARM_ReadMemU16)(uint32_t addr, uint32_t leng, uint16_t *buf, uint8_t *status);
typedef uint32_t (*JLINKARM_ReadMemU32)(uint32_t addr, uint32_t leng, uint32_t *buf, uint8_t *status);
typedef void     (*JLINKARM_ReadMemHW)(uint32_t addr, uint32_t leng, uint8_t *buf);
typedef int      (*JLINKARM_ReadMem)(uint32_t addr, uint32_t leng, uint8_t *buf);//从ARM的绝对地址addr处，读取leng个字节到buf中
typedef int      (*JLINKARM_TIF_Select)(unsigned tif);
typedef void     (*JLINK_ReadMemU8)(uint32_t addr, uint32_t leng, uint8_t *buf, uint8_t *status);
typedef uint32_t (*JLINK_GetMemZones)(uint32_t a, uint32_t b);
typedef void     (*JLINKARM_Go)(void);//令MCU的程序继续
//typedef uint32_t (_CALL *JLINK_TIF_Select)(uint32_t tif);
typedef uint32_t (*JLINK_Connect)(void);
typedef uint32_t (*JLINK_IsConnected)(void);
//typedef uint32_t(_CALL*JLINK_IsConnected)(void);


#pragma pack(1)
struct _rtt
{
    char id[11];
    gfifo_t FifoUp;
    gfifo_t FifoDown;
    uint8_t upMode;
    uint8_t downMode;
};
#pragma pack()


class SeggerOp
{
public:
    SeggerOp();
    ~SeggerOp();
    bool load_dll_and_get_api(QString &opInfo, int speed = 2000);//载入dll，并获取JLINK API的地址
    bool locateToArm(QString &opInfo, uint32_t arm_ram_base_addr, uint32_t arm_ram_size);//定位到ARM的SEGGER RTT位置
    bool api_is_available();
    bool unload_dll();

    uint16_t read_fifoUp_from_arm(uint8_t buf[], uint16_t len);
    uint16_t write_fifoDown_of_arm(uint8_t buf[], uint16_t len);

    /*注意，操作JLINK API之前，应先检测api_is_available()*/
    JLINK_Connect       seggerConnect;
    JLINK_IsConnected   seggerIsConnect;
    JLINKARM_Open       seggerOpen;
    JLINKARM_Close      seggerClose;
    JLINKARM_IsOpen     seggerIsOpen;

    void test(void);


private:
    int _index(const unsigned char *whole, unsigned int wholeSize, const unsigned char *search, unsigned int searchSize);

    QLibrary *_jlinkDll;
    gfifo_t FifoUp_info;//从ARM中复制出FifoUp的信息
    gfifo_t FifoDown_info;//从ARM中复制出FifoDown的信息
    uint32_t rtt_struct_abs_addr_in_arm;//RTT结构体在ARM中的绝对地址
    bool JLINK_API_is_available;//DLL已载入&&API地址已获取=>true

    //注意，操作JLINK API之前，应先检测dll是否已载入&API地址是否已获取
    JLINKARM_TIF_Select seggerTifSelect;
    JLINKARM_ReadMem    seggerReadMem;
    JLINKARM_WriteMem   seggerWriteMem;
    JLINKARM_WriteU16   seggerWriteU16;
    JLINKARM_SetSpeed   seggerSetSpeed;
};

#endif // SEGGEROP_H

