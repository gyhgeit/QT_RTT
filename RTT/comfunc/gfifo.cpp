#include <string.h>
#include "gfifo.h"


#include "comfunc.h"


/* 功能： 动态初始化一个fifo结构，如果在定义fifo变量的同时，直接进行了初始化，那么就没必要再调用该函数了
 * 形参： buffer的容量必须是2的整数次方
 */
void init_fifo(struct kfifo *fifo, uint8_t *buffer, uint16_t size)
{
    fifo->buffer = buffer;
    fifo->size = size;
    fifo->in = 0;
    fifo->out = 0;
}

//static inline uint16_t kfifo_put(struct kfifo *fifo,
//                const uint8_t *buffer, uint16_t len)
//{
//    unsigned long flags;
//    uint16_t ret;
//    //spin_lock_irqsave(fifo->lock, flags);
//    ret = __kfifo_put(fifo, buffer, len);
//    //spin_unlock_irqrestore(fifo->lock, flags);
//    return ret;
//}

//static inline uint16_t kfifo_get(struct kfifo *fifo,
//                     uint8_t *buffer, uint16_t len)
//{
//    unsigned long flags;
//    uint16_t ret;
//    //spin_lock_irqsave(fifo->lock, flags);
//    ret = __kfifo_get(fifo, buffer, len);
//        //当fifo->in == fifo->out时，buufer为空
//    if (fifo->in == fifo->out)
//        fifo->in = fifo->out = 0;
//    //spin_unlock_irqrestore(fifo->lock, flags);
//    return ret;
//}


uint16_t __kfifo_put(struct kfifo *fifo,
            const uint8_t *buffer, uint16_t len)
{
    uint16_t l;
       //buffer中空的长度
    len = min(len, fifo->size - fifo->in + fifo->out);
    /*
     * Ensure that we sample the fifo->out index -before- we
     * start putting bytes into the kfifo.
     */
    //smp_mb();
    /* first put the data starting from fifo->in to buffer end */
    l = min(len, fifo->size - (fifo->in & (fifo->size - 1)));
    memcpy(fifo->buffer + (fifo->in & (fifo->size - 1)), buffer, l);
    /* then put the rest (if any) at the beginning of the buffer */
    memcpy(fifo->buffer, buffer + l, len - l);

    /*
     * Ensure that we add the bytes to the kfifo -before-
     * we update the fifo->in index.
     */
    //smp_wmb();
    fifo->in += len;  //每次累加，到达最大值后溢出，自动转为0
    return len;
}

uint16_t __kfifo_get(struct kfifo *fifo,
             uint8_t *buffer, uint16_t len)
{
    uint16_t l;
        //有数据的缓冲区的长度
    len = min(len, fifo->in - fifo->out);
    /*
     * Ensure that we sample the fifo->in index -before- we
     * start removing bytes from the kfifo.
     */
    //smp_rmb();
    /* first get the data from fifo->out until the end of the buffer */
    l = min(len, fifo->size - (fifo->out & (fifo->size - 1)));
    memcpy(buffer, fifo->buffer + (fifo->out & (fifo->size - 1)), l);
    /* then get the rest (if any) from the beginning of the buffer */
    memcpy(buffer + l, fifo->buffer, len - l);
    /*
     * Ensure that we remove the bytes from the kfifo -before-
     * we update the fifo->out index.
     */
    //smp_mb();
    fifo->out += len; //每次累加，到达最大值后溢出，自动转为0
    return len;
}
