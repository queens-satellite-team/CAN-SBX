#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_MPU6050.h>
#include <SparkFun_I2C_GPS_Arduino_Library.h>
#include <TinyGPS++.h>
#include <Chrono.h>

#include "ADCS_DEFINITIONS.h"

//setup GPS,BNO055,MPU6050
TinyGPSPlus gps;
I2CGPS myI2CGPS;
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);
Adafruit_MPU6050 mpu;
Adafruit_Sensor *mpu_temp, *mpu_accel, *mpu_gyro;

//setup SD writing
const int chipSelect = 53;
File sensorData;
String buffer;
unsigned long lastMillis = 0;

// Define clocks
Chrono gps_clock;
Chrono bno_clock;
Chrono mpu_clock;
Chrono snc_clock; // this clock syncronizes readings

//write buffer to SD
void writeData() {
  //write any available data to SD
  unsigned int chunkSize = sensorData.availableForWrite();

  Serial.print(chunkSize);
  Serial.print("\t");
  Serial.print(buffer.length());
  Serial.print("\n");
  //  Serial.print(buffer.c_str());
  //  Serial.print("\n");

  if (chunkSize && buffer.length() >= chunkSize) {
    //write to file and blink LED
    digitalWrite(LED_BUILTIN, HIGH);

    Serial.print(buffer.c_str());
    Serial.print("\n");

    sensorData.write(buffer.c_str(), chunkSize);
    digitalWrite(LED_BUILTIN, LOW);
    //remove written data from buffer
    buffer.remove(0, chunkSize);
    sensorData.close();
    sensorData = SD.open("data.csv", FILE_WRITE);
  }
}

//Serial communication to OBC
int relayData(String data) {
  Serial1.write(data.c_str());
  Serial.write(data.c_str());
}

//GPS data read and bundling
String readGPS() {
  String data = "";
  String time_data = ",,";
  String coords_data = ",";
  String alt_data = "";
  //read gps
  while (myI2CGPS.available()) {
    gps.encode(myI2CGPS.read());
  }
#ifdef GPS_get_time
  time_data = String(gps.time.hour()) + "," + String(gps.time.minute()) + "," + String(gps.time.second());
#endif
#ifdef GPS_get_coords
  coords_data = String(gps.location.lat(), 6) + "," + String(gps.location.lng(), 6);
#endif
#ifdef GPS_get_alt
  alt_data = String(gps.altitude.meters());
#endif
  //return bundled data
  data = time_data + "," + coords_data + "," + alt_data;

  //  Serial.print(data);
  //  Serial.print("\n");

  return data;
}

//MPU6050 data read and bundling
String readMPU() {
  String data = "";
  String gyro_data = ",,";
  String acc_data = ",,";
  String temp_data = "";
  //read mpu6050
#ifdef MPU_get_gyro
  sensors_event_t gyro;
  mpu_gyro->getEvent(&gyro);
  gyro_data = String(gyro.gyro.x) + "," + String(gyro.gyro.y) + "," + String(gyro.gyro.x);
#endif
#ifdef MPU_get_acc
  sensors_event_t accel;
  mpu_accel->getEvent(&accel);
  acc_data = String(accel.acceleration.x) + "," + String(accel.acceleration.y) + "," + String(accel.acceleration.z);
#endif
#if defMPU_get_temp
  sensors_event_t temp;
  mpu_temp->getEvent(&temp);
  temp_data = String(temp.temperature);
#endif
  //return bundled data
  data = gyro_data + "," + acc_data + "," + temp_data;

  //  Serial.print(data);
  //  Serial.print("\n");

  return data;
}

//BNO055 data read and bundling
String readBNO() {

  //  Serial.print("reading BNO");
  //  Serial.print("\n");

  String data = "";
  String orient_data = ",,";
  String gyro_data = ",,";
  String acc_data = ",,";
  String mag_data = ",,";
  String temp_data = "";
  //read bno055
  sensors_event_t event;
  bno.getEvent(&event);
#ifdef BNO_get_orient
  orient_data = String(event.orientation.x) + "," + String(event.orientation.y) + "," + String(event.orientation.x);

  //    Serial.print("BNO Orient: \t");
  //    Serial.print(event.orientation.x);
  //    Serial.print("\n");
  //    Serial.print(orient_data);
  //    Serial.print("\n");
#endif

#ifdef BNO_get_gyro
  gyro_data = String(event.gyro.x) + "," + String(event.gyro.y) + "," + String(event.gyro.x);
#endif
#ifdef BNO_get_acc
  acc_data = String(event.acceleration.x) + "," + String(event.acceleration.y) + "," + String(event.acceleration.z);
#endif
#ifdef BNO_get_mag
  mag_data = String(event.magnetic.x) + "," + String(event.magnetic.y) + "," + String(event.magnetic.z);
#endif
#ifdef BNO_get_temp
  temp_data = String(bno.getTemp());
#endif

  //  Serial.print(orient_data);
  //  Serial.print("\n");

  data = orient_data + "," + gyro_data + "," + acc_data + "," + mag_data + "," + temp_data;

  //  Serial.print(data);
  //  Serial.print("\n");

  return data;
}

void setup() {

  Serial.begin(115200);
  //Serial1.begin(115200);
  Serial.print("Begin\n");


  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  //init SD file and headers
  String heading = String("MEGA_Time,GPS_Hour,GPS_Minute,GPS_Second,GPS_Lat,GPS_Long,GPS_Alt,") +
                   String("BNO_X,BNO_Y,BNO_Z,BNO_GYRO_X,BNO_GYRO_Y,BNO_GYRO_Z,") +
                   String("BNO_ACC_X,BNO_ACC_Y,BNO_ACC_Z,BNO_MAG_X,BNO_MAG_Y,BNO_MAG_Z,BNO_TEMP,") +
                   String("MPU_GYRO_X,MPU_GYRO_Y,MPU_GYRO_Z,MPU_ACC_X,MPU_ACC_Y,MPU_ACC_Z,MPU_TEMP") + "\r\n";
  SD.begin(chipSelect);
  if (!SD.exists("data.txt")) {
    sensorData = SD.open("data.csv", FILE_WRITE);
    sensorData.write(heading.c_str(), heading.length());

    Serial.print("File not found, initialized\n");

  } else {
    sensorData = SD.open("data.csv", FILE_WRITE);

    Serial.print("File found\n");

  }

  //Initialize GPS
  while (!myI2CGPS.begin()) {

    Serial.print("Waiting for GPS to initialize\n");

    delay(500);
  }

  Serial.print("GPS Initialized\n");

  //Initialize BNO055
  while (!bno.begin()) {

    Serial.print("Waiting for BNO to initialize\n");

    delay(500);
  }

  Serial.print("BNO Initialized\n");

  //Initialize MPU6050
  while (!mpu.begin()) {

    Serial.print("Waiting for MPU to initialize\n");

    delay(500);
  }
  mpu_temp = mpu.getTemperatureSensor();
  mpu_temp->printSensorDetails();
  mpu_accel = mpu.getAccelerometerSensor();
  mpu_accel->printSensorDetails();
  mpu_gyro = mpu.getGyroSensor();
  mpu_gyro->printSensorDetails();

  Serial.print("MPU Initialized\n");

  // Ensure first run gets a reading (This is kinda irrelevant,
  // but makes sure the first reading is syncronized
  gps_clock.restart();
  bno_clock.restart();
  mpu_clock.restart();
  snc_clock.restart();
  snc_clock.delay(max_time);
}

void loop() {
  String gps_data = "";
  String bno_data = "";
  String mpu_data = "";
  if (snc_clock.hasPassed(min_time)) {
    snc_clock.restart();
    // add a new line to the buffer
    buffer += String(millis()) + ",";
    if (gps_clock.hasPassed(gps_time)) {
      gps_clock.restart();
      gps_data = readGPS();
      buffer += gps_data + ",";
    }
    if (bno_clock.hasPassed(bno_time)) {
      bno_clock.restart();
      bno_data = readBNO();
      buffer += bno_data + ",";
    }
    if (mpu_clock.hasPassed(mpu_time)) {
      mpu_clock.restart();
      mpu_data = readMPU();
      buffer += mpu_data + ",";
    }
    buffer += "\r\n";
    if (Serial1.available()) {
      relayData(gps_data);
    }
  }
  writeData();
}
