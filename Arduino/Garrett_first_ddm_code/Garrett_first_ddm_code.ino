
int receiverCh1=3; // for fly sky
int Ch1=0; // tracks receiver values as it is read

int R_en=7; // for hbridge
int L_en=8; // for hbridge
int RPWM=5; // for hbridge
int LPWM=6;// for hbridge

void setup() 
{
  pinMode(receiverCh1,INPUT); 
 
  pinMode(R_en, OUTPUT);
  pinMode(L_en, OUTPUT);
  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);

  Serial.begin(9600);
 }


void loop() {
    digitalWrite(R_en, HIGH);
    digitalWrite(L_en, HIGH);
    Ch1=pulseIn(receiverCh1,HIGH);
    
    //Serial.println("fuck you");
    Serial.println(Ch1);

    
  //  FlySky controller transmitting data
    if (Ch1 >= 900 && Ch1 <=1100) //switch on transmitter is upward position= FORWARD
    { 
        digitalWrite(RPWM, LOW); 
        digitalWrite(LPWM, HIGH);    
    }
    if (Ch1 >= 1400 && Ch1 <=1500) //switch on transmitter is in middle position= STOP 
    { 
        digitalWrite(RPWM, LOW);
        digitalWrite(LPWM, LOW);
    }
    if (Ch1 >=1900 && Ch1 <= 2000) // switch on transmitter is in downward position= BACKWARDS
    { 
        digitalWrite(RPWM, HIGH);
        digitalWrite(LPWM, LOW);
        
    }

/*
Pseudocodeland:

ch1 number = some number
if ch1# > 0:
    loop
        a = ch1#
        wait
        b = ch1#(new one)
        c = b-a
        if c < 100:
            ch1real = a
*/


}


 
