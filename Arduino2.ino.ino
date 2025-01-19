int ledPin=4;
int ldrPin=39;
int ldrVlue;

void setup() {
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);

}

void loop() {
  ldrValue=analogRead(ldrPin);
  Serial.println(ldrValue);
 
  if (ldrVlue>2000){
      analogWrite(ledPin,50);
      delay(500);
  }
 
  else {
    analogWrite(ledPin,255);
  }

}