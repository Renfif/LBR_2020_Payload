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
//    mpu6050.calcGyroOffsets(true);
    mpu6050.setGyroOffsets(-1.33,-1.98,-1.87);
    //offsets:
//  X : -1.33
//  Y : -1.98
//  Z : -1.87


}

void loop() {
    //mpu data retrieval
    mpu6050.update();
    Serial.println(mpu6050.getAngleY());
    //rotating using that value
    //error = 0 - currentPos ; <-- error = negative current pos, so while the motor should run in the desired direction whenever its not equal to zero or in the meantime on the test jig should rotate clockwise if the value is positive & counterclockwise if negative until its zero again.
    //float roll=atan2(mpu6050.getAccX(),mpu6050.getAccZ())*180/3.141592654;
    float roll = mpu6050.getAngleY();
    float error = 0 - roll;

      if(int(error)< 0){
          orientationMotor.Enable();
          orientationMotor.TurnLeft(7);
        }
      if(int(error) > 0){
          orientationMotor.Enable();
          orientationMotor.TurnRight(7);
        }
      else{
        orientationMotor.Stop();
        }
    
}
