int Ch3_door_pin= 10;
int Door=0;

int R_en=7; 
int L_en=8;
int RPWM=5;
int LPWM=6;

void setup() 
{
  pinMode(Ch3_door_pin,INPUT); 
  pinMode(R_en, OUTPUT);
  pinMode(L_en, OUTPUT);
  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);

  digitalWrite(R_en, HIGH);
  digitalWrite(L_en, HIGH);

  Serial.begin(9600);
 }


void loop() {
// -------DOOR OPENING------------------------
    Door=pulseIn(Ch3_door_pin, HIGH);
    Serial.println(Door);

    if (Door >= 900 && Door <=1100) //switch on transmitter is upward position= FORWARD
    { 
        digitalWrite(RPWM, LOW); 
        digitalWrite(LPWM, HIGH);  
        
    }
    if (Door >= 1400 && Door <=1500) //switch on transmitter is in middle position= STOP 
    { 
        digitalWrite(RPWM, LOW);
        digitalWrite(LPWM, LOW);
    }
    if (Door >=1900 && Door <= 2000) // switch on transmitter is in downward position= BACKWARDS
    { 
        digitalWrite(RPWM, HIGH);
        digitalWrite(LPWM, LOW);
             
    }


      
   // delay(100);
}


 
