/*
 * author:  sean tedesco
 * email:   17sart@queensu.ca
 * date:    July 1st, 2021
 * 
 * ARDUINO I2C PINOUTS
 * GPIO18 (PIN A4)  -> SDA
 * GPIO19 (PIN A5)  -> SCL
 * GND              -> Ground
 * 
 * TO DO:
 *    - implement multiple callback functions which are called depending on received command from master 
 *    - implement "I2C manager" class to handle read/write operations with call backs
 *    - support different data types (only works with <char> currently)
 *    
 * - please reach out for any and all questions - 
*/

#include <Wire.h>

#define SLAVE_ADDRESS 0x04 
#define RX_BUFFER_SIZE 256
#define TX_BUFFER_SIZE 5

char data_rx[RX_BUFFER_SIZE];
char data_tx[TX_BUFFER_SIZE];
int tx_index = 0;

char letter = '!';

void setup() {
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
  
  data_tx[0] = 'a';
 ;
}

void loop() {
  data_tx[4] = letter;
  letter++;
  if((int)letter > 126){
    letter = '!';
  }
  delay(500);
  Serial.println(letter);
}


void receiveData(int byteCount) {
  int i = 0;
  while (Wire.available()) {
    data_rx[i] = Wire.read();
    i++;
  }
  data_rx[i] = '\0';
  Serial.print(data_rx);
}

// callback for sending data
void sendData() {
  Wire.write(data_tx[tx_index]);
  tx_index++;
  if(tx_index >= TX_BUFFER_SIZE){
    tx_index = 0;
  }
}
