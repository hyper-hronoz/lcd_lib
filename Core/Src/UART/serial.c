#include "serial.h"

void Serial_print(uint8_t *msg, uint32_t size) {
  HAL_UART_Transmit(serial, msg, size, SERIAL_MAX_DELAY);
}

void Serial_println(uint8_t *msg, uint32_t size) {
  uint8_t ending[] = "\r\n";
  Serial_print(msg, size);
  HAL_UART_Transmit(serial, ending, 2, SERIAL_MAX_DELAY);
}

void Serial_puts(const char *msg) {
  uint32_t text_length = strlen(msg);
  Serial_print((uint8_t*)msg, text_length);
}

void Serial_putsln(const char *msg) {
  uint32_t text_length = strlen(msg);
  Serial_println((uint8_t*)msg, text_length);
}
