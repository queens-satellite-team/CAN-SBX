/*
*   author: sean tedesco
*   email:  17sart@queensu.ca
*   date: July 16th, 2021
*
*   ARDUINO NANO I2C PINOUTS
*   PIN23 (PIN A4) -> SDA
*   PIN24 (PIN A5) -> SCL
*   PIN29 (Ground) -> GND
*
*   ARDUINO NANO SPI PINOUTS
*   PIN16 (PIN ~D13) -> SCK
*   PIN15 (PIN ~D12) -> MISO
*   PIN14 (PIN ~D11) -> MOSI
*   PIN13 (PIN ~D10) -> CSN
*   PIN11 (PIN ~D08) -> CE
*   
*   please feel free to reach out for any and all questions regarding this wee bit of code 
*/

/***********************************************************************************/
/********************************** INCLUDES ***************************************/
#include <SPI.h>
#include <RF24.h>
#include <Wire.h>

/***********************************************************************************/
/********************************** USER CONFIG ***********************************/

bool radioNumber = 1;           // payload = 0, ground station = 1, sets writing and reading pipe addresses
bool role = 0;                  // receive = 0, transmit = 1
bool debug = 0;                 // no print statements = 0, yes print statements = 1
uint8_t channel = 100;          // frequency channel
RF24 radio(8, 10);              // hardware connections: CE = 8, CSN = 10 

/***********************************************************************************/
/********************************** GLOBALS  ***************************************/

byte        addresses[][6] = {"1Node", "2Node"};
bool        new_data = false;
const int   num_chars = 256;
char        received_chars[num_chars];
char        transmitted_chars[num_chars];

/***********************************************************************************/
/*************************************** setup() ***********************************/
void setup() {

    /* setup debugging */
    Serial.begin(115200);
    while (!Serial){};
    Serial.flush();
    Serial.println(F("<success: arduino is ready>"));

    /* setup radio */
    if (!radio.begin()) {
        Serial.println(F("<error: radio hardware not responding>"));
        while (1) {}  // hold in infinite loop
    }
    radio.setPALevel(RF24_PA_HIGH);
    radio.setAutoAck(true);
    radio.setChannel(channel); //0-125
    radio.setDataRate(RF24_250KBPS);

    if (radioNumber) {
        radio.openWritingPipe(addresses[1]);
        radio.openReadingPipe(1, addresses[0]);
    } else {
        radio.openWritingPipe(addresses[0]);
        radio.openReadingPipe(1, addresses[1]);
    }

    if (role) { 
        radio.stopListening();
    } else { 
        radio.startListening();
    }
}
/***********************************************************************************/
/************************************* loop () *************************************/
void loop() {
    
  if ( role ) { 
    Serial.println("<success: switched to transmitting>"); 
    radio.stopListening();

    if (new_data)
    {
        if (!radio.write(&transmitted_chars, sizeof(transmitted_chars))) {
            if (debug){
                Serial.println(F("<error: could not send>"));
            }
        } else {
            if (debug) {
                Serial.println(F("<success: sent>"));
            }
            new_data = false;
        }
    }
    delay(10);

  } else {
    if (debug) { 
      Serial.println("<success: switched to receiving>");
    }
    radio.startListening();

    if( radio.available() ){                                             
      while ( radio.available() ) {                                   
        radio.read( &received_chars, sizeof(received_chars) );     
      }
        new_data = true; 
      }

    if(new_data == true){
      radio.stopListening();
      Serial.print(F("<response: "));
      Serial.print(received_chars);
      Serial.println(F(">"));
      new_data = false; 
    }
  }
}
