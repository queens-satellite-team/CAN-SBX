/* Please Note:
Date and time are in UTC
Altitude appeared to have a small error (<30m) when <14 sattelites were in view
-Tobias Chong
(2021-04-05)
*/
#include <SparkFun_I2C_GPS_Arduino_Library.h> //Use Library Manager or download here: https://github.com/sparkfun/SparkFun_I2C_GPS_Arduino_Library
I2CGPS myI2CGPS;

#include <TinyGPS++.h> //From: https://github.com/mikalhart/TinyGPSPlus
TinyGPSPlus gps;

void setup() {

  Serial.begin(115200);
  Serial.println("GPS Read Example");

  if (myI2CGPS.begin() == false)
  {
    Serial.println("Module failed to respond. Please check wiring.");
    while (1);
  }
  Serial.println("GPS module found!");
}

void loop() {

  while (myI2CGPS.available())
  {
    gps.encode(myI2CGPS.read());
  }

  if (gps.time.isUpdated())
  {
    displayInfo();
  }
}

void displayInfo()
{

  Serial.println();

  if (gps.time.isValid())
  {
    Serial.print(F("Date: "));
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());

    Serial.print((" Time: "));
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());

    Serial.println();
  }
  else
  {
    Serial.println(F("Time not yet valid"));
  }

  if (gps.location.isValid())
  {
    Serial.print("Location: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(", "));
    Serial.print(gps.location.lng(), 6);
    Serial.println();
  }
  else
  {
    Serial.println(F("Location not yet valid"));
  }

  if (gps.altitude.isValid())
  {
    Serial.print(F("Altitude Meters:"));
    Serial.print(gps.altitude.meters());
    Serial.print(F(" Feet:"));
    Serial.print(gps.altitude.feet());
  }

  if (gps.satellites.isValid())
  {
    Serial.print(F(" Satellites in View:"));
    Serial.print(gps.satellites.value());
  }

  if (gps.hdop.isValid())
  {
    Serial.print(F(" HDOP:"));
    Serial.print(gps.hdop.value()/100.0, 2);
  }

  Serial.println();
}
