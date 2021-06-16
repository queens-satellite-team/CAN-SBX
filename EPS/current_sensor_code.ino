/*  SparkFun ACS712 and ACS723 Demo
    Created by George Beckstein for SparkFun
    4/30/2017
    Updated by SFE
    6/14/2018

    Uses an Arduino to set up the ACS712 and ACS723 Current Sensors
    See the tutorial at: https://learn.sparkfun.com/tutorials/current-sensor-breakout-acs723-hookup-guide
*/
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
int sensorValue5 = 0;

float sensitivity = 0.1;
float Vref1 = 2508;
float Vref2 = 2528;
float Vref3 = 2518;
float Vref4 = 2513;
float Vref5 = 2523;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  for (int i = 0; i < avgSamples; i++)
  {
    sensorValue1 += analogRead(analogInPin1);
    sensorValue2 += analogRead(analogInPin2);
    sensorValue3 += analogRead(analogInPin3);
    sensorValue4 += analogRead(analogInPin4);
    sensorValue5 += analogRead(analogInPin5);

    // wait 2 milliseconds before the next loop
    // for the analog-to-digital converter to settle
    // after the last reading:
    delay(100);

  }

  sensorValue1 = sensorValue1 / avgSamples;
  sensorValue2 = sensorValue2 / avgSamples;
  sensorValue3 = sensorValue3 / avgSamples;
  sensorValue4 = sensorValue4 / avgSamples;
  sensorValue5 = sensorValue5 / avgSamples;

  // The on-board ADC is 10-bits -> 2^10 = 1024 -> 5V / 1024 ~= 4.88mV
  // The voltage is in millivolts
  float voltage1 = 4.88 * sensorValue1;
  float voltage2 = 4.88 * sensorValue2;
  float voltage3 = 4.88 * sensorValue3;
  float voltage4 = 4.88 * sensorValue4;
  float voltage5 = 4.88 * sensorValue5;

  // This will calculate the actual current (in mA)
  // Using the Vref and sensitivity settings you configure
  float current1 = (voltage1 - Vref1) * sensitivity;
  float current2 = (voltage2 - Vref2) * sensitivity;
  float current3 = (voltage3 - Vref3) * sensitivity;
  float current4 = (voltage4 - Vref4) * sensitivity;
  float current5 = (voltage5 - Vref5) * sensitivity;

  // This is the raw sensor value, not very useful without some calculations
  //Serial.print(sensorValue);

  /*************************************************************************************
   * Step 1.)
   * Uncomment and run the following code to set up the baseline voltage 
   * (the voltage with 0 current flowing through the device).
   * Make sure no current is flowing through the IP+ and IP- terminals during this part!
   * 
   * The output units are in millivolts. Use the Arduino IDE's Tools->Serial Plotter
   * To see a plot of the output. Adjust the Vref potentiometer to set the reference
   * voltage. This allows the sensor to output positive and negative currents!
   *************************************************************************************/

  //Serial.print(voltage);
  //Serial.print("mV");

  /*************************************************************************************
   * Step 2.)
   * Keep running the same code as above to set up the sensitivity
   * (how many millivolts are output per Amp of current.
   * 
   * This time, use a known load current (measure this with a multimeter)
   * to give a constant output voltage. Adjust the sensitivity by turning the
   * gain potentiometer.
   * 
   * The sensitivity will be (known current)/(Vreading - Vref).
   *************************************************************************************/

    /*************************************************************************************
   * Step 3.)
   * Comment out the code used for the last two parts and uncomment the following code.
   * When you have performed the calibration steps above, make sure to change the 
   * global variables "sensitivity" and "Vref" to what you have set up.
   * 
   * This next line of code will print out the calculated current from these parameters.
   * The output is in mA
   *************************************************************************************/

  Serial.print(current1);
  Serial.print("mA");
  Serial.print("\t");
  Serial.print(current2);
  Serial.print("mA");
  Serial.print("\t");
  Serial.print(current3);
  Serial.print("mA");
  Serial.print("\t");
  Serial.print(current4);
  Serial.print("mA");
  Serial.print("\t");
  Serial.print(current5);
  Serial.print("mA");
  Serial.print("\t");


  // -- DO NOT UNCOMMENT BELOW THIS LINE --
  Serial.print("\n");

  // Reset the sensor value for the next reading
  sensorValue1 = 0;
  sensorValue2 = 0;
  sensorValue3 = 0;
  sensorValue4 = 0;
  sensorValue5 = 0;
}
