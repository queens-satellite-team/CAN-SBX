/*
 * Source file for CC1120 transceiver
 * QSET - Satellite - Communications
 * Written January 2021
 */

#include "cc1120.h"
#include "stm32f4xx_hal_spi.h"
#include "stm32f4xx_hal_uart.h"

UART_HandleTypeDef *huart = 0x0;
SPI_HandleTypeDef *hspi = 0x0;


void UARTInit(UART_HandleTypeDef *UARTHandle){
	// provides the UART handle for source file
	huart = UARTHandle;
}


void printToTerminal(char *str){
	// print message to terminal for debugging
	int len = strlen(str);
	HAL_UART_Transmit(huart, (uint8_t *) str, len, 100);
}


void CC1120Init(SPI_HandleTypeDef *SPIHandle){
	// initialize all registers in the transceiver
	hspi = 	SPIHandle;
}


uint8_t writeToRegister(CC1120_Registers reg, uint8_t TXData){
	// write one byte to a specified configuration register

	//return status data
	uint8_t RXData = 0x0;

	// CC1120 requires register address to be sent first,
	do{
		if( HAL_SPI_TransmitReceive(hspi, reg, RXData, 1, 100) != HAL_OK )
		{
			printToTerminal("Register Write Fail: Address Error.\n\r");
		}
	// RXData bit 7 must be low for chip to be ready
	// RXData bit 6:4 must be low to be in IDLE state
	} while( RXData == (IDLE | CHIP_READY_N) );

	// once address is successfully sent, data is expected in the next byte
	if( HAL_SPI_TransmitReceive(hspi, TXData, RXData, 1, 100) != HAL_OK )
	{
		printToTerminal("Register Write Fail: Data Error.\n\r");
	}
}


void writeToRegisterExtended(CC1120_Registers reg, uint8_t value){
	// write one byte to a specified configuration register in the extended address space

}


void readFromRegister(CC1120_Registers reg){
	// read one byte from a specified configuration register

}


void readFromRegisterExtended(CC1120_Registers reg){
	// read one byte from a specified configuration register in the extended address space

}
