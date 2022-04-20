/*
 * ringbuffer_fml.h
 *
 *  Created on: 2021Äê5ÔÂ31ÈÕ
 *      Author: Administrator
 */

#ifndef RINGBUFFER_RINGBUFFER_FML_H_
#define RINGBUFFER_RINGBUFFER_FML_H_

void ringbuffer_creat_fml(void);
void can_ringbuffer_creat_fml(void);
void whole_package_spiring_creat_fml(void);
uint16_t whole_package_spiring_read_fml(uint8_t *p,uint16_t lens);
int32_t get_write_space_fml(rb_t *rb);

/*****UART ringbuffer operate*****/
void uartsoc_ringbuffer_creat_fml(void);
void uartsoc_ring_write_fml(uint8_t *data,uint16_t len);
uint16_t uartsoc_ring_read_fml(uint8_t *p);
uint16_t uartsoc_ring_can_read_fml(void);
#endif /* RINGBUFFER_RINGBUFFER_FML_H_ */
