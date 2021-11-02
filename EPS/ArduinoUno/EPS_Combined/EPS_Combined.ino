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
 *    - include current values in a buffer called data_tx ( just make sure that the buffer in main loop is the same buffer called in sendData() ).  
 *    - cast data in data_tx buffer as char (we can really only send one byte or char at a time).
 *          - can not be a float. If decimal values are needed, multiply out and let Jake Milley know. 
 *    - package important data with a tag, time stamp, and the actual data (for example: <S1$00212100>)
 *          - < > start and end characters 
 *          - $ seperates data pieces
 *          - S1 indicates sensor 1
 *          - 002121000 current measurement expressed in mA
 *    - package must have a fixed length for all readings
 *    
 *    
 * - please reach out for any and all questions - 
*/

#include <Wire.h>

#define SLAVE_ADDRESS 0x11
#define RX_BUFFER_SIZE 5
#define TX_BUFFER_SIZE 25
#define CURRENT_REFERENCE 2110
#define ARDUINO_REFERENCE 4.98
#define ANALOG_RESOLUTION 1.024

char data_rx[RX_BUFFER_SIZE];
char data_tx[TX_BUFFER_SIZE];
int tx_index = 0;

char letter = '!';

const int analogInPin1 = A0;
const int analogInPin2 = A1;
const int analogInPin3 = A2;
const int analogInPin4 = A3;
const int analogInPin5 = A4;
const int avgSamples = 10;

int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue3 = 0;
int sensorValue4 = 0;
//int sensorValue5 = 0;

float sensitivity = 0.4;
int current_reference = 2500;
float arduino_reference = 4.98;
float analog_resolution = 1.024;

//Payload 1 is A, Payload 2 is B, OBC is C, Comms is D
String data_tx_str = "<A.AAA B.BBB C.CCC D.DDD>";



void setup() {
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
  for (int i = 0; i < TX_BUFFER_SIZE; i++){ 
  data_tx[i] = data_tx_str[i];
  }

}

void loop() {
  for (int i = 0; i < avgSamples; i++)
  {
    sensorValue1 += analogRead(analogInPin1)*arduino_reference/analog_resolution;
    sensorValue2 += analogRead(analogInPin2)*arduino_reference/analog_resolution;
    sensorValue3 += analogRead(analogInPin3)*arduino_reference/analog_resolution;
    sensorValue4 += analogRead(analogInPin4)*arduino_reference/analog_resolution;
    //sensorValue5 += analogRead(analogInPin5);

    // wait 10 milliseconds before the next loop
    // for the analog-to-digital converter to settle
    // after the last reading:
    delay(10);

  }
 
  sensorValue1 = sensorValue1 / avgSamples; //2161
  sensorValue2 = sensorValue2 / avgSamples; //2201
  sensorValue3 = sensorValue3 / avgSamples;
  sensorValue4 = sensorValue4 / avgSamples;
  //sensorValue5 = sensorValue5 / avgSamples;


  // The current sensors have a current offset of approximately +2.11 Volts. Subtracting it by the current sensor reference current gives us a value in A
  // The current is in millivolts
  float current1 = (sensorValue1-current_reference)/sensitivity/1000;
  if (current1 < 0) {
        current1 = 0;
  }
  float current2 = (sensorValue2-current_reference)/sensitivity/1000;
  if (current2 < 0) {
        current2 = 0;
  }
  float current3 = (sensorValue3-current_reference)/sensitivity/1000;
  if (current3 < 0) {
        current3 = 0;
  }
  float current4 = (sensorValue4-current_reference)/sensitivity/1000;
  if (current4 < 0) {
        current4 = 0;
  }


  //float current5 = (current5 - Vref5) * sensitivity;

  String current1_str = String(current1, 3);
  String current2_str = String(current2, 3);
  String current3_str = String(current3, 3);
  String current4_str = String(current4, 3);
  //String current5_str = String(current5, 3);

//  Serial.print(current1);
//  Serial.print("mA");
//  Serial.print("\t");
//  Serial.print(current2);
//  Serial.print("mA");
//  Serial.print("\t");
//  Serial.print(current3);
//  Serial.print("mA");
//  Serial.print("\t");
//  Serial.print(current4);
//  Serial.print("mA");
//  Serial.print("\t");
//  Serial.print("\n");
//  Serial.print(current5);
  //Serial.print("mA");
 // Serial.print("\t");

//     <EPS P1: A.AAA P2: B.BBB O: C.CCC C: D.DDD>
//     0123456789012345678901234567890123456789012



  for (int i = 0; i <= 4; i++){
    data_tx[1 + i] = current1_str[i];
    data_tx[7 + i] = current2_str[i];
    data_tx[13 + i] = current3_str[i];
    data_tx[19 + i] = current4_str[i];
  }
  Serial.print(data_tx);
  // Reset the sensor value for the next reading
  sensorValue1 = 0;
  sensorValue2 = 0;
  sensorValue3 = 0;
  sensorValue4 = 0;
  //sensorValue5 = 0;
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
