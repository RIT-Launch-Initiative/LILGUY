#include <PDM.h>

void setup(){
    Serial.begin(115200);
    pinMode(9, OUTPUT);
}
void loop(){
    digitalWrite(9,HIGH);
    Serial.println("ON");
    delay(2000);
    digitalWrite(9,LOW);
    Serial.println("OFF");
    delay(2000);
}

