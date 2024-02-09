#include "index.h"
#include "lcd.h"

#define UART_TIMEOUT 1000


void user_before_while() {
  Serial_putsln("Hello");
  Serial_putsln("Starting the bus i2c scanner");

  HAL_StatusTypeDef res;
  int16_t available_adresses[10] = {-1};
  uint8_t available_adresses_index = 0;
  for (uint8_t i = 0; i < 128; i++) {
    res = HAL_I2C_IsDeviceReady(&hi2c1, i << 1, 1, HAL_MAX_DELAY);
    if (res == HAL_OK) {
      available_adresses[available_adresses_index] = i << 1;
      available_adresses_index++;
    }
  }

  Serial_putsln("Available adresses:");
  for (uint16_t i = 0;
       i < sizeof(available_adresses) / sizeof(available_adresses[0]); i++) {
    char msg[64] = {0};
    if (available_adresses[i] > 0) {
      snprintf(msg, sizeof(msg), "0x%02X", available_adresses[i]);
      Serial_println(msg, sizeof(msg));
    }
  }

  I2C_t i2c;
  I2C_init(&i2c, &hi2c1, available_adresses[0]);
  LCD_t lcd;
  LCD_init(&lcd, &i2c);

  LCD_send(&lcd, LCD_COMMAND_DISPLAY_8_BIT);
  LCD_send(&lcd, LCD_COMMAND_DISPLAY_CURSOR_BEGIN);
  LCD_send(&lcd, LCD_COMMAND_DISPLAY_NORMAL_REGIME_CURSOR_OFF);
  LCD_send(&lcd, LCD_COMMAND_DISPLAY_CLS);
  LCD_send_string(&lcd, "Deus sactus deum!");
}

void user_loop() {
  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
  HAL_Delay(1000);
}

void user_loop_end() {}
