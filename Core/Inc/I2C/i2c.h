#ifndef __I2C__
#define __I2C__

#include "stm32l1xx.h"

typedef struct I2C_User I2C_t;
struct I2C_User {
  I2C_HandleTypeDef *hi2c;
  uint8_t address;
};


void I2C_init(I2C_t* const self, I2C_HandleTypeDef *hi2c, uint8_t address);
HAL_StatusTypeDef I2C_send(const I2C_t *const self, uint8_t *msg, uint32_t size);

#endif
