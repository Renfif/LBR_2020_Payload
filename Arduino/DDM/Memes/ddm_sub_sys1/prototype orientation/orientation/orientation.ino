#include <MPU6050_tockn.h>
#include <BTS7960.h>
#include <Wire.h>

#include <AutoPID.h>

MPU6050 mpu6050(Wire);

const uint8_t EN = 8;
const uint8_t L_PWM = 9;
const uint8_t R_PWM = 10;

BTS7960 orientationMotor(EN, L_PWM, R_PWM);

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
    mpu6050.calcGyroOffsets(true);

}

void loop() {
    //mpu data retrieval
    mpu6050.update();
    Serial.println(mpu6050.getAngleY());
    //rotating using that value
    //error = 0 - currentPos ; <-- error = negative current pos, so while the motor should run in the desired direction whenever its not equal to zero or in the meantime on the test jig should rotate clockwise if the value is positive & counterclockwise if negative until its zero again.
//    if(){
//      orientationMotor.Enable();
//      
//      while (0-(mpu6050.getAngleY()) > 0){
//          orientationMotor.TurnLeft();
//        }
//      while (0-(mpu6050.getAngleY()) < 0){
//          orientationMotor.TurnRight();
//        }
//    }
//    else{
//      orientationMotor.Stop();
//      }
    
}
