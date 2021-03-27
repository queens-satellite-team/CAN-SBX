/* This file will contains all the code Reading the raw NMEA sentences from the Qwiic GPS module over I2C
 This code will eventually be run on the ADCS Arduino
 DataSheet for GPS https://cdn.sparkfun.com/assets/parts/1/2/2/8/0/GlobalTop_Titan_X1_Datasheet.pdf

Hardware Connections:
  Plug the Qwiic sensor into an Arduino using the SCL and SDA
  PORT.print it out at 115200 baud to serial monitor.
*/

#include "SparkFun_I2C_GPS_Arduino_Library.h" //Use Library Manager or download here: https://github.com/sparkfun/SparkFun_I2C_GPS_Arduino_Library
I2CGPS myI2CGPS; //Hook object to the library

#define PORT Serial


void setup()
{
  PORT.begin(115200);
  PORT.println("GTOP Read Example");

  while (myI2CGPS.begin() == false)
  {
    PORT.println("Module failed to respond. Please check wiring.");
    delay(500);
  }
  PORT.println("GPS module found!");
}

void loop()
{
  while (myI2CGPS.available()) //available() returns the number of new bytes available from the GPS module
  {
    byte incoming = myI2CGPS.read(); //Read the latest byte from Qwiic GPS

    if(incoming == '$') PORT.println(); //Break the sentences onto new lines
    PORT.write(incoming); //Print this character
  }
}
