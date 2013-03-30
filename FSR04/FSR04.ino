const int CHANNELS = 3;
int fsrPins[CHANNELS]={
  0,1,2};
int fsrReadings[CHANNELS]={
  0,0,0};

void setup(){
  for (int i=0; i<CHANNELS; i++)
    pinMode(fsrPins[i],INPUT);
  Serial.begin(9600);
}

void loop(){
  polling();
  for (int i=0; i<CHANNELS-1; i++){
    Serial.print(fsrReadings[i]);
    Serial.print(",");
  }
  Serial.println(fsrReadings[CHANNELS-1]);
  //delay(1000);
}

void polling(){
  for (int i=0; i<CHANNELS; i++)
    fsrReadings[i] = analogRead(fsrPins[i]);
}

