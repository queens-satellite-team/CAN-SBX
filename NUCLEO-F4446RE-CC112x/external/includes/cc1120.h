/*
 * Header file for CC1120 transceiver
 * QSET - Satellite - Communications
 * Written January 2021
 */

#ifndef CC1120_H_
#define CC1120_H_

#include "stm32f4xx_hal.h"


//transceiver states
typedef enum{
	IDLE = 0x00,
	RX = 0x10,
	TX = 0x20,
	FSTXON = 0x30,
	CALIBRATE = 0x40,
	SETTLING = 0x50,
	RXFIFOERROR = 0x60,
	TXFIFOERROR = 0x70,
	CHIP_READY_N = 0x80
} CC1120_States;


// configuration registers
typedef enum
{
  IOCFG3 = 0x00,
  IOCFG2 = 0x01,
  IOCFG1 = 0x02,
  IOCFG0 = 0x03,
  SYNC3 = 0x04,
  SYNC2 = 0x05,
  SYNC1 = 0x06,
  SYNC0 = 0x07,
  SYNC_CFG1 = 0x08,
  SYNC_CFG0 = 0x09,
  DEVIATION_M = 0x0A,
  MODCFG_DEV_E = 0x0B,
  DCFILT_CFG = 0x0C,
  PREAMBLE_CFG1 = 0x0D,
  PREAMBLE_CFG0 = 0x0E,
  FREQ_IF_CFG = 0x0F,
  IQIC = 0x10,
  CHAN_BW = 0x11,
  MDMCFG1 = 0x12,
  MDMCFG0 = 0x13,
  SYMBOL_RATE2 = 0x14,
  SYMBOL_RATE1 = 0x15,
  SYMBOL_RATE0 = 0x16,
  GC_REF = 0x17,
  AGC_CS_THR = 0x18,
  AGC_GAIN_ADJUST = 0x19,
  AGC_CFG3 = 0x1A,
  AGC_CFG2 = 0x1B,
  AGC_CFG1 = 0x1C,
  AGC_CFG0 = 0x1D,
  FIFO_CFG = 0x1E,
  DEV_ADDR = 0x1F,
  SETTLING_CFG = 0x20,
  FS_CFG = 0x21,
  WOR_CFG1 = 0x22,
  WOR_CFG0 = 0x23,
  WOR_EVENT0_MSB = 0x24,
  WOR_EVENT0_LSB = 0x25,
  PKT_CFG2 = 0x26,
  PKT_CFG1 = 0x27,
  PKT_CFG0 = 0x28,
  RFEND_CFG1 = 0x29,
  RFEND_CFG0 = 0x2A,
  PA_CFG2 = 0x2B,
  PA_CFG1 = 0x2C,
  PA_CFG0 = 0x2D,
  PKT_LEN = 0x2E
} CC1120_Registers;


//extended registers
typedef enum {
	EXTENDED_ADDRESS = 0x2F,
	IF_MIX_CFG = 0x00,
	FREQOFF_CFG = 0x01,
	TOC_CFG = 0x02,
	MARC_SPARE = 0x03,
	ECG_CFG = 0x04,
	CFM_DATA_CFG = 0x05,
	EXT_CTRL = 0x06,
	RCCAL_FINE = 0x07,
	RCCAL_COARSE = 0x08,
	RCCAL_OFFSET = 0x09,
	FREQOFF1 = 0x0A,
	FREQOFF0 = 0x0B,
	FREQ2 = 0x0C,
	FREQ1 = 0x0D,
	FREQ0 = 0x0E,
	IF_ADC2 = 0x0F,
	IF_ADC1 = 0x10,
	IF_ADC0 = 0x11,
	FS_DIG1 = 0x12,
	FS_DIG0 = 0x13,
	FS_CAL3 = 0x14,
	FS_CAL2 = 0x15,
	FS_CAL1 = 0x16,
	FS_CAL0 = 0x17,
	FS_CHP = 0x18,
	FS_DIVTWO = 0x19,
	FS_DSM1 = 0x1A,
	FS_DSM0 = 0x1B,
	FS_DVC1 = 0x1C,
	FS_DVC0 = 0x1D,
	FS_LBI = 0x1E,
	FS_PFD = 0x1F,
	FS_PRE = 0x20,
	FS_REG_DIV_CML = 0x21,
	FS_SPARE = 0x22,
	FS_VCO4 = 0x23,
	FS_VCO3 = 0x24,
	FS_VCO2 = 0x25,
	FS_VCO1 = 0x26,
	FS_VCO0 = 0x27,
	GBIAS6 = 0x28,
	GBIAS5 = 0x29,
	GBIAS4 = 0x2A,
	GBIAS3 = 0x2B,
	GBIAS2 = 0x2C,
	GBIAS1 = 0x2D,
	GBIAS0 = 0x2E,
	IFAMP = 0x2F,
	LNA = 0x30,
	RXMIX = 0x31,
	XOSC5 = 0x32,
	XOSC4 = 0x33,
	XOSC3 = 0x34,
	XOSC2 = 0x35,
	XOSC1 = 0x36,
	XOSC0 = 0x37,
	ANALOG_SPARE = 0x38,
	PA_CFG3 = 0x39,
	WOR_TIME1 = 0x64,
	WOR_TIME0 = 0x65,
	WOR_CAPTURE1 = 0x66,
	WOR_CAPTURE0 = 0x67,
	BIST = 0x68,
	DCFILTOFFSET_I1 = 0x69,
	DCFILTOFFSET_I0 = 0x6A,
	DCFILTOFFSET_Q1 = 0x6B,
	DCFILTOFFSET_Q0 = 0x6C,
	IQIE_I1 = 0x6D,
	IQIE_I0 = 0x6E,
	IQIE_Q1 = 0x6F,
	IQIE_Q0 = 0x70,
	RSSI1 = 0x71,
	RSSI0 = 0x72,
	MARCSTATE = 0x73,
	LQI_VAL = 0x74,
	PQT_SYNC_ERR = 0x75,
	DEM_STATUS = 0x76,
	FREQOFF_EST1 = 0x77,
	FREQOFF_EST0 = 0x78,
	AGC_GAIN3 = 0x79,
	AGC_GAIN2 = 0x7A,
	AGC_GAIN1 = 0x7B,
	AGC_GAIN0 = 0x7C,
	CFM_RX_DATA_OUT = 0x7D,
	CFM_TX_DATA_IN = 0x7E,
	ASK_SOFT_RX_DATA = 0x7F,
	RNDGEN = 0x80,
	MAGN2 = 0x81,
	MAGN1 = 0x82,
	MAGN0 = 0x83,
	ANG1 = 0x84,
	ANG0 = 0x85,
	CHFILT_I2 = 0x86,
	CHFILT_I1 = 0x87,
	CHFILT_I0 = 0x88,
	CHFILT_Q2 = 0x89,
	CHFILT_Q1 = 0x8A,
	CHFILT_Q0 = 0x8B,
	GPIO_STATUS = 0x8C,
	FSCAL_CTRL = 0x8D,
	PHASE_ADJUST = 0x8E,
	PARTNUMBER = 0x8F,
	PARTVERSION = 0x90,
	SERIAL_STATUS = 0x91,
	MODEM_STATUS1 = 0x92,
	MODEM_STATUS0 = 0x93,
	MARC_STATUS1 = 0x94,
	MARC_STATUS0 = 0x95,
	PA_IFAMP_TEST = 0x96,
	FSRF_TEST = 0x97,
	PRE_TEST = 0x98,
	PRE_OVR = 0x99,
	ADC_TEST = 0x9A,
	DVC_TEST = 0x9B,
	ATEST = 0x9C,
	ATEST_LVDS = 0x9D,
	ATEST_MODE = 0x9E,
	XOSC_TEST1 = 0x9F,
	XOSC_TEST0 = 0xA0,
	RXFIRST = 0xD2,
	TXFIRST = 0xD3,
	RXLAST = 0xD4,
	TXLAST = 0xD5,
	NUM_TXBYTES = 0xD6,
	NUM_RXBYTES = 0xD7,
	FIFO_NUM_TXBYTES = 0xD8,
	FIFO_NUM_RXBYTES = 0xD9
} CC1120_Extended_Registers;


// command strobes
typedef enum
{
  SRES = 0x30,
  SFSTXON = 0x32,
  SXOFF = 0x32,
  SCAL = 0x33,
  SRX = 0x34,
  STX = 0x35,
  SIDLE = 0x36,
  SAFC = 0x37,
  SWOR = 0x38,
  SPWD = 0x39,
  SFRX = 0x3A,
  SFTX = 0x3B,
  SWORRST = 0x3C,
  SNOP = 0x3D
} CC1120_Command_Strobes;


void UARTInit(UART_HandleTypeDef *UARTHandle);
void CC1120Init(SPI_HandleTypeDef *SPIHandle);
void printToTerminal(char *str);

uint8_t writeToRegister(CC1120_Registers reg, uint8_t TXData);
void writeToRegisterExtended(CC1120_Registers reg, uint8_t TXData);
void readFromRegister(CC1120_Registers reg);
void readFromRegisterExtended(CC1120_Registers reg);

#endif
