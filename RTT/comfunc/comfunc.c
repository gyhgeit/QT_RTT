#include <stdint.h>
#include <stdio.h>

#include "comfunc.h"

/***************************************************************
函数名：checksum
描  述：和校验
输入值：*data 数据指针 len 数据长度
输出值：无
返回值：uint8 cs
***************************************************************/
uint8_t checksum(uint8_t *data,uint16_t len)
{
    uint8_t cs = 0;

    while(len-- > 0)
        cs += * data++;
    return(cs);
}
/*
 * 数字转bcd
 */
void DectoBCD(int Dec, unsigned char *Bcd, int length)
{
     int i;
     int temp;

    for(i=length-1; i>=0; i--)
    {
         temp = Dec%100;
         Bcd[i] = ((temp/10)<<4) + ((temp%10) & 0x0F);
         Dec /= 100;
    }

}
uint8_t bin2bcd(uint8_t bin_byte)
{
    return ((((bin_byte) / 10) << 4) + (bin_byte) % 10)	;
}

/*
功能：把十进制数value转换为小端bcd
举例：hex2bcd(1234, buf, 4),执行后buf变为{0x34,,0x12,0x00,0x00}
*/
void hex2bcd_le(uint32_t value, uint8_t *bcd, uint8_t bytes)
{
    uint8_t x;

    while (bytes--)
    {
        x = value % 100u;
        *bcd = bin2bcd(x);
        bcd++;
        value /= 100u;
    }
}
void memadd(void* dest, char data, int  len)
{
    while(len--)
    {
         ((uint8_t *)dest)[len] += data;
    }
}
void put_be_val(uint32_t val, uint8_t * p, uint8_t bytes)
{
    while (bytes-- > 0)
    {
        *(p + bytes) = (uint8_t)(val & 0xFF);
        val >>= 8;
    }
}

void put_le_val(uint32_t val, uint8_t * p, uint8_t bytes)
{
    while (bytes-- > 0)
    {
        *p++ = (uint8_t)(val & 0xFF);
        val >>= 8;
    }
}


uint64_t get_le_val(void * p, uint8_t bytes)
{
    uint64_t ret = 0;

    while (bytes-- > 0)
    {
        ret <<= 8;
        ret |= *((uint8_t *)p + bytes);
    }
    return ret;
}
uint64_t get_be_val(uint8_t * p, uint8_t bytes)
{
    uint64_t ret = 0;
    while (bytes-- > 0)
    {
        ret <<= 8;
        ret |= *p++;
    }

    return ret;
}
uint16_t sp_crc16_with_init(uint16_t crc, const uint8_t *buf, uint32_t size)
{
    unsigned char i;

    while (size-- != 0)
    {
        for (i = 0x80; i != 0; i >>= 1)
        {
            if ((crc & 0x8000) != 0)
            {
                crc <<= 1;
                crc ^= 0x1021;
            }
            else
            {
                crc <<= 1;
            }
            if (((*buf) & i) != 0)
            {
                crc ^= 0x1021;
            }
        }
        buf++;
    }
    return (crc);
}
