/*
 * https://howtomechatronics.com/tutorials/arduino/how-to-extend-arduino-pwm-outputs-tlc5940-tutorial/
 * Arduino and TLC5940 Tutorial - Simple Example
 * by Dejan Nedelkovski, www.HowToMechatronics.com
 */
#include "Tlc5940.h" 
#include <math.h>

//#define maxValue (pow(2, 12)-1)
#define maxValue (pow(2, 10)-1)
#define interval 2000
#define VPRG 12
#define XLAT 9
#define SIN 11
#define SCLK 13
#define BLANK 10
#define GSCLK 3

void setup() {
  digitalWrite(VPRG, HIGH);
  pinMode(VPRG, OUTPUT);
  digitalWrite(XLAT, LOW);
  pinMode(XLAT, OUTPUT);
  digitalWrite(SIN, HIGH);
  pinMode(SIN, OUTPUT);
  digitalWrite(SCLK, LOW);
  pinMode(SCLK, OUTPUT);
  digitalWrite(BLANK, LOW);
  pinMode(BLANK, OUTPUT);
  digitalWrite(GSCLK, LOW);
  pinMode(GSCLK, OUTPUT);
  delay(3);

  for(unsigned int i=0; i<100; i++) {
    digitalWrite(SCLK, HIGH);
    delayMicroseconds(10);
    digitalWrite(SCLK, LOW);
    delayMicroseconds(10);
  }
  delay(3);
  digitalWrite(XLAT, HIGH);
  delay(3);
  digitalWrite(XLAT, LOW);

  delay(3);
  digitalWrite(VPRG, LOW);
  
  delay(3);
  
  Tlc.init(0); // Initiates the TLC5940 and set all channels off
}

void setLed(unsigned int red, unsigned int green, unsigned int blue) {
  Tlc.set(1, red);
  Tlc.set(12, red);
  Tlc.set(2, green);
  Tlc.set(13, green);
  Tlc.set(3, blue);
  Tlc.set(14, blue);
  Tlc.update();
}

void loop() {
  unsigned long currentMillis = millis();
  unsigned long previousMillis = currentMillis;
  //The Tlc.clear() function clears all the outputs, or sets the PWM value of all outputs to 0
  Tlc.clear();
  delay(1);
  
   
  setLed(maxValue, maxValue, maxValue);
  delay(3000);

  setLed(maxValue, 0, 0);
  delay(2000);
 
  setLed(0, maxValue ,0);
  delay(2000);
  
  setLed(0, 0, maxValue);
  delay(2000);

  
  currentMillis = millis();
  previousMillis = millis();
  while (currentMillis - previousMillis < interval) {
    unsigned int b = (((float)(currentMillis - previousMillis)) / interval) * maxValue;
    setLed(b, b ,b);
    currentMillis = millis();
  }

  previousMillis = millis();
  while (currentMillis - previousMillis < interval) {
    unsigned int b = (((float)(currentMillis - previousMillis)) / interval) * maxValue;
    setLed(b, 0 ,0);
    currentMillis = millis();
  }
  previousMillis = millis();
  while (currentMillis - previousMillis < interval) {
    unsigned int b = (((float)(currentMillis - previousMillis)) / interval) * maxValue;
    setLed(0, b ,0);
    currentMillis = millis();
  }
  previousMillis = millis();
  while (currentMillis - previousMillis < interval) {
    unsigned int b = (((float)(currentMillis - previousMillis)) / interval) * maxValue;
    setLed(0, 0 ,b);
    currentMillis = millis();
  }
  Tlc.clear();
  delay(1);
  Tlc.update();
  exit(0);
}
