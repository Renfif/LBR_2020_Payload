#include <MPU6050_tockn.h>
#include <Wire.h>
#include <Drive.h>
#include <AutoPID.h>

#define EnA 9
const int IN1 = 6;
const int IN2 = 7;
const int IN3;
const int IN4;
boolean toggle = false;

MPU6050 mpu6050(Wire);
Drive drive(IN1,IN2,IN3,IN4);

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
    pinMode(EnA, OUTPUT);
    pinMode(13,INPUT_PULLUP);
    Wire.begin();
    mpu6050.begin();
    mpu6050.calcGyroOffsets(true);
    

}

void loop() {
    //mpu data retrieval
    mpu6050.update();
    Serial.print(mpu6050.getAngleX());
//     Serial.print(mpu6050.getAngleY());
//     Serial.println(mpu6050.getAngleZ());

    int button = digitalRead(13);
    if(button == HIGH){
      toggle = !toggle;
    }
    while(toggle){
      digitalWrite(EnA,HIGH);
      drive.moveForward(500);
    }
    
}