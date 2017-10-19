#include <Arduino.h>
#include <Wire.h>
#include "LTC2495.h"

LTC2495 adc = LTC2495(0x45, 5.0);
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  Wire.begin();
  adc.Begin();
  Serial.println(HEX);
}

void loop() {
  // put your main code here, to run repeatedly:
  float Val = 0;
  Val = adc.GetVoltageDiff(0, 1);
  Serial.print("ADC 0 = ");
  Serial.println(Val, 5);
  Serial.println(Val + 2.5, 5);
  delay(500); 

}
