//A0 - input pin
int fsrPin = 0;
byte fsrReading;

void setup(){
  pinMode(fsrPin,INPUT);
  Serial.begin(9600);
}

void loop(){
  //Translate 0~1023 to 0~254
  fsrReading = map(analogRead(fsrPin),0,1023,0,254);
  //Write a byte to PC through Serial port.
  Serial.write(fsrReading);
  delay(1000);
}
