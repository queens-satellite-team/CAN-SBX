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
 *    - update SLAVE_ADDRESS to be 0x11
 *    - include current values in a buffer called data_tx ( just make sure that the buffer in main loop is the same buffer called in sendData() ).  
 *    - cast data in data_tx buffer as char (we can really only send one byte or char at a time).
 *          - can not be a float. If decimal values are needed, multiply out and let Jake Miley know. 
 *    - package important data with a tag, time stamp, and the actual data (for example: <S1$01:02:0102$00212100>)
 *          - < > start and end characters 
 *          - $ seperates data pieces
 *          - S1 indicates sensor 1
 *          - 01:02:0102  time in hours, minutes, seconds
 *          - 002121000 current measurement expressed in mA
 *    - package must have a fixed length for all readings
 *    
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
