// This is the library for the TB6612 that contains the class Motor and all the
// functions
#include <SparkFun_TB6612.h>

// Pins for all inputs
#define AIN1 9
#define BIN1 11
#define AIN2 8
#define BIN2 12
#define PWMA 3
#define PWMB 5
#define STBY 10

// these constants are used to allow you to make your motor configuration 
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;
const int offsetB = 1;
char serialData;

// Initializing motors.
Motor motorA = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motorB = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

void setup()
{
    Serial.begin(9600);
}


void loop()
{
   //Use of the drive function which takes as arguements the speed
   //and optional duration.  A negative speed will cause it to go
   //backwards.  Speed can be from -255 to 255.  Also use of the 
   //brake function which takes no arguements.
   while (Serial.available()){
       serialData = Serial.read();
       if(serialData == 'd'){
            motorA.drive(255,1000);
            motorB.drive(255,1000);
            Serial.println("go forward");
            delay(1000);
       }
       else if(serialData == 's'){
           motorA.brake();
           motorB.brake();
           Serial.println("cut that shit out");
           delay(1000);
       }
       else if(serialData == 'a'){
           motorA.drive(-255,1000);
           motorB.drive(-255,1000);
           Serial.println("go backward");
           delay(1000);
       }
       else{
           motorA.brake();
           motorB.brake();
           delay(1000);
       }   
    }
//fns:
//    motor1.drive(-255,1000);
//    motor1.brake();
//    delay(1000);
//
//
//
}