#include <Arduino.h>
#include <Wire.h>
#include "LTC2495.h"

#if defined(TLOG_PINOUT)
#include <SparkFunSX1509.h> // Include SX1509 library
const byte SX1509_ADDRESS = 0x3E;  // SX1509 I2C address
SX1509 io; // Create an SX1509 object to be used throughout
#endif

//No need to change if using either TLog or ALog
//If using custom board setup, change address, Vcc, voltage ref pin, and voltage ref value
LTC2495 adc = LTC2495(0x45, 5.0, 15, 1.8); //Initialize the LTC2495 ADC module with addres, voltage range, voltage referance pin, and value of voltage referance
float BattDiv = 0.1; //Voltage divder used to measure battery input voltage on TLogv1

void setup() {
  Serial.begin(38400); //Initalize Serial comunication at 38400 bps
  
  Wire.begin(); //Begin I2C comunication
  adc.Begin(); //Start the LTC2495 ADC module
  
#if defined(TLOG_PINOUT)
  Serial.println("TLog Enabled");
  
  io.begin(SX1509_ADDRESS); //Initalize IO Expander 
  io.clock(INTERNAL_CLOCK_2MHZ, 4);
  io.pinMode(3, OUTPUT);  //Turn on voltage referance, via IO expander
  digitalWrite(3, HIGH);
#elif defined(ALOG_PINOUT)
  Serial.println("ALog Enabled");
  
  pinMode(19, OUTPUT);  //Turn on voltage referance, via MCU pins
  digitalWrite(19, HIGH);
#endif
}

void loop() {
  float Val = 0; //Temporary value to store ADC result
  float Raw = 0; //Temporary value for raw ADC result
  
  Serial.println("LTC2495 ADC Values:");
  
  #if defined(TLOG_PINOUT)
    for(int i = 0; i < 16; i++){
      Val = adc.GetVoltageComp(i); //Get the compaensated voltage from pin i
      Raw = adc.GetVoltage(i);
      Serial.print("Pin "); Serial.print(i);
      Serial.print(": Comp = ");
      Serial.print(Val, 5); Serial.print("V");
      Serial.print(" Raw = ");
      Serial.print(Raw, 5); Serial.print("V\n");
    }
    
    float BatVoltage = adc.GetVoltage(14);
    float RefVoltage = adc.GetVoltage(15);
    
    Serial.print("\nSystem Info:\n");
    Serial.print("Referance Voltage = "); Serial.print(RefVoltage); Serial.print("V\n");
    Serial.print("Battery Voltage = "); Serial.print(BatVoltage/BattDiv); Serial.print("V\n\n");
    
  #elif defined(ALOG_PINOUT)
    int BatPin = 7;
    for(int i = 0; i < 16; i++){
      Val = adc.GetVoltageComp(i); //Get the compaensated voltage from pin i
      Raw = adc.GetVoltage(i);
      Serial.print("Pin "); Serial.print(i);
      Serial.print(": Comp = ");
      Serial.print(Val, 5); Serial.print("V");
      Serial.print(" Raw = ");
      Serial.print(Raw, 5); Serial.print("V\n");
    }
    
    Serial.print("\nInternal ADC Values:\n");

    int ADCPins[] = {0, 1, 4, 5, 6, 7}; 
    for(int i = 0; i < 6; i++){
      Val = analogRead(ADCPins[i])*(float(3.3)/float(1024.0)); //Get the voltage from pin i
      Serial.print("Pin "); Serial.print(ADCPins[i]);
      Serial.print(": Val = ");
      Serial.print(Val, 5); Serial.print("V\n");
    }
    float BatVoltage = analogRead(BatPin)*(float(3.3)/float(1024.0));
    Serial.print("\nSystem Info:\n");
    Serial.print("Referance Voltage = "); Serial.print(adc.GetVoltage(15)); Serial.print("V\n");
    Serial.print("Battery Voltage = "); Serial.print(BatVoltage/BattDiv); Serial.print("V\n\n");
  #endif

  delay(500); 

}
