#include "seggerop.h"
#include <QString>
#include "comfunc_qt.h"
#include "comfunc.h"
#include <stdlib.h>


#define MIN(a, b) (((a) < (b)) ? (a) : (b))

//#define arm_ram_base_addr    0x20000000 //MCU中RAM的起始地址
//#define arm_ram_size    (20*1024)  //MCU中RAM的容量



#define get_fifo_used_size(pFifo)     (((pFifo)->in - (pFifo)->out) )  //查询fifo中未读出的字节数uint16_t
#define get_fifo_unused_size(pFifo)    ((pFifo)->size - get_fifo_used_size((pFifo)))   		//查询fifo的剩余容量uint16_t

int SeggerOp::_index(const unsigned char *whole, unsigned int wholeSize, const unsigned char *search, unsigned int searchSize)
{
    // looking for "SEGGER RTT"
    bool found = false;

    int i = 0;
    while ((unsigned int)i < wholeSize - searchSize + 1)
    {
        if (search[0] != whole[i])
        {
            i++;
            continue;
        }

        int temp = 1;
        int j = 1;
        while ((unsigned int)j < searchSize)
        {
            if (whole[i + temp++] != search[j++])
                break;
            if ((unsigned int)j == searchSize)
                found = true;
        }

        if (found)
        {
            break;
        }
        i++;
    }

    int ix = -1;
    if (found)
        ix = i;
    return ix;
}

SeggerOp::SeggerOp()
{
    _jlinkDll = new QLibrary();
    JLINK_API_is_available = false;
}

SeggerOp::~SeggerOp()
{
    delete _jlinkDll;
}

bool SeggerOp::unload_dll()
{
    if(this->api_is_available())
    {
        this->seggerClose();//卸载dll之前必须先关闭，否则unload会崩溃
    }
    JLINK_API_is_available = false;

    return  _jlinkDll->unload();
}

/*
功能：载入dll文件、获取dll中的几个函数地址
形参：@speed为JLINK的速度，&opInfo输出错误信息
返回值：正常返回true，异常返回false，并设置opInfo
*/
bool SeggerOp::load_dll_and_get_api(QString &opInfo, int speed)
{
    _jlinkDll->setFileName("JLinkARM.dll");

    if (!_jlinkDll->load())
    {
        opInfo.append("error: cannot find file：JLinkARM.dll\r\n");
        return false;
    }

    seggerTifSelect = (JLINKARM_TIF_Select)_jlinkDll->resolve("JLINKARM_TIF_Select");
    seggerReadMem   = (JLINKARM_ReadMem)_jlinkDll->resolve("JLINKARM_ReadMem");
    seggerWriteMem  = (JLINKARM_WriteMem)_jlinkDll->resolve("JLINKARM_WriteMem");
    seggerWriteU16  = (JLINKARM_WriteU16)_jlinkDll->resolve("JLINKARM_WriteU16");
    seggerSetSpeed  = (JLINKARM_SetSpeed)_jlinkDll->resolve("JLINKARM_SetSpeed");
    seggerConnect   = (JLINK_Connect)_jlinkDll->resolve("JLINK_Connect");
    seggerIsConnect = (JLINK_IsConnected)_jlinkDll->resolve("JLINK_IsConnected");
    seggerOpen      = (JLINKARM_Open)_jlinkDll->resolve("JLINKARM_Open");
    seggerClose     = (JLINKARM_Close)_jlinkDll->resolve("JLINKARM_Close");
    seggerIsOpen    = (JLINKARM_IsOpen)_jlinkDll->resolve("JLINKARM_IsOpen");

    if (   !seggerTifSelect
        || !seggerReadMem
        || !seggerWriteMem
        || !seggerWriteU16
        || !seggerSetSpeed
        || !seggerConnect
        || !seggerIsConnect
        || !seggerOpen
        || !seggerClose
        || !seggerIsOpen   )
    {
        opInfo.append("error: failed to get api function from JLinkARM.dll\r\n");
        return false;
    }

    seggerTifSelect(1);
    seggerSetSpeed(speed);

    JLINK_API_is_available = true;
    opInfo.append("JLinkARM.dll is loaded\r\n");
    return true;
}

/*
 * 功能：搜索SEGGER RTT的内存地址，如果搜索成功，则把地址记录在this->rtt_struct_abs_addr_in_arm
 * 形参：@opInfo，不管成功or失败，都把可视化信息输出到实参;@ARM单片机RAM的起始地址，一般是0x20000000，@ARM单片机的RAM容量，单位为字节
 * 返回值：true or false
*/
bool SeggerOp::locateToArm(QString &opInfo, uint32_t arm_ram_base_addr, uint32_t arm_ram_size)
{
    // 在ARM单片机的整个RAM中搜索字符串"SEGGER RTT"

    qDebug("内存起始地址=0x%2X, size = %d KB\r\n", arm_ram_base_addr, arm_ram_size/1024);

    uint8_t *whole = (uint8_t *)malloc(arm_ram_size);
    if(NULL == whole)
    {
        opInfo.append(QString("出错: 上位机无法分配%1字节的内存\r\n").arg(arm_ram_size));
        return false;
    }

    memset(whole, 0, arm_ram_size);
    seggerReadMem(arm_ram_base_addr, arm_ram_size, whole);

    const unsigned char SEARCH[] = { 'S', 'E', 'G', 'G', 'E', 'R', ' ', 'R', 'T', 'T' };
    int ix = _index(whole, arm_ram_size, SEARCH, sizeof(SEARCH));
    free(whole);
    if (-1 == ix)
    {
        opInfo.append("出错: 无法找到MCU，请检查PC -> JLINK -> MCU的连接, 以及设置的RAM参数是否正确");
        qDebug() << QString("出错: 无法找到字符串\"SEGGER RTT\"，请检查PC->JLINK->MCU的连接");
        return false;
    }

    rtt_struct_abs_addr_in_arm = arm_ram_base_addr + ix;

    opInfo.append("已连接到MCU\r\n");

    return true;
}

/*
 * 功能：从ARM的fifoUp中read数据到buf中
 * 形参：@len为最多想读出多少个字节到buf中
 * 返回值：实际读出了多少个字节到buf中
*/
uint16_t SeggerOp::read_fifoUp_from_arm(uint8_t buf[], uint16_t len)
{
    struct _rtt rtt_tmp;
    seggerReadMem(rtt_struct_abs_addr_in_arm, sizeof(rtt_tmp), (uint8_t*)&rtt_tmp);//获取rtt的信息

    uint16_t front_len;

    gfifo_t *fifo = &rtt_tmp.FifoUp;

    //有数据的缓冲区的长度
    len = min(len, fifo->in - fifo->out);
    front_len = min(len, fifo->size - (fifo->out & (fifo->size - 1)));

    seggerReadMem((uint32_t)fifo->buffer + (fifo->out & (fifo->size - 1)), front_len, buf);
    seggerReadMem((uint32_t)fifo->buffer, len - front_len, buf + front_len);

    if(len != 0)
    {
        seggerWriteU16(rtt_struct_abs_addr_in_arm + offset_of(struct _rtt, FifoUp) + offset_of(gfifo_t, out),
                        fifo->out + len);
    }

    return len;
}
/*
 * 功能：向下位机发送数据
 * 返回值：实际写入了多少字节
*/
uint16_t SeggerOp::write_fifoDown_of_arm(uint8_t buf[], uint16_t len)
{
    struct _rtt rtt_tmp;
    seggerReadMem(rtt_struct_abs_addr_in_arm, sizeof(rtt_tmp), (uint8_t*)&rtt_tmp);//获取rtt的信息
    gfifo_t *fifo = &rtt_tmp.FifoDown;

    //qDebug() << "in = " << fifo->in << ", out = " << fifo->out;
    qDebug() << "in = " << (fifo->in & (fifo->size - 1)) << ", out = " << (fifo->out & (fifo->size - 1));

    uint16_t len_behind;//buf后半部分剩余的容量

    len = min(len, fifo->size - fifo->in + fifo->out);

    len_behind = min(len, fifo->size - (fifo->in & (fifo->size - 1)));

    qDebug() << "len_1 = " << len_behind << ", len_2 = " << (len - len_behind);

    seggerWriteMem((uint32_t)(fifo->buffer + (fifo->in & (fifo->size - 1))), len_behind, buf);//后半部
    seggerWriteMem((uint32_t)fifo->buffer, len - len_behind, buf + len_behind);//前半部


    if(len != 0)//update in pointer
    {
        seggerWriteU16(rtt_struct_abs_addr_in_arm + offset_of(struct _rtt, FifoDown) + offset_of(gfifo_t, in),
                        fifo->in + len);
    }

    return len;

}
void SeggerOp::test(void)
{
//    JLINKARM_IsOpen isOpen;
//    isOpen = (JLINKARM_IsOpen)_jlinkDll->resolve("JLINKARM_IsOpen");
//    qDebug()<<"isopen: "<<isOpen();

//    JLINKARM_GetSN get_sn = (JLINKARM_GetSN)_jlinkDll->resolve("JLINKARM_GetSN");
//    qDebug()<<"sn = " << get_sn();

//    JLINKARM_GetId get_id = (JLINKARM_GetId)_jlinkDll->resolve("JLINKARM_GetId");
//    qDebug()<<"mcu id = " << get_id();

//    JLINK_IsConnected is_connect = (JLINK_IsConnected)_jlinkDll->resolve("JLINK_IsConnected");
//    qDebug()<<"is_connect = " << is_connect();

    qDebug()<< "dll is loded:" << this->api_is_available();

}

/*
 * 功能：描述JLINK API是否可用，同时满足两个条件才认为可用：
 * 1、DLL文件已载入
 * 2、从DLL文件中读出了API的地址
 * 相关函数：load_dll_and_get_api、unload_dll
*/
bool SeggerOp::api_is_available()
{
    return JLINK_API_is_available;
}
