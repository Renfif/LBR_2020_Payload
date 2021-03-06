<p>// Accelerometer/SD Datalogger<br>/* 
Gets raw g-force measurements from MPU6050 accelerometer in x/y/z axes and writes to an SD card </p><p>Credit to:                                         Source available at:
Jeff Rowberg for MPU6050_raw data example sketch   <a href="https://github.com/jrowberg/i2cdevlib"> www.HowToMechatronics.com
</a>
Dejan Nedelkovski for Arduino SD card tutorial     <a href="http://www.HowToMechatronics.com"> www.HowToMechatronics.com
</a>
*/</p><p>#include <sd.h>
#include <spi.h>
#include "I2Cdev.h"
#include "MPU6050.h"</spi.h></sd.h></p><p>#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif</p><p>File myFile;</p><p>// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;
//MPU6050 accelgyro(0x69); // <-- use for AD0 high</p><p>int pinCS = 10; //CS pin for SD card 
int scale = 16384; //divide values by MPU6050 sensitivity scale to get readings in g's (m/s^2 / 9.8)
                   //use scale = 16384 for the default I2Cdevlib sensitivity setting of +/-2</p><p>int16_t ax, ay, az;</p><p>#define LED_PIN 13
bool blinkState = false;</p><p>void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif</p><p>    // initialize serial communication
    // serial value can be up to you depending on project
    Serial.begin(9600);</p><p>    // initialize SD card
    if (SD.begin())
    {
        Serial.println("SD card is ready to use.");
    } else
    {
        Serial.println("SD card initialization failed");
        return;
    }</p><p>    // initialize accel/gyro
    Serial.println("Initializing accelerometer...");
    accelgyro.initialize();
    accelgyro.setSleepEnabled(false);</p><p>    // verify connection
    Serial.println("Testing accelerometer connection...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");</p><p>    // configure Arduino LED for
    pinMode(LED_PIN, OUTPUT);
}</p><p>void loop() {
  
    // read raw accelerometer measurements from device
    accelgyro.getAcceleration(&ax, &ay, &az);</p><p>    // display tab-separated accel x/y/z values in serial monitor
    Serial.print("acceleration:\t");
    Serial.print((float) ax / scale); Serial.print("\t");
    Serial.print((float) ay / scale); Serial.print("\t");
    Serial.println((float) az / scale); 
  
    // write the accelerometer values to SD card
    myFile = SD.open("test2.txt", FILE_WRITE);
    if (myFile) {
      myFile.print("acceleration:\t");
      myFile.print((float) ax / scale); myFile.print("\t");
      myFile.print((float) ay / scale); myFile.print("\t");
      myFile.println((float) az / scale); 
      myFile.close();
    }
    
    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
}</p>