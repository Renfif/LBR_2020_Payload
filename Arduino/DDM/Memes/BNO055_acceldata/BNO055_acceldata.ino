/////////////FOR WIRING///////////////////////
// only wiring 5v and GND
// SDA  arduino A04
// SCL arduino A05
// need to calibrate imu with each use by waving it around yeeehaww

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <math.h>
 
#define BNO055_SAMPLERATE_DELAY_MS (100)
 
Adafruit_BNO055 myIMU = Adafruit_BNO055();

float rolltilt;
float pitchtilt;

 
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
myIMU.begin();
delay(1000);
int8_t temp=myIMU.getTemp();
myIMU.setExtCrystalUse(true);
}
 
void loop() {
  // put your main code here, to run repeatedly:
uint8_t system, gyro, accel, mg=0;
myIMU.getCalibration(&system, &gyro, &accel, &mg);

imu::Vector<3> acc =myIMU.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
 
rolltilt=atan2(acc.y(),acc.z())*180/3.141592654;  //Trig bitchezz gives deg
pitchtilt=atan2(acc.x(),acc.z())*180/3.141592654;

Serial.print(acc.x());
Serial.print(",");
Serial.print(acc.y());
Serial.print(",");
Serial.print(acc.z());
Serial.print(",");
//Serial.print("Calibration:");
Serial.print(accel);
Serial.print(",");
Serial.print(gyro);
Serial.print(",");
Serial.print(mg);
Serial.print(",");
Serial.print(system);
Serial.print(",");
Serial.print("Roll Angle");
Serial.print(rolltilt);
Serial.print(",");
Serial.print("Pitch Angle");
Serial.println(pitchtilt);
  
delay(BNO055_SAMPLERATE_DELAY_MS);
}
