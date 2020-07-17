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

void setup() {
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
  delay(2000);

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
