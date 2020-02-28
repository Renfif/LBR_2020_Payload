int Ch4_orient_pin= 3; // for orientation pin on the frisky
int Orient=0; // tracks receiver values as they are read
int mapval=0;
int map2=0;

int R_en=7; 
int L_en=8;
int RPWM=5;
int LPWM=6;

int Ch5_dirt_pin= 9;
int Dirt=0;

int R_en2=12; 
int L_en2=13;
int RPWM2=10;
int LPWM2=11;

//int Ch6_arm_pin=A2;
//int Arm=0;

void setup() 
{
  pinMode(Ch4_orient_pin,INPUT); 
  pinMode(R_en, OUTPUT);
  pinMode(L_en, OUTPUT);
  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);

  pinMode(R_en2, OUTPUT);
  pinMode(L_en2, OUTPUT);
  pinMode(RPWM2, OUTPUT);
  pinMode(LPWM2, OUTPUT);

  digitalWrite(R_en, HIGH);
  digitalWrite(L_en, HIGH);

  digitalWrite(R_en2, HIGH);
  digitalWrite(L_en2, HIGH);

  Serial.begin(9600);
 }


void loop() {
//---------ARMING SWITCH---------------------
   /* Arm=analogRead(Ch6_arm_pin);
    Serial.print("Arm:");
    Serial.println(Arm);*/


// ---------ORIENTATION----------------------
    Orient=pulseIn(Ch4_orient_pin, HIGH);
    //Serial.println(Orient);

    mapval=map(Orient, 1475, 2010, 0, 255);
    //Serial.println(mapval);

    if (mapval >= 129)
    {
      map2=map(mapval, 129, 255,0 , 255);
      analogWrite(RPWM, 0);
      analogWrite(LPWM, map2);
    }
    if (mapval < 129)
    {
      map2=map(mapval, 0, 129, 255, 0);
      analogWrite(RPWM, map2);
      analogWrite(LPWM, 0);
    }
    
    //Serial.println(map2);

// -------DIRT BREAK------------------------
    Dirt=pulseIn(Ch5_dirt_pin, HIGH);
    Serial.println(Dirt);

    if (Dirt >= 900 && Dirt <=1100) //switch on transmitter is upward position= FORWARD
    { 
        //digitalWrite(RPWM, LOW); 
        //digitalWrite(LPWM, HIGH);  
        analogWrite(RPWM2,255 ); 
        analogWrite(LPWM2, 0);  
    }
    if (Dirt >= 1400 && Dirt <=1500) //switch on transmitter is in middle position= STOP 
    { 
        //digitalWrite(RPWM2, LOW);
        //digitalWrite(LPWM2, LOW);
        analogWrite(RPWM2,0 ); 
        analogWrite(LPWM2, 0);
    }
    if (Dirt >=1900 && Dirt <= 2000) // switch on transmitter is in downward position= BACKWARDS
    { 
        //digitalWrite(RPWM2, HIGH);
        //digitalWrite(LPWM2, LOW);
        analogWrite(RPWM2,0 ); 
        analogWrite(LPWM2, 255);
        
    }


      
   // delay(100);
}


 
