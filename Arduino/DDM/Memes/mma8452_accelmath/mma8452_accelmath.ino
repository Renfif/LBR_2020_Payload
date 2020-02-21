/*
  Library for the MMA8452Q
  By: Jim Lindblom and Andrea DeVore
  SparkFun Electronics

  Do you like this library? Help support SparkFun. Buy a board!
  https://www.sparkfun.com/products/14587

  This sketch uses the SparkFun_MMA8452Q library to initialize
  the accelerometer and stream raw x, y, z, acceleration
  values from it.

  Hardware hookup:
  Arduino --------------- MMA8452Q Breakout
    3.3V  ---------------     3.3V
    GND   ---------------     GND
  SDA (A4) --\/330 Ohm\/--    SDA
  SCL (A5) --\/330 Ohm\/--    SCL

  The MMA8452Q is a 3.3V max sensor, so you'll need to do some
  level-shifting between the Arduino and the breakout. Series
  resistors on the SDA and SCL lines should do the trick.

  License: This code is public domain, but if you see me
  (or any other SparkFun employee) at the local, and you've
  found our code helpful, please buy us a round (Beerware
  license).

  Distributed as is; no warrenty given.
*/

#include <Wire.h>                 // Must include Wire library for I2C
#include "SparkFun_MMA8452Q.h"    // Click here to get the library: http://librarymanager/All#SparkFun_MMA8452Q
# include <math.h>

/////////////ACCELEROMETER/////////////////////////
float roll=0;
float pitch=0;

////////////FIXING MOTOR TWITCHING////////////////
float oldRoll=0; //global variable that will be used to store old roll values for comparison
int spike=50;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 100;    // the debounce time; increase if the output flickers

///////////H-BRIDGE PINS////////////////////////
int R_en=7; 
int L_en=8;
int RPWM=5;
int LPWM=6;

MMA8452Q accel;                   // create instance of the MMA8452 class

void setup() {
  Serial.begin(9600);
  Serial.println("MMA8452Q Raw Data Reading Code!");
  Wire.begin();

  pinMode(R_en, OUTPUT);
  pinMode(L_en, OUTPUT);
  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);

  digitalWrite(R_en, HIGH);
  digitalWrite(L_en, HIGH);


  if (accel.begin() == false) {
    Serial.println("Not Connected. Please check connections and read the hookup guide.");
    while (1);
  }
}

void loop() {
  if (accel.available()) {      // Wait for new data from accelerometer
    // Raw of acceleration of x, y, and z directions

   /* xacc=accel.getX()*1000/256;    
    yacc=accel.getY()*1000/256;  
    zacc=accel.getZ()*1000/256;  */
    
    oldRoll=roll; //store the previous roll value
    delay(300);
    roll=atan2(accel.getX(),accel.getZ())*180/3.141592654;
       
    //pitch=atan2(accel.getY(),accel.getZ())*180/3.141592654;

    ////////////FILTER////////////////////////////////////////
    float difference=abs(oldRoll-roll);
    
    if(difference>spike) //check the difference
    {
    lastDebounceTime=millis();
    }

    if ((millis() - lastDebounceTime) < debounceDelay) {
    Serial.println("Hallas");
    delay(50);
    }

    ///////////////////////////////////////////////////////////    
    Serial.println(roll);
    //Serial.print("\t");
    //Serial.println(pitch);

    if (roll >= -10 || roll<=10 )
    {
      digitalWrite(RPWM, LOW);
      digitalWrite(LPWM, LOW);
     // Serial.println("stop");
    }
    if (roll<-10)
    {
      digitalWrite(RPWM, HIGH);
      digitalWrite(LPWM, LOW);
      //Serial.println("left");
    }

    if (roll>10)
    {
      digitalWrite(RPWM, LOW);
      digitalWrite(LPWM, HIGH);
      //Serial.println("right");
    }
  ////////////////////////////////////////////////////////////////////////
/*
    Serial.print(xacc);
    Serial.print("\t");
    Serial.print(yacc);
    Serial.print("\t");
    Serial.print(zacc);
    Serial.println(); */
    
    /*
    Serial.print(accel.getX());
    Serial.print("\t");
    Serial.print(accel.getY());
    Serial.print("\t");
    Serial.print(accel.getZ());
    Serial.println();*/
  }
}
