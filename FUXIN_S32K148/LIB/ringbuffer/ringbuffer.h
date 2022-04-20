/*
 * ringbuffer.h
 *
 *  Created on: 2021��5��25��
 *      Author: Administrator
 */

#ifndef RINGBUFFER_RINGBUFFER_H_
#define RINGBUFFER_RINGBUFFER_H_

/** ���λ��������ݽṹ */
typedef struct {
    uint16_t rbCapacity;//�ռ��С
    uint8_t  *rbHead; //ͷ read
    uint8_t  *rbTail; //β
    uint8_t  *rbBuff; //�����׵�ַ
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
