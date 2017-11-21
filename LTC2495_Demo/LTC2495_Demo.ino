#include <Arduino.h>
#include <Wire.h>
#include "LTC2495.h"
#include <SparkFunSX1509.h> // Include SX1509 library
const byte SX1509_ADDRESS = 0x3E;  // SX1509 I2C address
SX1509 io; // Create an SX1509 object to be used throughout
LTC2495 adc = LTC2495(0x45, 5.0, 15, 1.8);
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  Wire.begin();
  adc.Begin();
//  Serial.println(HEX);
  io.begin(SX1509_ADDRESS);
  io.clock(INTERNAL_CLOCK_2MHZ, 4);
  io.pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  float Val = 0;
  Val = adc.GetVoltageComp(0);
  Serial.print("ADC 0 = ");
  Serial.println(Val, 5);

//  Val = adc.GetVoltageComp(15);
//  Serial.print("ADC 15 = ");
//  Serial.println(Val, 5);
  delay(500); 

}
