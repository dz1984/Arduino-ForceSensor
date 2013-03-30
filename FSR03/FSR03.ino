#include <stdlib.h>
//Channels
const int CHANNELS =3;
//Analog input pin
int fsrPins[CHANNELS]={
  0,1,2};
int fsrReadings[CHANNELS];

double fsrVoltages[CHANNELS];
double fsrResistances[CHANNELS];
double fsrConductances[CHANNELS];
double fsrForcelbs[CHANNELS];
double fsrForceNs[CHANNELS];

void setup(){
  for (int i=0; i<CHANNELS; i++)
    pinMode(fsrPins[i],INPUT);
  Serial.begin(9600);
}

void loop(){
  for (int i=0; i<CHANNELS; i++){
    polling(fsrPins[i]);
  }
  render();
  Serial.println("--------------------------");
  delay(1000);
}

void polling(int fsrPin){
  fsrReadings[fsrPin] = analogRead(fsrPin);
  if (fsrReadings[fsrPin]==0){
    fsrVoltages[fsrPin] = 0;
    fsrResistances[fsrPin] = 0;
    fsrConductances[fsrPin] = 0;    
    fsrForcelbs[fsrPin] = 0;
    fsrForceNs[fsrPin] = 0;
  }
  else{
    fsrVoltages[fsrPin] = float(map(fsrReadings[fsrPin],0,1023,0,5000));
    //fsrResistances[fsrPin] = (10000000*(5000-fsrVoltages[fsrPin]))/fsrVoltages[fsrPin];
    fsrResistances[fsrPin] = (10000000*(5000/fsrVoltages[fsrPin]));
    fsrConductances[fsrPin] = 1000000/fsrResistances[fsrPin];  
    if (fsrResistances[fsrPin]>250000000){
      fsrForcelbs[fsrPin] = fsrConductances[fsrPin]/0.0002;  
    } 
    else{
      fsrForcelbs[fsrPin] = (fsrConductances[fsrPin]-0.0012)/0.00014;
    }
    fsrForceNs[fsrPin] = fsrForcelbs[fsrPin] * 4.4;
  }
}

void render(){
  Serial.print("Channels : ");
  format(fsrPins);

  //Receive analog reading.
  Serial.print("Analog reading = ");
  format(fsrReadings);

  //Translate analog reading to Voltage(mV).
  Serial.print("Voltage reading in mV = ");
  format(fsrVoltages);

  /*
      Calculate sensor's resistance.
   Rsensor = (Rfixed*(Vtotal-Vout))/Vout
   */
  Serial.print("FSR resistance in mohms = ");
  format(fsrResistances);

  /*
      Caculate sensor's conductance.
   C = 1/R(ohms)=1000000/R(mohms)
   */
  Serial.print("Conductance in mohms: ");
  format(fsrConductances);

  /*
      Caculate lb force.
   F = (C-0.0012)/0.00014
   */
  Serial.print("Force lb = ");
  format(fsrForcelbs);

  /*
      Caculate Newtons force.
   N = F * 4.4;
   */
  Serial.print("Force N = ");
  format(fsrForceNs);

}

String format(int arr[]){
  for (int i=0; i<CHANNELS-1; i++){
    Serial.print(arr[i]);
    Serial.print(",");
  }
  Serial.println(arr[CHANNELS-1]);
}

void format(double arr[]){
  for (int i=0; i<CHANNELS-1; i++){
    Serial.print(arr[i]);
    Serial.print(",");
  }
  Serial.println(arr[CHANNELS-1]);
}






