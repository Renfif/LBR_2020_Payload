#include <EnableInterrupt.h>

#define rcPin1 6

volatile uint16_t pulsestart=0; 
volatile uint16_t pulsewidth=0;
//volatile unsigned long pulsestart=0; 
//volatile unsigned long pulsewidth=0;
volatile uint16_t risingcount=0;
volatile uint16_t fallingcount=0;

void counttime()
{
  pulsestart = micros();
  risingcount++;
}
void subtracttime()
{
  pulsewidth = micros()- pulsestart;
  fallingcount++;
}

void setup() {
  Serial.begin(9600);
  pinMode(rcPin1, INPUT_PULLUP);  
  enableInterrupt(rcPin1, counttime, RISING);
  enableInterrupt(rcPin1, subtracttime, FALLING);
}

void loop() {
  //delay(1000);
  Serial.print("risingcount: ");
  Serial.print(risingcount);  
  Serial.print(" fallingcount: ");
  Serial.println(fallingcount); 
  //Serial.print("pulsewidth: ");
  //Serial.println(pulsewidth);
}