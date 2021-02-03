#include "Arduino-CC1120x.h"
#include "source.cpp"

byte eeprom_output_data = 0; //receive data
byte eeprom_input_data = 0;  //send data
byte clr = 0;                //clear

  
void setup() 
{
  pinMode(RESET, OUTPUT);          //reset pin --> output
  pinMode(DATAOUT, OUTPUT);        //mosi pin --> output
  pinMode(DATAIN, INPUT);          //miso pin --> input
  pinMode(SPICLOCK, OUTPUT);       //sclk pin --> output
  pinMode(SLAVESELECT, OUTPUT);    //ss pin --> output
  digitalWrite(SLAVESELECT,HIGH);  //disable deivce communication
  digitalWrite(RESET, HIGH);       //reset off
  Serial.begin(9600);              //start Serial
  Serial.println("start program");

Write_eeprom_configuration(IOCFG3, 0xB0);        //write settings to c1120
Write_eeprom_configuration(IOCFG2, 0x06);
Write_eeprom_configuration(IOCFG1, 0xB0);
Write_eeprom_configuration(IOCFG0, 0x40);
Write_eeprom_configuration(SYNC3, 0x93);
Write_eeprom_configuration(SYNC2, 0x0B);
Write_eeprom_configuration(SYNC1,0x51);
Write_eeprom_configuration(SYNC0,0xDE);
Write_eeprom_configuration(SYNC_CFG1,0x0B);
Write_eeprom_configuration(SYNC_CFG0,0x17);
Write_eeprom_configuration(DEVIATION_M, 0x06);
Write_eeprom_configuration(MODCFG_DEV_E, 0x03);
Write_eeprom_configuration(DCFILT_CFG, 0x1C);
Write_eeprom_configuration(PREAMBLE_CFG1, 0x18);
Write_eeprom_configuration(PREAMBLE_CFG0,0x2A);
Write_eeprom_configuration(FREQ_IF_CFG, 0x40);
Write_eeprom_configuration(IQIC,0xC6);
Write_eeprom_configuration(CHAN_BW, 0x14);
Write_eeprom_configuration(MDMCFG1,0x46);
Write_eeprom_configuration(MDMCFG0,0x05);
Write_eeprom_configuration(SYMBOL_RATE2,0x43);
Write_eeprom_configuration(SYMBOL_RATE1,0xA9);
Write_eeprom_configuration(SYMBOL_RATE0,0x2A);
Write_eeprom_configuration(AGC_REF,0x20);
Write_eeprom_configuration(AGC_CS_THR,0x19);
Write_eeprom_configuration(AGC_GAIN_ADJUST,0x00);
Write_eeprom_configuration(AGC_CFG3,0x91);
Write_eeprom_configuration(AGC_CFG2,0x20);
Write_eeprom_configuration(AGC_CFG1,0xA9);
Write_eeprom_configuration(AGC_CFG0,0xCF);
Write_eeprom_configuration(FIFO_CFG,0x00);
Write_eeprom_configuration(DEV_ADDR,0x00);
Write_eeprom_configuration(SETTLING_CFG,0x0B);
Write_eeprom_configuration(FS_CFG,0x14);          //carrier
Write_eeprom_configuration(WOR_CFG1,0x08);
Write_eeprom_configuration(WOR_CFG0,0x21);
Write_eeprom_configuration(WOR_EVENT0_MSB,0x00);
Write_eeprom_configuration(WOR_EVENT0_LSB,0x00);
Write_eeprom_configuration(PKT_CFG2,0x04);
Write_eeprom_configuration(PKT_CFG1,0x05);
Write_eeprom_configuration(PKT_CFG0,0x20);
Write_eeprom_configuration(RFEND_CFG1,0x0F);
Write_eeprom_configuration(RFEND_CFG0,0x00);
Write_eeprom_configuration(PA_CFG2,0x7F);
Write_eeprom_configuration(PA_CFG1,0x56);
Write_eeprom_configuration(PA_CFG0,0x7C);
Write_eeprom_configuration(PKT_LEN,0xFF);
Write_eeprom_extended(IF_MIX_CFG,0x00);
Write_eeprom_extended(FREQOFF_CFG,0x22);
Write_eeprom_extended(TOC_CFG,0x0B);
Write_eeprom_extended(MARC_SPARE,0x00);
Write_eeprom_extended(ECG_CFG,0x00);
Write_eeprom_extended(CFM_DATA_CFG,0x00);
Write_eeprom_extended(EXT_CTRL,0x01);
Write_eeprom_extended(RCCAL_FINE,0x00);
Write_eeprom_extended(RCCAL_COARSE,0x00);
Write_eeprom_extended(RCCAL_OFFSET,0x00);
Write_eeprom_extended(FREQOFF1,0x00);
Write_eeprom_extended(FREQOFF0,0x00);
Write_eeprom_extended(FREQ2,0x6C);
Write_eeprom_extended(FREQ1,0x80);
Write_eeprom_extended(FREQ0,0x00);
Write_eeprom_extended(IF_ADC2,0x02);
Write_eeprom_extended(IF_ADC1,0xA6);
Write_eeprom_extended(IF_ADC0,0x04);
Write_eeprom_extended(FS_DIG1,0x00);
Write_eeprom_extended(FS_DIG0,0x5F);
Write_eeprom_extended(FS_CAL3,0x00);
Write_eeprom_extended(FS_CAL2,0x20);
Write_eeprom_extended(FS_CAL1,0x40);
Write_eeprom_extended(FS_CAL0,0x0E);
Write_eeprom_extended(FS_CHP,0x28);
Write_eeprom_extended(FS_DIVTWO,0x03);
Write_eeprom_extended(FS_DSM1,0x00);
Write_eeprom_extended(FS_DSM0,0x33);
Write_eeprom_extended(FS_DVC1,0xFF);
Write_eeprom_extended(FS_DVC0,0x17);
Write_eeprom_extended(FS_PRE, 0x6E);      
Write_eeprom_extended(FS_REG_DIV_CML, 0x14);       
Write_eeprom_extended(FS_SPARE, 0xAC);              
Write_eeprom_extended(FS_VCO4, 0x14);              
Write_eeprom_extended(FS_VCO3, 0x00);              
Write_eeprom_extended(FS_VCO2, 0x00);               
Write_eeprom_extended(FS_VCO1, 0x00);              
Write_eeprom_extended(FS_VCO0, 0xB4);              
Write_eeprom_extended(GBIAS6, 0x00);              
Write_eeprom_extended(GBIAS5, 0x02);            
Write_eeprom_extended(GBIAS4, 0x00);            
Write_eeprom_extended(GBIAS3, 0x00);             
Write_eeprom_extended(GBIAS2, 0x10);             
Write_eeprom_extended(GBIAS1, 0x00);             
Write_eeprom_extended(GBIAS0, 0x00);             
Write_eeprom_extended(IFAMP, 0x01);              
Write_eeprom_extended(LNA, 0x01);              
Write_eeprom_extended(RXMIX, 0x01);            
Write_eeprom_extended(XOSC5, 0x0E);            
Write_eeprom_extended(XOSC4, 0xA0);            
Write_eeprom_extended(XOSC3, 0x03);            
Write_eeprom_extended(XOSC2, 0x04);            
Write_eeprom_extended(XOSC1, 0x03);            
Write_eeprom_extended(XOSC0, 0x00);            
Write_eeprom_extended(ANALOG_SPARE, 0x00);       
Write_eeprom_extended(PA_CFG3, 0x00);           
Write_eeprom_extended(WOR_TIME1, 0x00);        
Write_eeprom_extended(WOR_TIME0, 0x00);       
Write_eeprom_extended(WOR_CAPTURE1, 0x00);    
Write_eeprom_extended(WOR_CAPTURE0, 0x00);    
Write_eeprom_extended(BIST, 0x00);        
Write_eeprom_extended(DCFILTOFFSET_I1, 0x00);
Write_eeprom_extended(DCFILTOFFSET_I0, 0x00);
Write_eeprom_extended(DCFILTOFFSET_Q1, 0x00);
Write_eeprom_extended(DCFILTOFFSET_Q0, 0x00);
Write_eeprom_extended(IQIE_I1, 0x00);   
Write_eeprom_extended(IQIE_I0, 0x00);  
Write_eeprom_extended(IQIE_Q1, 0x00);  
Write_eeprom_extended(IQIE_Q0, 0x00);  
Write_eeprom_extended(RSSI1, 0x80);   
Write_eeprom_extended(RSSI0, 0x00);   
Write_eeprom_extended(MARCSTATE, 0x41);
Write_eeprom_extended(LQI_VAL, 0x00);  
Write_eeprom_extended(PQT_SYNC_ERR, 0xFF);
Write_eeprom_extended(DEM_STATUS, 0x00);  
Write_eeprom_extended(FREQOFF_EST1, 0x00);
Write_eeprom_extended(FREQOFF_EST0, 0x00);
Write_eeprom_extended(AGC_GAIN3, 0x00);  
Write_eeprom_extended(AGC_GAIN2, 0xD1);  
Write_eeprom_extended(AGC_GAIN1, 0x00);  
Write_eeprom_extended(AGC_GAIN0, 0x3F);  
Write_eeprom_extended(CFM_RX_DATA_OUT, 0x00);
Write_eeprom_extended(CFM_TX_DATA_IN, 0x00); 
Write_eeprom_extended(ASK_SOFT_RX_DATA, 0x30);
Write_eeprom_extended(RNDGEN, 0x7F);   
Write_eeprom_extended(MAGN2, 0x00);   
Write_eeprom_extended(MAGN1, 0x00);   
Write_eeprom_extended(MAGN0, 0x00);   
Write_eeprom_extended(ANG1, 0x00);   
Write_eeprom_extended(ANG0, 0x00);   
Write_eeprom_extended(CHFILT_I2, 0x08);
Write_eeprom_extended(CHFILT_I1, 0x00);
Write_eeprom_extended(CHFILT_I0, 0x00);
Write_eeprom_extended(CHFILT_Q2, 0x00);
Write_eeprom_extended(CHFILT_Q1, 0x00);
Write_eeprom_extended(CHFILT_Q0, 0x00);
Write_eeprom_extended(GPIO_STATUS, 0x00);
Write_eeprom_extended(FSCAL_CTRL, 0x01);   
Write_eeprom_extended(PHASE_ADJUST, 0x00);   
Write_eeprom_extended(PARTNUMBER, 0x00);   
Write_eeprom_extended(PARTVERSION, 0x00);  
Write_eeprom_extended(SERIAL_STATUS, 0x00);
Write_eeprom_extended(MODEM_STATUS1, 0x01);
Write_eeprom_extended(MODEM_STATUS0, 0x00);
Write_eeprom_extended(MARC_STATUS1, 0x00); 
Write_eeprom_extended(MARC_STATUS0, 0x00); 
Write_eeprom_extended(PA_IFAMP_TEST, 0x00);
Write_eeprom_extended(FSRF_TEST, 0x00);   
Write_eeprom_extended(PRE_TEST, 0x00);   
Write_eeprom_extended(PRE_OVR, 0x00);   
Write_eeprom_extended(ADC_TEST, 0x00);  
Write_eeprom_extended(DVC_TEST, 0x0B);  
Write_eeprom_extended(ATEST, 0x40);   
Write_eeprom_extended(ATEST_LVDS, 0x00);
Write_eeprom_extended(ATEST_MODE, 0x00);
Write_eeprom_extended(XOSC_TEST1, 0x3C);
Write_eeprom_extended(XOSC_TEST0, 0x00);
Write_eeprom_extended(RXFIRST, 0x00);   
Write_eeprom_extended(TXFIRST, 0x00);   
Write_eeprom_extended(RXLAST, 0x00);   
Write_eeprom_extended(TXLAST, 0x00);   
Write_eeprom_extended(NUM_TXBYTES, 0x00);
Write_eeprom_extended(NUM_RXBYTES, 0x00);   
Write_eeprom_extended(FIFO_NUM_TXBYTES, 0x0F);
Write_eeprom_extended(FIFO_NUM_RXBYTES, 0x00);

}

void loop() 
{
  SendData(0x56);
  Serial.println(0x56);
  delay(1000);
}