#ifndef CRC__H
#define CRC__H

#include <stdint.h>
#include "stm32f1xx_hal.h"

uint32_t CRC32_ForBytes(uint8_t *pData,uint32_t uLen);
uint32_t revbit(uint32_t uData);

#endif
