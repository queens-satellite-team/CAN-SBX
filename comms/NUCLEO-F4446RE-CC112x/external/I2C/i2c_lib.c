#include "i2c_lib.h"

/******************************************************************************************
 * Local Variables
 */
I2C_HandleTypeDef I2C_Handle;


/******************************************************************************************
 * Export Functions
 */
void initI2C(I2C_HandleTypeDef hi2c)
{
	I2C_Handle = hi2c;
}

HAL_StatusTypeDef writeI2C(uint8* pAddr, uint8* pData, uint8 nBytes)
{
	HAL_StatusTypeDef ret;

	ret = HAL_I2C_Master_Transmit(hi2c, pAddr, pData, nBytes, HAL_MAX_DELAY);
}

HAL_StatusTypeDef readI2C(uint8* pAddr, uint8* pData, uint8 nBytes)
{
	HAL_StatusTypeDef ret;

	ret = HAL_I2C_Master_Transmit(hi2c, pAddr, pData, nBytes, HAL_MAX_DELAY);
}
