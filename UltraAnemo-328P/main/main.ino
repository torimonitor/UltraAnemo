//trigger for timer overflow
volatile int overflowCount = 0;

//trigger for time calculator
volatile boolean timeTrigger = false;

//value for present TCNT1
volatile int presentTCNT1 = 0;

//output signal pin
int pin = 13;

void setup() {
  //Serial Communication Setup
  Serial.begin(115200);

  //Timer1 Setup
  TCCR1A = 0; // 初期化
  TCCR1B = 0; // 初期化
  //TCNT1 = 3036; 
  TCCR1B |= (1 << CS12); // CS12 -> 1  prescaler = 256
  TIMSK1 |= (1 << TOIE1); //TOIE -> 1

  //AttachInterrupt Setup
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  attachInterrupt(0, blink, RISING); //inout pi is pi2
}

ISR(TIMER1_OVF_vect) {
  overflowCount++;
}

void loop() {
  TCCR1B |= (1 << CS12); // CS12 -> 1  prescaler = 256
  digitalWrite(pin, LOW);
  delay(90);
  timeTrigger = false;
  digitalWrite(pin,HIGH);
  delay(10);
}

void blink() {
  if(timeTrigger == false){
    TCCR1B = 0b00000000; //stop timer1 untill calculation finishes
    presentTCNT1 = TCNT1;
    Serial.print("OverFlow: ");
    Serial.print(overflowCount);
    Serial.print("\t");
    Serial.print("ClockCount: ");
    Serial.println(presentTCNT1);
    overflowCount = 0; //reset overflow count
    TCNT1=0; //reset TCNT1
    timeTrigger = true;
  }
}
