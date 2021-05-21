/****************************************************************************
 * @file 	cc112x_spi.c
 * @brief 	Implementation file for basic and neccessary functions
 * 			to communicate with CC112X over SPI
 */

/******************************************************************************
 * INCLUDES
 */
#include "cc112x_spi.h"

/******************************************************************************
 * LOCAL VARIABLES
 */
SPI_HandleTypeDef SPI_Handle;

/******************************************************************************
 * FUNCTIONS
 */

/******************************************************************************
 * INCLUDES
 */

#include "cc112x_spi.h"
/******************************************************************************************
 * Local Variables
 */
SPI_HandleTypeDef SPI_Handle;


/******************************************************************************
 * FUNCTIONS
 */
static void pyxReadWriteBurstSingle(uint8 addr,uint8 *pData,uint16 len);

void initCC1120(SPI_HandleTypeDef hspi)
{
	SPI_Handle = hspi;
}


/******************************************************************************
 * @fn          cc112xSpiReadReg
 *
 * @brief       Read value(s) from config/status/extended radio register(s).
 *              If len  = 1: Reads a single register
 *              if len != 1: Reads len register values in burst mode
 *
 * input parameters
 *
 * @param       addr   - address of first register to read
 * @param       *pData - pointer to data array where read bytes are saved
 * @param       len   - number of bytes to read
 *
 * output parameters
 *
 * @return      rfStatus_t
 */
rfStatus_t cc112xSpiReadReg(uint16 addr, uint8 *pData, uint8 len)
{
  uint8 tempExt  = (uint8)(addr>>8);
  uint8 tempAddr = (uint8)(addr & 0x00FF);
  uint8 rc;

  /* Checking if this is a FIFO access -> returns chip not ready  */
  if((CC112X_SINGLE_TXFIFO<=tempAddr)&&(tempExt==0)) return STATUS_CHIP_RDYn_BM;

  /* Decide what register space is accessed */
  if(!tempExt)
  {
    rc = pyx8BitRegAccess((RADIO_BURST_ACCESS|RADIO_READ_ACCESS),tempAddr,pData,len);
  }
  else if (tempExt == 0x2F)
  {
    rc = pyx16BitRegAccess((RADIO_BURST_ACCESS|RADIO_READ_ACCESS),tempExt,tempAddr,pData,len);
  }
  return (rc);
}

/******************************************************************************
 * @fn          cc112xSpiWriteReg
 *
 * @brief       Write value(s) to config/status/extended radio register(s).
 *              If len  = 1: Writes a single register
 *              if len  > 1: Writes len register values in burst mode
 *
 * input parameters
 *
 * @param       addr   - address of first register to write
 * @param       *pData - pointer to data array that holds bytes to be written
 * @param       len    - number of bytes to write
 *
 * output parameters
 *
 * @return      rfStatus_t
 */
rfStatus_t cc112xSpiWriteReg(uint16 addr, uint8 *pData, uint8 len)
{
  uint8 tempExt  = (uint8)(addr>>8);
  uint8 tempAddr = (uint8)(addr & 0x00FF);
  uint8 rc;

  /* Checking if this is a FIFO access - returns chip not ready */
  if((CC112X_SINGLE_TXFIFO<=tempAddr)&&(tempExt==0)) return STATUS_CHIP_RDYn_BM;

  /* Decide what register space is accessed */
  if(!tempExt)
  {
    rc = pyx8BitRegAccess((RADIO_BURST_ACCESS|RADIO_WRITE_ACCESS),tempAddr,pData,len);
  }
  else if (tempExt == 0x2F)
  {
    rc = pyx16BitRegAccess((RADIO_BURST_ACCESS|RADIO_WRITE_ACCESS),tempExt,tempAddr,pData,len);
  }
  return (rc);
}

/*******************************************************************************
 * @fn          cc112xSpiWriteTxFifo
 *
 * @brief       Write pData to radio transmit FIFO.
 *
 * input parameters
 *
 * @param       *pData - pointer to data array that is written to TX FIFO
 * @param       len    - Length of data array to be written
 *
 * output parameters
 *
 * @return      rfStatus_t
 */
rfStatus_t cc112xSpiWriteTxFifo(uint8 *pData, uint8 len)
{
  uint8 rc;
  rc = pyx8BitRegAccess(RADIO_WRITE_ACCESS|RADIO_BURST_ACCESS,CC112X_BURST_TXFIFO, pData, len);
  return (rc);
}

/*******************************************************************************
 * @fn          cc112xSpiReadRxFifo
 *
 * @brief       Reads RX FIFO values to pData array
 *
 * input parameters
 *
 * @param       *pData - pointer to data array where RX FIFO bytes are saved
 * @param       len    - number of bytes to read from the RX FIFO
 *
 * output parameters
 *
 * @return      rfStatus_t
 */
rfStatus_t cc112xSpiReadRxFifo(uint8 * pData, uint8 len)
{
  uint8 rc;
  rc = pyx8BitRegAccess(RADIO_READ_ACCESS|RADIO_BURST_ACCESS,CC112X_BURST_RXFIFO, pData, len);
  return (rc);
}

/******************************************************************************
 * @fn      cc112xGetTxStatus(void)
 *
 * @brief   This function transmits a No Operation Strobe (SNOP) to get the
 *          status of the radio and the number of free bytes in the TX FIFO.
 *
 *          Status byte:
 *
 *          ---------------------------------------------------------------------------
 *          |          |            |                                                 |
 *          | CHIP_RDY | STATE[2:0] | FIFO_BYTES_AVAILABLE (free bytes in the TX FIFO |
 *          |          |            |                                                 |
 *          ---------------------------------------------------------------------------
 *
 *
 * input parameters
 *
 * @param   none
 *
 * output parameters
 *
 * @return  rfStatus_t
 *
 */
rfStatus_t cc112xGetTxStatus(void)
{
    return(pyxSpiCmdStrobe(CC112X_SNOP));
}

/******************************************************************************
 *
 *  @fn       cc112xGetRxStatus(void)
 *
 *  @brief
 *            This function transmits a No Operation Strobe (SNOP) with the
 *            read bit set to get the status of the radio and the number of
 *            available bytes in the RXFIFO.
 *
 *            Status byte:
 *
 *            --------------------------------------------------------------------------------
 *            |          |            |                                                      |
 *            | CHIP_RDY | STATE[2:0] | FIFO_BYTES_AVAILABLE (available bytes in the RX FIFO |
 *            |          |            |                                                      |
 *            --------------------------------------------------------------------------------
 *
 *
 * input parameters
 *
 * @param     none
 *
 * output parameters
 *
 * @return    rfStatus_t
 *
 */
rfStatus_t cc112xGetRxStatus(void)
{
    return(pyxSpiCmdStrobe(CC112X_SNOP | RADIO_READ_ACCESS));
}




/*******************************************************************************
 * @fn          trx8BitRegAccess
 *
 * @brief       This function performs a read or write from/to a 8bit register
 *              address space. The function handles burst and single read/write
 *              as specfied in addrByte. Function assumes that chip is ready.
 *
 * input parameters
 *
 * @param       accessType - Specifies if this is a read or write and if it's
 *                           a single or burst access. Bitmask made up of
 *                           RADIO_BURST_ACCESS/RADIO_SINGLE_ACCESS/
 *                           RADIO_WRITE_ACCESS/RADIO_READ_ACCESS.
 * @param       addrByte - address byte of register.
 * @param       pData    - data array
 * @param       len      - Length of array to be read(TX)/written(RX)
 *
 * output parameters
 *
 * @return      chip status
 */
rfStatus_t pyx8BitRegAccess(uint8 accessType, uint8 addrByte, uint8 *pData, uint16 len)
{

  uint8 readValue;
  uint8* pRxData = 0x00;


  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET); // Bring chip select low to start

  HAL_SPI_TransmitReceive(&SPI_Handle, (uint8*)(accessType | addrByte), pRxData, 1, 100); // write the address we are accessing
  readValue = *pRxData;

  pyxReadWriteBurstSingle(accessType | addrByte, pData, len); // read or write data

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET); // Bring chip select high to stop

  return readValue;

}

/******************************************************************************
 * @fn          trx16BitRegAccess
 *
 * @brief       This function performs a read or write in the extended adress
 *              space of CC112X.
 *
 * input parameters
 *
 * @param       accessType - Specifies if this is a read or write and if it's
 *                           a single or burst access. Bitmask made up of
 *                           RADIO_BURST_ACCESS/RADIO_SINGLE_ACCESS/
 *                           RADIO_WRITE_ACCESS/RADIO_READ_ACCESS.
 * @param       extAddr - Extended register space address = 0x2F.
 * @param       regAddr - Register address in the extended address space.
 * @param       *pData  - Pointer to data array for communication
 * @param       len     - Length of bytes to be read/written from/to radio
 *
 * output parameters
 *
 * @return      rfStatus_t
 */
rfStatus_t pyx16BitRegAccess(uint8 accessType, uint8 extAddr, uint8 regAddr, uint8 *pData, uint8 len)
{
    // this is for non-extended access
    uint8 readValue;
    uint8* pRxData = 0x00;


    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET); // Bring chip select low to start

    HAL_SPI_TransmitReceive(&SPI_Handle, (uint8*)(accessType | extAddr), pRxData, 1, 100);
    readValue = *pRxData;

    HAL_SPI_Transmit(&SPI_Handle, (uint8*)regAddr, sizeof(regAddr), 100);

    pyxReadWriteBurstSingle(accessType|extAddr, pData, len);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET); // Bring chip select high to stop
    return readValue;
}

/*******************************************************************************
 * @fn          trxSpiCmdStrobe
 *
 * @brief       Send command strobe to the radio. Returns status byte read
 *              during transfer of command strobe. Validation of provided
 *              is not done. Function assumes chip is ready.
 *
 * input parameters
 *
 * @param       cmd - command strobe
 *
 * output parameters
 *
 * @return      status byte
 */
rfStatus_t pyxSpiCmdStrobe(uint8 cmd)
{
  uint8  rc;
  uint8* pRxData = 0x00;

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET); // Bring chip select low to start

  HAL_SPI_TransmitReceive(&SPI_Handle, (uint8*)(cmd), pRxData, 1, 100);
  rc = *pRxData;

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);// Bring chip select high to stop

  return rc;
}

/*******************************************************************************
 * @fn          trxReadWriteBurstSingle
 *
 * @brief       When the address byte is sent to the SPI slave, the next byte
 *              communicated is the data to be written or read. The address
 *              byte that holds information about read/write -and single/
 *              burst-access is provided to this function.
 *
 *              Depending on these two bits this function will write len bytes to
 *              the radio in burst mode or read len bytes from the radio in burst
 *              mode if the burst bit is set. If the burst bit is not set, only
 *              one data byte is communicated.
 *
 *              NOTE: This function is used in the following way:
 *
 *              TRXEM_SPI_BEGIN();
 *              while(TRXEM_PORT_IN & TRXEM_SPI_MISO_PIN);
 *              ...[Depending on type of register access]
 *              trxReadWriteBurstSingle(uint8 addr,uint8 *pData,uint16 len);
 *              TRXEM_SPI_END();
 *
 * input parameters
 *
 * @param       none
 *
 * output parameters
 *
 * @return      void
 */
static void pyxReadWriteBurstSingle(uint8 addr,uint8 *pData,uint16 len)
{
	uint16 i;
	/* Communicate len number of bytes: if RX - the procedure sends 0x00 to push bytes from slave*/
  if(addr&RADIO_READ_ACCESS)
  {
    if(addr&RADIO_BURST_ACCESS)
    {
      for (i = 0; i < len; i++)
      {

          /* Store pData from last pData RX */
          HAL_SPI_TransmitReceive(&SPI_Handle, (0x00), pData, 1, 100);
          pData++;

      }
    }
    else
    {

    	HAL_SPI_TransmitReceive(&SPI_Handle, (0x00), pData, 1, 100);
    }
  }
  else
  {
    if(addr&RADIO_BURST_ACCESS)
    {
      /* Communicate len number of bytes: if TX - the procedure doesn't overwrite pData */
      for (i = 0; i < len; i++)
      {
    	HAL_SPI_Transmit(&SPI_Handle, pData, sizeof(pData), 100);
        pData++;
      }
    }
    else
    {
    	HAL_SPI_Transmit(&SPI_Handle, pData, sizeof(pData), 100);
    }
  }
  return;
}

/*******************************************************************************
*   @fn         registerConfig
*
*   @brief      Write register settings as given by SmartRF Studio found in
*               cc112x_easy_link_reg_config.h
*
*   @param      none
*
*   @return     none
*/
void registerConfig(registerSetting_t * s, uint16_t len) {
    uint8 writeByte;

    // Reset radio
    pyxSpiCmdStrobe(CC112X_SRES);

    HAL_Delay(1000);

    // Write registers to radio
    for(uint16 i = 0; i < len; i++) {
        writeByte = s[i].data;
        cc112xSpiWriteReg(s[i].addr, &writeByte, 1);
    }

    for(uint16 i = 0; i < len; i++) {
        cc112xSpiReadReg(s[i].addr, &writeByte, 1);
        //Serial.println(writeByte, HEX);
        //TODO: Change to HAL_UART_Transmit function
    }
}




