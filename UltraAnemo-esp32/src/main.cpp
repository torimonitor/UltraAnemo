#include <Arduino.h>

const int ledCh = 0;
const int ledFreq = 40000;
const int bitNum = 8;
const int ledPin = 32;


void setup(){
  ledcSetup(ledCh, ledFreq, bitNum);
  ledcAttachPin(ledPin, ledCh);
  ledcWriteTone(ledCh, ledFreq);
}

void loop(){

}