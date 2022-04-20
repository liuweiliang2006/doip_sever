/*
 * ringbuffer.c
 *
 *  Created on: 2021Äê5ÔÂ25ÈÕ
 *      Author: Administrator
 */
#include "string.h"
#include <stdio.h>
#include "ringbuffer.h"

uint16_t rb_capacity(rb_t *rb)
{
    return rb->rbCapacity;
}
uint16_t rb_start_tail(rb_t *rb)
{
    //return rb->rbCapacity;
    return (rb->rbTail-rb->rbBuff);
}
uint16_t rb_get_head(rb_t *rb)
{
    //return rb->rbCapacity;
    return (rb->rbHead-rb->rbBuff);
}
uint16_t rbCanRead(rb_t *rb)
{
    if (rb->rbHead == rb->rbTail)
    {

        return 0;
    }

    if (rb->rbHead < rb->rbTail)
    {

        return rb->rbTail - rb->rbHead;

    }
    if (rb->rbHead > rb->rbTail)
    {

    return rb_capacity(rb) - (rb->rbHead - rb->rbTail);

    }
}

uint16_t rbCanWrite(rb_t *rb)
{
    return rb_capacity(rb) - rbCanRead(rb);
}
#define min(a, b) (((a) < (b)) ? (a) : (b))
void rbCreate(rb_t* rb,uint8_t *Buff,uint32_t BuffLen)
{
    if(NULL == rb)
    {
        return;
    }
    rb->rbCapacity = BuffLen;
    rb->rbBuff = Buff;
    rb->rbHead = rb->rbBuff;
    rb->rbTail = rb->rbBuff;
}

int32_t rbWrite(rb_t *rb, const void *data, uint16_t count)
{

    int tailAvailSz = 0;
    if(NULL == rb)
     {
         return -1;
     }
     if(NULL == data)
     {
         return -1;
     }
    if (count >= rbCanWrite(rb))
      {
          return -1;
      }

    if (rb->rbHead <= rb->rbTail)
    {

        tailAvailSz = rb_capacity(rb) - (rb->rbTail - rb->rbBuff);
        if (count <= tailAvailSz)
        {

            memcpy(rb->rbTail, data, count);
            rb->rbTail += count;

            if (rb->rbTail == rb->rbBuff+rb_capacity(rb))
            {
                rb->rbTail = rb->rbBuff;
            }
            return count;
        }
        else
        {

            memcpy(rb->rbTail, data, tailAvailSz);
            rb->rbTail = rb->rbBuff;

            return tailAvailSz + rbWrite(rb, (char*)data+tailAvailSz, count-tailAvailSz);
        }
    }
    else
    {

      memcpy(rb->rbTail, data, count);
      rb->rbTail += count;

      return count;
    }

}

int32_t rbRead(rb_t *rb, void *data, uint16_t count)
{
    int copySz = 0;
    if(NULL == rb)
    {
        return -1;
    }
    if(NULL == data)
    {
        return -1;
    }
    if (rb->rbHead == rb->rbTail)
    {

         return 0;
    }

    if (rb->rbHead < rb->rbTail)
    {

        copySz = min(count, rbCanRead(rb));
        memcpy(data, rb->rbHead, copySz);
        rb->rbHead += copySz;
        return copySz;
    }
    else
    {

        if (count < rb_capacity(rb)-(rb->rbHead - rb->rbBuff))
        {

            copySz = count;
            memcpy(data, rb->rbHead, copySz);
            rb->rbHead += copySz;
            return copySz;
        }
        else
        {

            if (count >= rbCanRead(rb))
            {
            //    return -1;
            }
            copySz = rb_capacity(rb) - (rb->rbHead - rb->rbBuff);
            memcpy(data, rb->rbHead, copySz);
            rb->rbHead = rb->rbBuff;
            copySz += rbRead(rb, (char*)data+copySz, count-copySz);
            return copySz;
        }
    }
}




