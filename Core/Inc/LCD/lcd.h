#ifndef __LCD__
#define __LCD__

#include "stm32l1xx.h"

#include "i2c.h"

#define LCD_COMMAND_DISPLAY_CLS  0b00000001, 0
#define LCD_COMMAND_DISPLAY_NORMAL_REGIME_CURSOR_OFF  0b00001100, 0
#define LCD_COMMAND_DISPLAY_CURSOR_BEGIN  0b00000010, 0
#define LCD_COMMAND_DISPLAY_8_BIT 0b00110000, 0
#define LCD_COMMAND_NEW_LINE 0b11000000, 0
typedef struct LCD_t {
  I2C_t* i2c;
} LCD_t;


void LCD_init(LCD_t *const self, I2C_t *i2c);
HAL_StatusTypeDef LCD_send(const LCD_t *const self, uint8_t data, uint8_t flags);
HAL_StatusTypeDef LCD_send_string(const LCD_t * const self, char *str);


#endif
