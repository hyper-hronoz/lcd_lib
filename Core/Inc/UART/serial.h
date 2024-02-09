#ifndef __SERIAL__
#define __SERIAL__

#include "stm32l1xx.h"
#include "exporter.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>

#define SERIAL_MAX_DELAY HAL_MAX_DELAY

static UART_HandleTypeDef *serial = &huart1;


void Serial_print(uint8_t *msg, uint32_t size);
void Serial_println(uint8_t *msg, uint32_t size);
void Serial_puts(const char *msg);
void Serial_putsln(const char *msg);

#endif
