#define  lim 4
int limval=0;
# define sig 5
int sigval=0;

void setup() {
pinMode(lim,INPUT_PULLUP);
pinMode(sig,OUTPUT);
Serial.begin(9600);
}

void loop() {
limval=digitalRead(lim);
Serial.print(limval); Serial.print("\t");

if (limval==1){
  digitalWrite(sig,HIGH);
  Serial.println("mother bitch");
}
if(limval==0){
  digitalWrite(sig,LOW);
  Serial.println("nothing yet whore");
}
}
