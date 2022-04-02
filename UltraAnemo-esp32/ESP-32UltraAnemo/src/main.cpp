#include <Arduino.h>

uint8_t triggerINPin = 32;  //trigger pin
uint8_t echoINPin = 26;     //echo pin

volatile bool flagPulse = false;
volatile uint32_t pulseStartCount = 0;
volatile uint32_t pulseEndCount = 0;

// 割り込み処理 ボタンを検知
void IRAM_ATTR triggerDetected()
{
	// ボタンが押されていない場合にしか処理しない
	if (!flagPulse)
	{
    pulseStartCount = ESP.getCycleCount();
	}
}

// 割り込み処理 ボタンを検知
void IRAM_ATTR echoDetected()
{
	// ボタンが押されていない場合にしか処理しない
	if (!flagPulse)
	{
    pulseEndCount = ESP.getCycleCount();
    flagPulse = true;
	}
}

void setup()
{
	// シリアル通信を開始
	Serial.begin(9600);
	delay(50);
  Serial.print("Serial: READY");

	// GPIOピンモードを設定
	pinMode(triggerINPin, INPUT);
  pinMode(echoINPin, INPUT);
	// 割り込みを登録 トリガはLOWになった時
	attachInterrupt(triggerINPin, triggerDetected, RISING);
  attachInterrupt(echoINPin, echoDetected, RISING);
}

void loop()
{
	// 状態取得
	if (flagPulse){
    Serial.print("ClockCount: ");
    Serial.println(pulseEndCount-pulseStartCount);
    flagPulse = false;
	}
}