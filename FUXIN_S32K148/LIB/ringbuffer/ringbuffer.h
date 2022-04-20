/*
 * ringbuffer.h
 *
 *  Created on: 2021年5月25日
 *      Author: Administrator
 */

#ifndef RINGBUFFER_RINGBUFFER_H_
#define RINGBUFFER_RINGBUFFER_H_

/** 环形缓存区数据结构 */
typedef struct {
    uint16_t rbCapacity;//空间大小
    uint8_t  *rbHead; //头 read
    uint8_t  *rbTail; //尾
    uint8_t  *rbBuff; //数据首地址
}rb_t;

extern rb_t wholePackageSpirbTx;

uint16_t rb_start_tail(rb_t *rb);
uint16_t rb_get_head(rb_t *rb);
int32_t get_write_space(rb_t *rb);
int32_t rbWrite(rb_t *rb, const void *data, uint16_t count);
int32_t rbRead(rb_t *rb, void *data, uint16_t count);
int32_t spi_ring_write(uint8_t *data,uint16_t len);
uint16_t spi_ring_read(uint8_t *p);
uint16_t spi_hand_ring_read(uint8_t *p,uint16_t count);
void rbCreate(rb_t* rb,uint8_t *Buff,uint32_t BuffLen);
uint16_t rbCanWrite(rb_t *rb);




#endif /* RINGBUFFER_RINGBUFFER_H_ */
