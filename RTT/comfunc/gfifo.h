/*
注意：fifo的buf的容量必须是2的整数次方
*/

//#include "gfifo.h"
#ifndef GFIFO_H
#define GFIFO_H
#include <stdint.h>
#pragma execution_character_set("utf-8")


#define gfifo_put(...)  __kfifo_put(__VA_ARGS__)
#define gfifo_get(...)  __kfifo_get(__VA_ARGS__)


#pragma pack(1)
typedef struct kfifo {
    uint8_t *buffer;     /* the buffer holding the data */
    uint16_t size;         /* the size of the allocated buffer */
    uint16_t in;           /* data is added at offset (in % size) */
    uint16_t out;          /* data is extracted from off. (out % size) */
    //spinlock_t *lock;          /* protects concurrent modifications */
}gfifo_t;
#pragma pack()


void init_fifo(struct kfifo *fifo, uint8_t *buffer, uint16_t size);//注意，



uint16_t __kfifo_put(struct kfifo *fifo,
            const uint8_t *buffer, uint16_t len);
uint16_t __kfifo_get(struct kfifo *fifo,
             uint8_t *buffer, uint16_t len);


#endif // GFIFO_H
