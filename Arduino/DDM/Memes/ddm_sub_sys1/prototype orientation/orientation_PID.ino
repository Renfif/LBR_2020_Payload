#include <MPU6050.h>
#include <Wire.h>
#include <PID.h>

MPU6050 mpu6050(Wire, 0.05, .095);
PID Pcontrol(&Input,&Output,&Setpoint, Kp, Ki, Kd, DIRECT);
BTS7960 motorController(EN, L_PWM, R_PWM);

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
    Wire.begin();
    mpu6050.begin();
    mpu6050.calcGyroOffsets();
    // mpu6050.calcGyroOffsets(true); //this one waits for serial monitor to start

}

void loop() {
    int currentPos = 0;
    //mpu data retrieval
    mpu6050.update();
    Serial.println(mpu6050.getAngleY());
    currentPos = mpu6050.getAngleY();
    //--
    motorController.Enable();



}