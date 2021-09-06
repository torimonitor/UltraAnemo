/* Ultrasonic distance sensor code by ELECTRONOOBS 26/07/2018 
 * Schematic: http://www.electronoobs.com/eng_arduino_tut36_sch1.php */
 
//Variables
#include <Arduino.h>

bool triggered = false;
bool Trig_in_state =  false;

void setup() {

  DDRD |= B00111000;  // Sets D3, D4, D5 outputs
  DDRB |= B00000100;  // Sets D10 as output
    
  PCICR |= (1 << PCIE0);    //enable PCMSK0 scan   
  PCMSK0 |= (1 << PCINT0);  //Set pin D8 (trigger pin) set to fire interrupt on state change. 
  PCMSK0 |= (1 << PCINT1);  //Set pin D9 (echo in) set to fire an interrupt on state change.                                             

}

void loop() {
  if(triggered)//Burst code starts...
  {
  delayMicroseconds(150);    
  /*We have seen a delay of 250uS when we've made tests
  between the 10us trig pulse and the 8 cycles burt. For some reasons, if I put 250us delay,
  I get 350 on the oscilloscope. That's why I've made a 150us delay. 
  */
  PORTD &= B11011111;   //D5 LOW    //Activate the MAX323 PNP transistor for supply  
    
  PORTD |= B00001000;   //D3 HIGH
  PORTD &= B11101111;   //D4 LOW
  delayMicroseconds(12);//12us so around 40KHz. Freq = 1/2*12us
  PORTD &= B11110111;   //D3 LOW
  PORTD |= B00010000;   //D4 HIGH
  delayMicroseconds(12);
  //We do this 8 times...
  PORTD |= B00001000;   //D3 HIGH
  PORTD &= B11101111;   //D4 LOW
  delayMicroseconds(12);
  PORTD &= B11110111;   //D3 LOW
  PORTD |= B00010000;   //D4 HIGH
  delayMicroseconds(12);

  PORTD |= B00001000;   //D3 HIGH
  PORTD &= B11101111;   //D4 LOW
  delayMicroseconds(12);
  PORTD &= B11110111;   //D3 LOW
  PORTD |= B00010000;   //D4 HIGH
  delayMicroseconds(12);

  PORTD |= B00001000;   //D3 HIGH
  PORTD &= B11101111;   //D4 LOW
  delayMicroseconds(12);
  PORTD &= B11110111;   //D3 LOW
  PORTD |= B00010000;   //D4 HIGH
  delayMicroseconds(12);

  PORTD |= B00001000;   //D3 HIGH
  PORTD &= B11101111;   //D4 LOW
  delayMicroseconds(12);
  PORTD &= B11110111;   //D3 LOW
  PORTD |= B00010000;   //D4 HIGH
  delayMicroseconds(12);

  PORTD |= B00001000;   //D3 HIGH
  PORTD &= B11101111;   //D4 LOW
  delayMicroseconds(12);
  PORTD &= B11110111;   //D3 LOW
  PORTD |= B00010000;   //D4 HIGH
  delayMicroseconds(12);

  PORTD |= B00001000;   //D3 HIGH
  PORTD &= B11101111;   //D4 LOW
  delayMicroseconds(12);
  PORTD &= B11110111;   //D3 LOW
  PORTD |= B00010000;   //D4 HIGH
  delayMicroseconds(12);

  PORTD |= B00001000;   //D3 HIGH
  PORTD &= B11101111;   //D4 LOW
  delayMicroseconds(12);

 
  PORTD &= B11000111;   //D3, D4, D5 LOW  //We have finished the burst. We set everything to low
  
  PORTB |= B00000100;   
  /*Rember, after the 8 cycles, the echo out pin, D10, is set
  to high till we receive the bounced echo signal.*/
  triggered = false;    //Reset the triggered value
  }
}



ISR(PCINT0_vect){
  //If digital D8 is high -> trigger was activated
  if(PINB & B00000001){ 
    Trig_in_state = true; //Set the Trig_in_state to true since we've detected the trigger pulse
  }
  //If trigger pin is low, the 10us pulse is over and we start the code
  else if(Trig_in_state)
  {
    triggered = true;     //Set trigered state to true
    Trig_in_state = false;    //Reset the D8 pin state
  }

  /*After the 8cycle burst each time there will be an interruption, that could be made by D8 or D9
  since those are the only 2 pins set as interrupt active
  So, since D8(trigger) is already low till next measurement, only D9 (echo in) could fire the interruption
  So, when we detect that, we set the echo out pin to low (D10) and end the echo pulse
  IMPORTANT: A better way to do this, is to also measure the echo in frequency to make sure
  it is around 40KHz, but I haven't done that. Works like this as well. 
  */
  PORTB &= 11111011; //D10, echo pin out to LOW
}
