#ifndef USART_H_
#define USART_H_

#include "stm32f4xx_usart.h"

int usart_write(const char *s);
void init_usart(USART_TypeDef *usart, void (*cb)(const char));

#endif
