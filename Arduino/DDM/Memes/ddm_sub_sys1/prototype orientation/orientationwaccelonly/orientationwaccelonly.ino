#include <SparkFun_MMA8452Q.h>
#include <BTS7960.h>
#include <Wire.h>

// Wire/i2c pins on arduino nano are A4 & A5

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
    //error = setpoint - current posiiton, so the motor should rotate clockwise if the value is positive & counterclockwise if negative until its at the setpoint again.
      int speed = 7;
    //7 is the speed used for the test motor, acutal motor should be at ~100%(255)
      float setpoint = 0;
      float roll=atan2(accel.getX(),accel.getZ())*180/3.141592654;
      float error = setpoint - roll; //error value determined by desired setpoint(in this case its zero) and current measured position
      Serial.println(roll);
        if(error != 0){
        //this f statement decide what range of values are acceptable for error to be zero, 0 meaning it must be exactly the setpoint
        if(int(error < 0)){
            orientationMotor.Enable();
            orientationMotor.TurnLeft(speed);
          }
        if(int(error > 0)){
            orientationMotor.Enable();
            orientationMotor.TurnRight(speed);
          }
      }
      else{
        orientationMotor.Stop();
//        orientationMotor.Disable();
      }
    }
    
}
