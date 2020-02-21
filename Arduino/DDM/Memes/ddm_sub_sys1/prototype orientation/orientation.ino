#include <MPU6050_tockn.h>
#include <Wire.h>
#include <Drive>
#include <AutoPID>

#define EnA 9
#define In1 6
#define In2 7

MPU6050 mpu6050(Wire);
Drive drive(In1,In2)

/*
 * 6055 pins:
 * VCC & GND to arduino 5V and GND rail
 * SCL to A5, SDA to A4
 * INT to digital 2
 * 
*/

void setup() {
    // Open serial communications
    Serial.begin(9600);
    pinMode(enA, OUTPUT);
    Wire.begin();
    mpu6050.begin();
    mpu6050.calcGyroOffsets(true);
    

}

void loop() {
    //mpu data retrieval
    mpu6050.update();
   Serial.print(mpu6050.getAngleX());
//    Serial.print(mpu6050.getAngleY());
//    Serial.println(mpu6050.getAngleZ());
}