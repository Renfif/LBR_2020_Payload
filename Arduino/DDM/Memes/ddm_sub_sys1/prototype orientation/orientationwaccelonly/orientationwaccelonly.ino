#include <SparkFun_MMA8452Q.h>
#include <BTS7960.h>
#include <Wire.h>
#include <AutoPID.h>

MMA8452Q accel;

const uint8_t EN = 8;
const uint8_t L_PWM = 9;
const uint8_t R_PWM = 10;

BTS7960 orientationMotor(EN, L_PWM, R_PWM); 

void setup() {
    // Open serial communications
    Serial.begin(9600);
    Wire.begin();
    if(accel.begin() == false){
      Serial.println("Device not connected, startup failed.");
    }
//    orientationMotor.Disable();
}

void loop() {
    //accelerometer data retrieval
    if(accel.available()){
//      Serial.println(accel.getCalculatedX(), 3);
    
    //rotating using that value
    //error = negative current pos, so while the motor should run in the desired direction whenever its not equal to zero or in the meantime on the test jig should rotate clockwise if the value is positive & counterclockwise if negative until its zero again.
      float roll=atan2(accel.getX(),accel.getZ())*180/3.141592654;
      float error = 0 - roll;
      Serial.println(roll);
//      if(error != 0){
        if (-5<error<5){
        if(int(error < 0)){
            orientationMotor.Enable();
            orientationMotor.TurnLeft(7);
          }
        if(int(error > 0)){
            orientationMotor.Enable();
            orientationMotor.TurnRight(7);
          }
      }
      else{
        orientationMotor.Stop();
//        orientationMotor.Disable();
      }
    }
    
}
