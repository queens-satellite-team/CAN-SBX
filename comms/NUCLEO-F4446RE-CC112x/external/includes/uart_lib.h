#ifndef _UART_H_
#define _UART_H_

/******************************************************************************************
 * Includes
 */
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include "stdio.h"
#include "string.h"

/******************************************************************************************
 * Export Functions
 */
void initUART(UART_HandleTypeDef huart);
void printString(char* string);

void initOBC(UART_HandleTypeDef huart);
void stringToOBC(char* string);
void stringFromOBC(uint8_t* buffer, uint16_t numBytes);

#endif

/******************************************************************************************
 * UART EXAMPLE CODE
 *
 * 1.
 * uint8_t buffer[10];
 * strcpy((char*)buffer, "Hello\r\n");
 * HAL_UART_Transmit(&huart2, buffer, strlen((char*) buffer, HAL_MAX_DELAY);
 *
 * 2.
 * char uart_buffer[10];
 * uart_buffer_length = sprintf(uart_buffer, "Hello\r\n");
 * HAL_UART_Transmit(&huart2, (uint8_t*) uart_buffer, uart_buffer_length, HAL_MAX_DELAY);
 *
 */
