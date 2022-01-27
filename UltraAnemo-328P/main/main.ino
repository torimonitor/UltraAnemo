void setup() {
  Serial.begin(9600);
  TCCR1A = 0; // 初期化
  TCCR1B = 0; // 初期化
  TCNT1 = 3036; 
  TCCR1B |= (1 << CS12); // CS12 -> 1  prescaler = 256
  TIMSK1 |= (1 << TOIE1); //TOIE -> 1
}

ISR(TIMER1_OVF_vect) {
  Serial.println(millis());
  TCNT1 = 3036;
}

void loop() {
}
