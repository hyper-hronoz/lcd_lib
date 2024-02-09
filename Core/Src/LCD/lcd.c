#include "lcd.h"
#include "exporter.h"


void LCD_init(LCD_t *const self, I2C_t *i2c) {
  self->i2c = i2c;
}

HAL_StatusTypeDef LCD_send_string(const LCD_t *const me, char *str) {

  uint8_t i = 0;
  while (*str) {
    LCD_send(me, (uint8_t)(*str), 1);
    str++;
    i++;
    if (i == 16) {
      LCD_send(me, LCD_COMMAND_NEW_LINE);
    }
  }

  return HAL_OK;
}

#define PIN_RS (1 << 0)
#define PIN_EN (1 << 2)
#define BACKLIGHT (1 << 3)
HAL_StatusTypeDef LCD_send(const LCD_t *lcd, uint8_t data, uint8_t flags) {

  HAL_StatusTypeDef res;

  for (;;) {
    res = HAL_I2C_IsDeviceReady(lcd->i2c->hi2c, lcd->i2c->address, 1, HAL_MAX_DELAY);
    if (res == HAL_OK)
      break;
  }

  uint8_t up = data & 0xF0;
  // то же самое, но data сдвигается на 4 бита влево
  uint8_t lo = (data << 4) & 0xF0;
  uint8_t data_arr[4];
  // 4-7 биты содержат информацию, биты 0-3 настраивают работу дисплея
  data_arr[0] = up | flags | BACKLIGHT | PIN_EN;
  // дублирование сигнала, на выводе Е в этот раз 0
  data_arr[1] = up | flags | BACKLIGHT;
  data_arr[2] = lo | flags | BACKLIGHT | PIN_EN;
  data_arr[3] = lo | flags | BACKLIGHT;

  res = I2C_send(lcd->i2c, data_arr, sizeof(data_arr));

  HAL_Delay(5);

  return res;
}

