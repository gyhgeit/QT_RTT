#ifndef COMFUNC_H
#define COMFUNC_H
#pragma execution_character_set("utf-8")

#include <stdint.h>
#include <stdio.h>



#ifdef __cplusplus//.c定义的函数要想被.cpp调用，必须要extern "C"括起来；而.c想调.cpp的函数，必须要重写.cpp的函数，因为.c不支持调用类
extern "C" {
#endif


#define UNUSED(var) (void)var
#define array_size(array) (sizeof(array)/sizeof(array[0]))
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define offset_of(obj_type,mb)  ((unsigned int)&(((obj_type*)0)->mb))
#define sizeof_mb(obj_type,mb)   sizeof(((obj_type*)0)->mb) //返回结构体某个成员所占的字节数(在编译阶段计算)

#define min(a, b) ((a)<(b)?(a):(b))


uint8_t checksum(uint8_t *data,uint16_t len);
void DectoBCD(int Dec, unsigned char *Bcd, int length);
uint8_t bin2bcd(uint8_t bin_byte);
void hex2bcd_le(uint32_t value, uint8_t *bcd, uint8_t bytes);
void memadd(void* dest, char data, int  len);
void put_be_val(uint32_t val, uint8_t * p, uint8_t bytes);
void put_le_val(uint32_t val, uint8_t * p, uint8_t bytes);
uint64_t get_le_val(void * p, uint8_t bytes);
uint64_t get_be_val(uint8_t * p, uint8_t bytes);
uint16_t sp_crc16_with_init(uint16_t crc, const uint8_t *buf, uint32_t size);


#ifdef __cplusplus
}
#endif



#endif // COMFUNC_H
