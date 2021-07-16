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

bool radioNumber = 0;           // payload = 0, ground station = 1, sets writing and reading pipe addresses
bool role = 1;                  // receive = 0, transmit = 1
uint8_t channel = 100;          // frequency channel
uint8_t OBC_PIN = 2;            // led status pin for obc 
uint8_t slave_address = 0x04;   // must be the same on master side (obc rasperry pi)

RF24 radio(8, 10);              // hardware connections: CE = 8, CSN = 10 

bool debug = 1;                 // no print statements = 0, yes print statements = 1 

/***********************************************************************************/
/********************************** GLOBALS  ***************************************/

byte        addresses[][6] = {"1Node", "2Node"};
bool        new_data = false;
const int   num_chars = 256;
char        received_chars[num_chars];
char        transmitted_chars[num_chars];

/***********************************************************************************/
/*************************************** setup() ***********************************/
void setup()
{
    /* setup debugging */
    if (debug){
        Serial.begin(115200);
        while (!Serial){};
        Serial.flush();
    }

    /* setup led indicator */
    pinMode(OBC_PIN, OUTPUT);     
    digitalWrite(OBC_PIN, HIGH); // start in a good place

    /* setup comms to obc connection */
    Wire.begin(slave_address);
    Wire.onReceive(recv_from_obc);
    Wire.onRequest(send_to_obc);

    /* setup radio */
    if (!radio.begin()) {
        if (debug) {
            Serial.println(F("<error: radio hardware not responding>"));
        }
        digitalWrite(OBC_PIN, LOW); // end in a bad place
        while (1) {}                // hold in infinite loop
    }
    radio.setPALevel(RF24_PA_HIGH);
    radio.setAutoAck(true);
    radio.setChannel(channel);
    radio.setDataRate(RF24_250KBPS); // RF24_1MBPS or RF24_250KBPS

    if (radioNumber) {
        radio.openWritingPipe(addresses[1]);
        radio.openReadingPipe(1, addresses[0]);
    } else {
        radio.openWritingPipe(addresses[0]);
        radio.openReadingPipe(1, addresses[1]);
    }

    radio.stopListening();

    if (debug) {
        Serial.println(F("<success: arduino is ready>"));
    }  
}
/***********************************************************************************/
/************************************* loop () *************************************/
void loop()
{
    if (new_data)
    {
        if (!radio.write(&received_chars, sizeof(received_chars))) {
            if (debug){
                Serial.println(F("<failed>"));
            }
        } else {
            if (debug) {
                Serial.println(F("<success>"));
            }
            new_data = false;
        }
    }
    delay(10);
}

/***********************************************************************************/
/*********************************** recv_from_obc() *******************************/
void recv_from_obc()
{
    static boolean recv_in_progress = false;
    static byte ndx = 0;
    char start_marker = '<';
    char end_marker = '>';
    char rc;

    while (Wire.available() > 0 && new_data == false)
    {
        rc = Wire.read();

    if (recv_in_progress == true)
    {
      if (rc != end_marker)
      {
        received_chars[ndx] = rc;
        ndx++;
        if (ndx >= num_chars)
        {
          ndx = num_chars- 1;
        }
      }
      else
      {
        received_chars[ndx] = '\0'; // terminate the string
        recv_in_progress = false;
        ndx = 0;
        new_data = true;
      }
    }
    else if (rc == start_marker)
    {
      recv_in_progress = true;
      received_chars[ndx] = rc;
    }
  }
}
/***********************************************************************************/
/*********************************** send_to_obc() *********************************/
void send_to_obc()
{
    static uint8_t tx_index = 0; 

    if (Wire.write(transmitted_chars[tx_index])) {
        tx_index++;
        if (tx_index >= num_chars) {
            tx_index = 0; 
        }
    }
}
