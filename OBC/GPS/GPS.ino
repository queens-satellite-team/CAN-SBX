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

byte protocol_header[6];
int count;
byte GNGGA[6]={'$','G','N','G','G','A'};
void setup()
{
  PORT.begin(115200);
  PORT.println("GTOP Read Example");

  while (myI2CGPS.begin() == false)
  {
    PORT.println("Module failed to respond. Please check wiring.");
    delay(500);
  }
  PORT.println("GPS module found!");}

void loop()
{
  while (myI2CGPS.available()) //available() returns the number of new bytes available from the GPS module
  {
    byte incoming = myI2CGPS.read(); //Read the latest byte from Qwiic GPS
    
    if(incoming == '$'){
      count = 0;
      PORT.println(); //Break the sentences onto new lines
    }
    else{
      count ++;
    }
    if(count <= 5){
    protocol_header[count] = incoming;
    
    }
    if(count==5&&(compareArray(protocol_header,GNGGA,6))==0){
    PORT.println();
    PORT.write("match found");
    PORT.println();
    }
    PORT.write(incoming); //Print this character
  }
}
int compareArray(byte a[],byte b[],int size)  {
  int i;
  for(i=0;i<size;i++){
    if(a[i]!=b[i])
      return 1;
  }
  return 0;
}
