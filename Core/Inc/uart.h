/*
 * uart.h
 *
 *  Created on: Feb 4, 2025
 *      Author: npedu-204-04
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"

void initUart(UART_HandleTypeDef *inHuart);
char getUart();
char *getMessage();

#endif /* INC_UART_H_ */
