#ifndef INCLUDES_I2C_LIB_H_
#define INCLUDES_I2C_LIB_H_

/******************************************************************************************
 * Includes
 */
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"

/******************************************************************************************
 * Export Functions
 */
void initI2C(I2C_HandleTypeDef hi2c);
HAL_StatusTypeDef writeI2C(uint8* pAddr, uint8* pData, uint8 nBytes);
HAL_StatusTypeDef readI2C(uint8* pAddr, uint8* pData, uint8 nBytes);


#endif /* INCLUDES_I2C_LIB_H_ */
