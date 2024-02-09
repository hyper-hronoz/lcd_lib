#include "i2c.h"


void I2C_init(I2C_t *const self, I2C_HandleTypeDef *hi2c, uint8_t address) {
  self->hi2c = hi2c;
  self->address = address;
}

HAL_StatusTypeDef I2C_send(const I2C_t * const self, uint8_t *msg, uint32_t size) {
  HAL_StatusTypeDef res = HAL_I2C_Master_Transmit(self->hi2c, self->address, msg, size, HAL_MAX_DELAY);
  return HAL_OK;
}
