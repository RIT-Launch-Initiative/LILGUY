#include <LSM6DS3.h>
#include "Wire.h"

LSM6DS3 lilIMU(I2C_MODE, 0x6A);
float currentAccMagnitude = 0;//In G's
int counter = 0;
float sampleRate = 500;//HZ
int boostThreshold = 2;//G's
int boostTimeMS = 250;//Length of time to feel g's before going "AAHHHAHA"
float samplePeriod;
float onTime = 0.1;//Time Camera is on in minutes after detecting boost

void setup() {
    Serial.begin(115200); 
    lilIMU.begin();
    samplePeriod = (1/sampleRate)*1000;// converts HZ to MS to wait at end of loop, hoping that its fast enough to not mater
    
}

void loop(){
    digitalWrite(9,LOW);
    currentAccMagnitude = pow(lilIMU.readFloatAccelX(), 2) + pow(lilIMU.readFloatAccelY(), 2) + pow(lilIMU.readFloatAccelZ(), 2);
    Serial.println(counter);
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
        
    }
    delay(samplePeriod);
}