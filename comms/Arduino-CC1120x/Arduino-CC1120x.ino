#define DATAOUT 11     //MOSI --> pin 11
#define DATAIN  12     //MISO --> pin 12
#define SPICLOCK  3   //SCLK --> pin 3
#define SLAVESELECT 10 //SS --> pin 10
#define RESET 9        //RESET --> pin 9


#define WRSR  1        //write protection command ??
#define WRITE 2        //write command
#define READ  3        //read command
#define WRDI  4        //write disable command ??
#define RDSR  5        //buffer command ??
#define WREN  6        //write enable command

#define IOCFG3 0x00    //define configuration registers
#define IOCFG2 0x01
#define IOCFG1 0x02
#define IOCFG0 0x03
#define SYNC3 0x04
#define SYNC2 0x05
#define SYNC1 0x06
#define SYNC0 0x07
#define SYNC_CFG1 0x08
#define SYNC_CFG0 0x09
#define DEVIATION_M 0x0A
#define MODCFG_DEV_E 0x0B
#define DCFILT_CFG 0x0C
#define PREAMBLE_CFG1 0x0D
#define PREAMBLE_CFG0 0x0E
#define FREQ_IF_CFG 0x0F
#define IQIC 0x10
#define CHAN_BW 0x11
#define MDMCFG1 0x12
#define MDMCFG0 0x13
#define SYMBOL_RATE2 0x14
#define SYMBOL_RATE1 0x15
#define SYMBOL_RATE0 0x16
#define AGC_REF 0x17
#define AGC_CS_THR 0x18
#define AGC_GAIN_ADJUST 0x19
#define AGC_CFG3 0x1A
#define AGC_CFG2 0x1B
#define AGC_CFG1 0x1C
#define AGC_CFG0 0x1D
#define FIFO_CFG 0x1E
#define DEV_ADDR 0x1F
#define SETTLING_CFG 0x20
#define FS_CFG 0x21
#define WOR_CFG1 0x22
#define WOR_CFG0 0x23
#define WOR_EVENT0_MSB 0x24
#define WOR_EVENT0_LSB 0x25
#define PKT_CFG2 0x26
#define PKT_CFG1 0x27
#define PKT_CFG0 0x28
#define RFEND_CFG1 0x29
#define RFEND_CFG0 0x2A
#define PA_CFG2 0x2B
#define PA_CFG1 0x2C
#define PA_CFG0 0x2D
#define PKT_LEN 0x2E
#define EXTENDED ADDRESS 0x2F
#define IF_MIX_CFG 0x00    //define extended registers
#define FREQOFF_CFG 0x01
#define TOC_CFG 0x02
#define MARC_SPARE 0x03
#define ECG_CFG 0x04
#define CFM_DATA_CFG 0x05
#define EXT_CTRL 0x06
#define RCCAL_FINE 0x07
#define RCCAL_COARSE 0x08
#define RCCAL_OFFSET 0x09
#define FREQOFF1 0x0A
#define FREQOFF0 0x0B
#define FREQ2 0x0C
#define FREQ1 0x0D
#define FREQ0 0x0E
#define IF_ADC2 0x0F
#define IF_ADC1 0x10
#define IF_ADC0 0x11
#define FS_DIG1 0x12
#define FS_DIG0 0x13
#define FS_CAL3 0x14
#define FS_CAL2 0x15
#define FS_CAL1 0x16
#define FS_CAL0 0x17
#define FS_CHP 0x18
#define FS_DIVTWO 0x19
#define FS_DSM1 0x1A
#define FS_DSM0 0x1B
#define FS_DVC1 0x1C
#define FS_DVC0 0x1D
#define FS_LBI 0x1E
#define FS_PFD 0x1F
#define FS_PRE 0x20
#define FS_REG_DIV_CML 0x21
#define FS_SPARE 0x22
#define FS_VCO4 0x23
#define FS_VCO3 0x24
#define FS_VCO2 0x25
#define FS_VCO1 0x26
#define FS_VCO0 0x27
#define GBIAS6 0x28
#define GBIAS5 0x29
#define GBIAS4 0x2A
#define GBIAS3 0x2B
#define GBIAS2 0x2C
#define GBIAS1 0x2D
#define GBIAS0 0x2E
#define IFAMP 0x2F
#define LNA 0x30
#define RXMIX 0x31
#define XOSC5 0x32
#define XOSC4 0x33
#define XOSC3 0x34
#define XOSC2 0x35
#define XOSC1 0x36
#define XOSC0 0x37
#define ANALOG_SPARE 0x38
#define PA_CFG3 0x39
#define WOR_TIME1 0x64
#define WOR_TIME0 0x65
#define WOR_CAPTURE1 0x66
#define WOR_CAPTURE0 0x67
#define BIST 0x68
#define DCFILTOFFSET_I1 0x69
#define DCFILTOFFSET_I0 0x6A
#define DCFILTOFFSET_Q1 0x6B
#define DCFILTOFFSET_Q0 0x6C
#define IQIE_I1 0x6D
#define IQIE_I0 0x6E
#define IQIE_Q1 0x6F
#define IQIE_Q0 0x70
#define RSSI1 0x71
#define RSSI0 0x72
#define MARCSTATE 0x73
#define LQI_VAL 0x74
#define PQT_SYNC_ERR 0x75
#define DEM_STATUS 0x76
#define FREQOFF_EST1 0x77
#define FREQOFF_EST0 0x78
#define AGC_GAIN3 0x79
#define AGC_GAIN2 0x7A
#define AGC_GAIN1 0x7B
#define AGC_GAIN0 0x7C
#define CFM_RX_DATA_OUT 0x7D
#define CFM_TX_DATA_IN 0x7E
#define ASK_SOFT_RX_DATA 0x7F
#define RNDGEN 0x80
#define MAGN2 0x81
#define MAGN1 0x82
#define MAGN0 0x83
#define ANG1 0x84
#define ANG0 0x85
#define CHFILT_I2 0x86
#define CHFILT_I1 0x87
#define CHFILT_I0 0x88
#define CHFILT_Q2 0x89
#define CHFILT_Q1 0x8A
#define CHFILT_Q0 0x8B
#define GPIO_STATUS 0x8C
#define FSCAL_CTRL 0x8D
#define PHASE_ADJUST 0x8E
#define PARTNUMBER 0x8F
#define PARTVERSION 0x90
#define SERIAL_STATUS 0x91
#define MODEM_STATUS1 0x92
#define MODEM_STATUS0 0x93
#define MARC_STATUS1 0x94
#define MARC_STATUS0 0x95
#define PA_IFAMP_TEST 0x96
#define FSRF_TEST 0x97
#define PRE_TEST 0x98
#define PRE_OVR 0x99
#define ADC_TEST 0x9A
#define DVC_TEST 0x9B
#define ATEST 0x9C
#define ATEST_LVDS 0x9D
#define ATEST_MODE 0x9E
#define XOSC_TEST1 0x9F
#define XOSC_TEST0 0xA0
#define RXFIRST 0xD2
#define TXFIRST 0xD3
#define RXLAST 0xD4
#define TXLAST 0xD5
#define NUM_TXBYTES 0xD6
#define NUM_RXBYTES 0xD7
#define FIFO_NUM_TXBYTES 0xD8
#define FIFO_NUM_RXBYTES 0xD9



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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SendData(byte data)                        //send data
{
  Write_eeprom_strobe(0x36);                     //Set to IDLE MODE
  delay(20);
  Write_eeprom_strobe(0x35);                     //Set to TX MODE
  delay(20);
        
 Write_eeprom_strobe(0x31);                //SFSTXON
 delay(10);
 Write_eeprom_strobe(0x3F);                //txfifo, size
 delay(10);
 Write_eeprom_strobe(data);                //txfifo, data, size
 delay(10);
 Write_eeprom_strobe(0x35);                //stx
 //while (!digitalRead(IOCFG0));     // Wait for GDO0 to be set -> sync transmitted  
 //while (digitalRead(IOCFG0));      // Wait for GDO0 to be cleared -> end of packet
 delay(10);
        Write_eeprom_strobe(0x3B);                //flush tx fifo
}

byte Receive_data()                               //receive data
{
  Write_eeprom_strobe(0x36);                      //Set to IDLE MODE
  delay(10);
  Write_eeprom_strobe(0x34);                      //Set to RX MODE
  delay(10);
  
  byte size;
  byte status[2];
  if(Read_eeprom_extended(0xD7))            // BYTES_IN_RXFIFO
  {
    Write_eeprom_strobe(0x3A);
    return size;
  }
  else
  {
    Write_eeprom_strobe(0x3A); 
    return 0;
  } 
}

byte Read_eeprom_configuration(int EEPROM_address)    //read from Configuration Register
{
  int data;
  digitalWrite(SLAVESELECT,LOW);             //enable device communication 
  Send_SPI((char)(EEPROM_address+0x80)); //send adrress
  data = Send_SPI(0xFF);                 //get data
  digitalWrite(SLAVESELECT,HIGH);            //disable device communication 
  return data;                               //return data
}

byte Read_eeprom_extended(int EEPROM_address) //read from Extended Register
{
  int data;
  digitalWrite(SLAVESELECT,LOW);             //enable device communication 
  Send_SPI((char)(0xAF));                //send address 1
  Send_SPI((char)(EEPROM_address));      //send address 2
  data = Send_SPI(0xFF);                 //get data
  digitalWrite(SLAVESELECT,HIGH);            //disable device communication 
  return data;                               //return data
}

byte Read_eeprom_direct(int EEPROM_address)    //read from Direct Memory Access Register
{
  int data;
  digitalWrite(SLAVESELECT,LOW);            //enable device communication 
  Send_SPI((char)(0xBE));              //send adrress 1
  Send_SPI((char)(EEPROM_address));     //send address 2
  data = Send_SPI(0xFF);                //get data
  digitalWrite(SLAVESELECT,HIGH);           //disable device communication 
  return data;                              //return data
}

void Write_eeprom_configuration(int EEPROM_address, int EEPROM_data)    //write to Configuration Register
{  
  digitalWrite(SLAVESELECT,LOW);             //enable device communication 
  Send_SPI((char)(EEPROM_address));      //send address
  Send_SPI((char)(EEPROM_data));         //send data
  digitalWrite(SLAVESELECT,HIGH);            //disable device communication 
}

void Write_eeprom_strobe(int EEPROM_data)    //write Command Strobe
{  
  digitalWrite(SLAVESELECT,LOW);             //enable device communication 
  //spi_transfer((char)(EEPROM_data));         //send command
  Send_SPI((char)(EEPROM_data));
  delay(10);
  digitalWrite(SLAVESELECT,HIGH);            //disable device communication 
}

void Write_eeprom_extended(int EEPROM_address, int EEPROM_data)    //write to Extended Register
{  
  digitalWrite(SLAVESELECT,LOW);             //enable device communication 
  Send_SPI((char)(0x2F));                //send address 1
  Send_SPI((char)(EEPROM_address));      //send address 2
  Send_SPI((char)(EEPROM_data));         //send data
  digitalWrite(SLAVESELECT,HIGH);            //disable device communication 
}

void Write_eeprom_direct(int EEPROM_address, int EEPROM_data)    //write to Direct Memory Access Register
{  
  digitalWrite(SLAVESELECT,LOW);             //enable device communication 
  Send_SPI((char)(0x3E));                //send address 1
  Send_SPI((char)(EEPROM_address));      //send address 2
  Send_SPI((char)(EEPROM_data));         //send data
  digitalWrite(SLAVESELECT,HIGH);            //disable device communication 
}


char Send_SPI(char verzenden){
  uint8_t so = 0x00;
  uint8_t i = 0;
  //NSDELAY
  // data transfer
  for (i = 8; i > 0; i--) {
    // Slave Input write
    digitalWrite(DATAOUT, (verzenden >> i-1) & 0x01);
    // SCLK up
    digitalWrite(SPICLOCK, HIGH);
    // Slave Output read
    so |= (uint8_t) digitalRead(DATAIN) << i-1;
    // wait t_hd = 10 ns
    //NSDELAY
    // SCLK down
    digitalWrite(SPICLOCK, LOW);
    // wait t_sd = 10 ns
    //NSDELAY
  }
        return verzenden;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
