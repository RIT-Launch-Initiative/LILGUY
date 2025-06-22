#include <LSM6DS3.h>
#include "Wire.h"
#include <PDM.h>

LSM6DS3 lilIMU(I2C_MODE, 0x6A);
float currentAccMagnitude = 0;//In G's
int counter = 0;
float sampleRate = 500;//HZ
int boostThreshold = 5;//G's
int boostTimeMS = 400;//Length of time to feel g's before going "AAHHHAHA"
float samplePeriod;
float onTime = 20;//Time Camera is on in minutes after detecting boost

void setup() {
    
    pinMode(9, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200); 
    lilIMU.begin();
    
    samplePeriod = (1/sampleRate)*1000;// converts HZ to MS to wait at end of loop, hoping that its fast enough to not mater
    
    digitalWrite(9, LOW);  //LED blinking sequence to indicate it has powered on 
    for(int i = 0; i < 3; i++)
    {
      digitalWrite(LED_GREEN, LOW); 
      delay(2000);
      digitalWrite(LED_GREEN, HIGH);
      delay(2000);
    }

}

void loop(){
  
    currentAccMagnitude = pow(lilIMU.readFloatAccelX(), 2) + pow(lilIMU.readFloatAccelY(), 2) + pow(lilIMU.readFloatAccelZ(), 2);
    Serial.println(counter);
    Serial.println(currentAccMagnitude);
    
    if (currentAccMagnitude > pow(boostThreshold, 2)) {
        counter++;
    }
    else if (counter > 0){
        counter--;
    }
    if (counter > boostTimeMS/samplePeriod){
        counter = 0;
      
        
        Serial.println("BOOST");
        digitalWrite(9,HIGH);
        delay(onTime*60000);//Min to MS       
        digitalWrite(9,LOW);
        Serial.println("RECORDING DONE");
        
    }
    delay(samplePeriod);

    
}
