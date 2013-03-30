//A0-input pin
int fsrPin = 0;

int fsrReading;
double fsrVoltage;
double fsrResistance;
double fsrConductance;
double fsrForcelb;
double fsrForceN;

void setup(){
  pinMode(fsrPin,INPUT);
  Serial.begin(9600);
}

void loop(){
  //Receive analog reading.
  fsrReading = analogRead(fsrPin);
  Serial.print("Analog reading = ");
  Serial.println(fsrReading);
  
  //Translate analog reading to Voltage(mV).
  fsrVoltage = float(map(fsrReading,0,1023,0,5000));
  Serial.print("Voltage reading in mV = ");
  Serial.println(fsrVoltage);
 
  if (fsrVoltage < 0.0001){
    Serial.println("No pressure");
  }else{
    /*
      Calculate sensor's resistance.
      Rsensor = (Rfixed*(Vtotal-Vout))/Vout
    */
    fsrResistance = (10000000*(5000-fsrVoltage))/fsrVoltage;
    Serial.print("FSR resistance in mohms = ");
    Serial.println(fsrResistance);
    
    /*
      Caculate sensor's conductance.
      C = 1/R(ohms)=1000000/R(mohms)
    */
    fsrConductance = 1000000/fsrResistance;  
    Serial.print("Conductance in mohms: ");
    Serial.println(fsrConductance);
    
    /*
      Caculate lb force.
      F = (C-0.0012)/0.00014
     */
    fsrForcelb = (fsrConductance-0.0012)/0.00014;
    Serial.print("Force lb = ");
    Serial.println(fsrForcelb);
    
    /*
      Caculate Newtons force.
      N = F * 4.4;
     */
    fsrForceN = fsrForcelb * 4.4;
    Serial.print("Force N = ");
    Serial.println(fsrForceN);
  }
  Serial.println("--------------------------");
  delay(1000);
}
