/*////////////////ACCELEROMETER/////////////////////////////////////////////////////////////////////////////
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
*///////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////SD CARD//////////////////////////////////////////////////////////////////////////////////
// 5V power
// MISO - 12
// MOSI - 11
// SCK - 13
// CS- 10

///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Wire.h>                 // Must include Wire library for I2C for accelerometer
#include "SparkFun_MMA8452Q.h"    // Click here to get the library: http://librarymanager/All#SparkFun_MMA8452Q
# include <math.h>

#include <SPI.h>                  // for SD card reader
#include <SD.h>

float roll=0; //global variable that stores the value of roll

MMA8452Q accel;                   // create instance of the MMA8452 class for accelerometer
File myFile;                      // for SD card reader

////////////SETUP////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  Serial.println("MMA8452Q Raw Data Reading Code!");
  Wire.begin();

  if (accel.begin() == false) {
    Serial.println("Not Connected. Please check connections and read the hookup guide.");
    while (1);
  }

  while (!Serial) { ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");
       if (!SD.begin(10)) {
       Serial.println("initialization failed!");
       while (1);
       }
  Serial.println("initialization done.");

  myFile = SD.open("test.txt", FILE_WRITE);                     // open the file. note that only one file can be open at a time, so you have to close this one before opening another.
  // if the file opened okay, write to it:
        if (myFile) {
        Serial.print("Writing to test.txt...");
        myFile.println("New section");
        myFile.println("The SD reader has been turned on");
        myFile.println("testing 1, 2, 3.");
        myFile.close();                                        // close the file:
        Serial.println("done.");
        } 
        else {                                                // if the file didn't open, print an error
        Serial.println("error opening test.txt");
        }
}

///////////////MAIN LOOP//////////////////////////////////////////////////////////////////////////
void loop() {
  if (accel.available()) {      // Wait for new data from accelerometer
    // Raw of acceleration of x, y, and z directions
   /* xacc=accel.getX()*1000/256;    
    yacc=accel.getY()*1000/256;  
    zacc=accel.getZ()*1000/256;  */
    roll=atan2(accel.getX(),accel.getZ())*180/3.141592654;
    //Serial.println(roll);

    myFile = SD.open("test.txt", FILE_WRITE);
        if (myFile) {
          myFile.print("roll");
          myFile.print("\t");      
          myFile.println(roll);
          myFile.close();                                        // close the file

          Serial.print("roll");
          Serial.print("\t");
          Serial.println(roll);
          }
    
  }
}
