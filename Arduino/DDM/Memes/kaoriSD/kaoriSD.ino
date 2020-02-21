// MISO - 12
// MOSI - 11
// SCK - 13
// CS- 10

#include <SPI.h>
#include <SD.h>
File myFile;

void setup() {
// Open serial communications and wait for port to open:
String msg = "your're mom gay";

Serial.begin(9600);

while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}

Serial.print("Initializing SD card...");
if (!SD.begin(10)) {
Serial.println("initialization failed!");
while (1);
}
Serial.println("initialization done.");
// open the file. note that only one file can be open at a time,
// so you have to close this one before opening another.
myFile = SD.open("test.txt", FILE_WRITE);
// if the file opened okay, write to it:
if (myFile) {
Serial.print("Writing to test.txt...");
myFile.println("New section");
myFile.println("This is a test file :)");
myFile.println("testing 1, 2, 3.");
myFile.println(msg);
// close the file:
myFile.close();
Serial.println("done.");
} else {
// if the file didn't open, print an error:
Serial.println("error opening test.txt");
}
}


void loop() {
// nothing happens after setup
myFile = SD.open("test.txt", FILE_WRITE);
// if the file opened okay, write to it:
if (myFile) {
Serial.print("MAIN LOOP");
myFile.println("main loop file writing");
myFile.println("sup bitch");
myFile.println("sup bitchezzzz");
myFile.println("fat");
myFile.println("adios my friend");
//myFile.println(msg);
// close the file:
myFile.close();

}
}
