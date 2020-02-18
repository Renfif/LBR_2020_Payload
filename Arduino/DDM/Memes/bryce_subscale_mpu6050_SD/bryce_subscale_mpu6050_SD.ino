  
#include <SPI.h>
#include <SD.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);
const int chipSelect = 4;

/*
 * 6055 pins:
 * VCC & GND to arduino 5V and GND rail
 * SCL to A5, SDA to A4
 * INT to digital 2
 * SD-Card breakout pins:
 * VCC & GND to arduino 5V and GND rail
 * MISO to digital 12, MOSI to digital 11 
 * SCK to digital 13
 * CS(chip select) to digital 4
 */

void setup() {
    // Open serial communications
    Serial.begin(9600);
    Wire.begin();
    mpu6050.begin();
    mpu6050.calcGyroOffsets(true);

//    //FOR TESTING PURPOSES ONLY
//    while (!Serial) {
//        ; // wait for serial port to connect
//    }

    Serial.print("Initializing SD card...");

    // see if the card is present and can be initialized
    if (!SD.begin(chipSelect)) {
        Serial.println("Card failed, or not present");
        while (1);
    }
    Serial.println("card initialized.");
    //---------------------------
    //start of file print
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
    if (dataFile) {
        dataFile.println("Data Log Start");
        dataFile.close();
    }
}

void loop() {
    //string for data we are logging
    String dataString = "";

    //mpu data retrieval
    mpu6050.update();
//    Serial.print(mpu6050.getAngleX());
//    Serial.print(mpu6050.getAngleY());
//    Serial.println(mpu6050.getAngleZ());
    dataString += String (mpu6050.getAngleX());
    //------

    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
    
    // if the file is available, write to it:
    if (dataFile) {
        dataFile.println(dataString);
        dataFile.close();
        // print to the serial port too:
        Serial.println(dataString);
    }
    // if the file isn't open, pop up an error:
    else {
        Serial.println("error opening datalog.txt");
    }

}
