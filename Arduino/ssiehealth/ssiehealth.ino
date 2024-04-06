#include "eHealth.h"


float ECG = 0;
float GSR = 0;
int AIR = 0;
int ECGfreq = 100;
int GSRAIRfreq = 10;
unsigned long lastsampleECG = 0;
unsigned long lastsampleGSRAIR = 0;
unsigned long time = 0;

void setup() {
  Serial.begin(115200);
  // eHealth.initPulsioximeter(); 
  // eHealth.initPositionSensor();
}

void loop() {
  time = millis();

  if (time >= (lastsampleECG + (1000 / ECGfreq))) {
    ECG = eHealth.getECG();
    lastsampleECG = millis();

    if (time >= (lastsampleGSRAIR + (1000 / GSRAIRfreq))) {
      GSR = eHealth.getSkinConductanceVoltage();
      AIR = eHealth.getAirFlow();
      lastsampleGSRAIR = millis();
    }
    eHealth.initPulsioximeter(); 
    eHealth.initPositionSensor();
    Serial.print(ECG);
    Serial.print(";");
    Serial.print(GSR);
    Serial.print(";");
    Serial.println(AIR);

  }
}
