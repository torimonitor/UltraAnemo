//trigger for timer overflow
volatile unsigned int overflowCount = 0;

//trigger for time calculator
volatile boolean timeTrigger = false;

//value for present TCNT1
volatile unsigned int presentTCNT1 = 0;

//output signal pin
int PIN = 13;
int HIGH_US = 125;
int LOW_US = 588;
float HIGH_INTERVAL = 0;
boolean CHK_OF_ERROR = false;

void setup() {
  //Serial Communication Setup
  Serial.begin(115200);

  //Timer1 Setup
  TCCR1A = 0; // 初期化
  TCCR1B = 0; // 初期化
  //TCNT1 = 3036; 
  TCCR1B |= (1 << CS10); // CS10 -> 1  prescaler = 1
  TIMSK1 |= (1 << TOIE1); //TOIE -> 1

  //AttachInterrupt Setup
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN, LOW);
  attachInterrupt(0, blink, RISING); //inout pi is pi2
}

void loop() {
  delay(100);
  TCCR1B |= (1 << CS10); // CS12 -> 1  prescaler = 1
  delayMicroseconds(LOW_US);
  digitalWrite(PIN,HIGH);
  delayMicroseconds(HIGH_US);
  digitalWrite(PIN, LOW);

  if(timeTrigger == true){
    delay(1000);
    intervalCalculation();
    Serial.print("OverFlow: ");
    Serial.print(overflowCount);
    Serial.print("\t");
    Serial.print("ClockCount: ");
    Serial.print(presentTCNT1);
    Serial.print("\t");
    Serial.print("ERROR: ");
    Serial.print(CHK_OF_ERROR);
    Serial.print("\t");
    Serial.print("Low Time: ");
    Serial.print(HIGH_INTERVAL,4);
    Serial.println(" us");
    timerValInit();
  }
}

ISR(TIMER1_OVF_vect) {
  overflowCount++;
}

void intervalCalculation(){
  if(overflowCount > 1){
    CHK_OF_ERROR = true;
  }
  HIGH_INTERVAL = (((float)overflowCount*65535)+(float)presentTCNT1)*1*62.5/1000; //sum of timercount * prescaler * one clock(ps) * 10^-3 = interval(us)
}

void timerValInit(){
    overflowCount = 0; //reset overflow count
    TCNT1=0; //reset TCNT1
    timeTrigger = false;
    CHK_OF_ERROR = false;
}

void blink() {
  if(timeTrigger == false){
    TCCR1B = 0b00000000; //stop timer1 untill calculation finishes
    presentTCNT1 = TCNT1;
    timeTrigger = true;
  }
}
