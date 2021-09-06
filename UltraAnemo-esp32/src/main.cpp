#include <Arduino.h>

//Definitions for pulse generator and transmitter
const int ledCh = 0;
const int ledFreq = 40000;
const int bitNum = 8;
const int ledPin = 32;

//Definitions for reciever
const int echoPin = 34;

//Definitions for echo intterrupt
//Note: This is for 40Mhz CPU
volatile unsigned long startCountVar = 0;
volatile unsigned long stopCountVar = 0;
volatile boolean echoFlag = false;
volatile unsigned int cycleCount = 0;
volatile unsigned long startTimer = 0;
volatile unsigned long checkTimer = 0;

void setup(){
  //Setup for serial communications
  Serial.begin(9600);

  //Setup for pulse generator and transmitter
  ledcSetup(ledCh, ledFreq, bitNum);

  //Setup for reciever
  //attachInterrupt(echoPin, stopCount, RISING);
}

void loop(){
  ledcAttachPin(ledPin, ledCh);
  ledcWriteTone(ledCh, ledFreq);
  //Serial.println("Pulse ON");
  delay(500);
  ledcDetachPin(ledPin);
  //Serial.println("Pulse OFF");
  delay(500);
}

//if prevopus program works, then change hoge to main.
/*

//for echo intterrupt
void stopCount(){
  //no intterrupts untill all pulse passes
  noInterrupts();
  stopCountVar = ESP.getCycleCount();
  echoFlag = true;
  delay(250);
  interrupts();
}

void hoge(){
  Serial.println("Start");
  //start counting
  startCountVar = ESP.getCycleCount();
  //generate pulse for 250us
  ledcAttachPin(ledPin, ledCh);
  ledcWriteTone(ledCh, ledFreq);
  delayMicroseconds(250);
  ledcDetachPin(ledPin);
  delayMicroseconds(250);
  startTimer = millis();

  while(true || checkTimer-startTimer>1000){
    checkTimer = millis();
    if(echoFlag){
      //calcurate cycleCount and restart cycleCount
      cycleCount = stopCountVar - startCountVar;
      Serial.println(cycleCount);
      echoFlag = false;
      //restart counting
      break;
    }
  }
  ESP.restart();
  Serial.println("Restart");
}
*/