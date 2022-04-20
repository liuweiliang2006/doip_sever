/*
 * utils.h
 *
 *  Created on: Jan 8, 2019
 *      Author: rxiao
 */

#ifndef SOURCES_UTILS_H_
#define SOURCES_UTILS_H_
#include <stdint.h>

typedef enum
{
    Shake_hands                         = 0x000U,    /*!< Generic operation success status */
    spi_com_normal                      = 0x001U
} status_spi;


typedef enum
{
    Shake_hands_req                  = 0x000U,
    soc_com_req                      = 0x001U,
    mcu_com_req                      = 0x002U
} process_spi;
#endif /* SOURCES_UTILS_H_ */
