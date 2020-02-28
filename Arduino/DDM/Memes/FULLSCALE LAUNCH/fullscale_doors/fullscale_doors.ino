// Dual H-bridge pins
#define in1 6 //in1 and 2 are for motor A
#define in2 7
#define in3 4 //in3 and 4 are for motor B
#define in4 5

// H-bridge pins 
int R_en=8; 
int L_en=9;
int RPWM=10;
int LPWM=11;

// Input signal
#define lim 3
int limval=0;

// for timing
unsigned long time_since_pressed=0;
//unsigned long previous_time = 0;

void setup() {
  pinMode(in1, OUTPUT); // Dual H-bridge
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(lim, INPUT_PULLUP); //signal
  
  pinMode(R_en, OUTPUT); //H-brdige
  pinMode(L_en, OUTPUT);
  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);
  digitalWrite(R_en, HIGH);
  digitalWrite(L_en, HIGH);
  Serial.begin(9600);
}
void loop() {
  limval=digitalRead(lim);
  Serial.print(limval);
  if (limval==0)        // All motors stopped
  {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      digitalWrite(RPWM, LOW);
      digitalWrite(LPWM, LOW);
  }
  if (limval==1)        //
  {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      
      time_since_pressed=millis();
      
      Serial.println(time_since_pressed);
            //digitalWrite(RPWM, HIGH);
            //digitalWrite(LPWM, LOW);

           if (time_since_pressed >10000){  
            //previous_time += time_since_pressed;
            digitalWrite(RPWM, HIGH);
            digitalWrite(LPWM, LOW);
             }
          else{
            digitalWrite(RPWM, LOW);
            digitalWrite(LPWM, LOW); 
            }
   }
  
}
