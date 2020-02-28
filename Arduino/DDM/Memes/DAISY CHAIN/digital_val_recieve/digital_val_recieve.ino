#define sig 5
int sigval=0;

void setup() {
pinMode(sig,INPUT);
Serial.begin(9600);
}

void loop() {
sigval=digitalRead(sig);
Serial.println(sigval);
}
