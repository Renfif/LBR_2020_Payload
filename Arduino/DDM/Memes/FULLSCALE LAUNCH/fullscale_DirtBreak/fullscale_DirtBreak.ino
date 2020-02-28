// FULLSCALE DIRT BREAK CODE FOR ARDUINO #1
// Receiver pins and variables
int signalpin= 9;
int sigval=0;

// H-bridge pins 
int R_en=7; 
int L_en=8;
int RPWM=5;
int LPWM=6;

// Limit switches pins and variables
int lim1=2;
int lim2=3;
int lim1val=0;
int lim2val=0;

void setup() 
{
  pinMode(signalpin,INPUT); // receiver 
  
  pinMode(R_en, OUTPUT); //H-brdige
  pinMode(L_en, OUTPUT);
  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);
  digitalWrite(R_en, HIGH);
  digitalWrite(L_en, HIGH);

  pinMode(lim1,INPUT_PULLUP); // limit switches
  pinMode(lim2,INPUT_PULLUP);

  Serial.begin(9600);
 }


void loop() {
// -------DOOR OPENING------------------------
    sigval=pulseIn(signalpin, HIGH);
    Serial.println(sigval);
    lim1val=digitalRead(lim1);
    lim2val=digitalRead(lim2);

    if (sigval >= 900 && sigval <=1100) //switch on transmitter is upward position= FORWARD
    { 
        digitalWrite(RPWM, HIGH); 
        digitalWrite(LPWM, LOW);  
          if (lim1val==1){
              digitalWrite(RPWM, LOW);
              digitalWrite(LPWM, LOW);
          }
        
    }
    
    if (sigval >= 1400 && sigval <=1500) //switch on transmitter is in middle position= STOP 
    { 
        digitalWrite(RPWM, LOW);
        digitalWrite(LPWM, LOW);
    }
    
    if (sigval >=1900 && sigval <= 2000) // switch on transmitter is in downward position= BACKWARDS
    { 
        digitalWrite(RPWM, LOW);
        digitalWrite(LPWM, HIGH);
        if (lim2val==1){
              digitalWrite(RPWM, LOW);
              digitalWrite(LPWM, LOW);
          }
             
    }


      
   delay(100);
}


 
