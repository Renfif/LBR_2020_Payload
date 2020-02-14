#include <Drive>
#include <AutoPID>
#include <Wire.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensors.h>
#include <utility/imumaths.h>

#define enA 9
#define in1 6
#define in2 7

Drive drive(IN1,IN2)
//drive takes a value between 0 and 1024
Adafruit_BNO055 bno = Adafruit_BNO055(55);

void setup() {
  Serial.begin(9600);
//  pinMode(enA, OUTPUT);

  
}   

void loop() {
  drive.moveForward(500);
  
  
}
