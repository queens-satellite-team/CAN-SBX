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

char Send_SPI(char verzenden)
{
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