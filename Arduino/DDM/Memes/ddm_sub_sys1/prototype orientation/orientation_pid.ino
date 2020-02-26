#include <MPU6050_tockn.h>
#include <Wire.h>
#include <L298N.h>
#include <AutoPID.h>

#define ENA 9
#define IN1 10
#define IN2 11
#define enableButton 5

int buttonState = 0;

MPU6050 mpu6050(Wire);
L298N orientationMotor(ENA, IN1, IN2);

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
    pinMode(enableButton,INPUT);
    Wire.begin();
    mpu6050.begin();
    mpu6050.calcGyroOffsets(true);
    orientationMotor.setSpeed(50);

}

void loop() {
    //mpu data retrieval
    mpu6050.update();
    Serial.println(mpu6050.getAngleY());
//     Serial.print(mpu6050.getAngleX());
//     Serial.println(mpu6050.getAngleZ());

    buttonState = digitalRead(enableButton);
    while(buttonState == HIGH){
        orientationMotor.forward();
    }
    
}