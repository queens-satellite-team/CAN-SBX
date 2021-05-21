#include "uart_lib.h"

/******************************************************************************************
 * Local Variables
 */
UART_HandleTypeDef UART_Handle;


/******************************************************************************************
 * Export Functions
 */
void initUART(UART_HandleTypeDef huart)
{
	UART_Handle = huart;
}

void printString(char* string)
{
	uint8_t buf[strlen(string)];
	strcpy((char*)buf, string);
	HAL_UART_Transmit(&UART_Handle, buf, strlen((char*)buf), HAL_MAX_DELAY);
}


