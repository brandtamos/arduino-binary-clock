/* Binary clock

*/

//#include <math.h>

//M0 pins
//these uses the analog input pins because we need
//pins 2 and 3 for interupts! 
const int M0_BIT0_PIN = A0;
const int M0_BIT1_PIN = A1;
const int M0_BIT2_PIN = A2;
const int M0_BIT3_PIN = A3;

//M1 pins
const int M1_BIT0_PIN = 4;
const int M1_BIT1_PIN = 5;
const int M1_BIT2_PIN = 6;

//H0 pins
const int H0_BIT0_PIN = 7;
const int H0_BIT1_PIN = 8;
const int H0_BIT2_PIN = 9;
const int H0_BIT3_PIN = 10;

//H1 pins
const int H1_BIT0_PIN = 11;
const int H1_BIT1_PIN = 12;

//Second indicator
const int SECOND_INDICATOR_PIN = 13;

//interrupt pins (used for setting time)
const int SET_MINUTE_INTERRUPT_PIN = 2;
const int SET_HOUR_INTERRUPT_PIN = 3;

const int DECOUNCE_WAIT_TIME_MS = 200;
//value that holds referential total second value
long gSecondValue = 0;

//making these values global so the interrupt can modify them
int gMinuteValue = 0;
int gHourValue = 0;


void setup()
{
  //set led pins to output
  pinMode(M0_BIT0_PIN, OUTPUT);
  pinMode(M0_BIT1_PIN, OUTPUT);
  pinMode(M0_BIT2_PIN, OUTPUT);
  pinMode(M0_BIT3_PIN, OUTPUT);
  pinMode(M1_BIT0_PIN, OUTPUT);
  pinMode(M1_BIT1_PIN, OUTPUT);
  pinMode(M1_BIT2_PIN, OUTPUT);
  pinMode(H0_BIT0_PIN, OUTPUT);
  pinMode(H0_BIT1_PIN, OUTPUT);
  pinMode(H0_BIT2_PIN, OUTPUT);
  pinMode(H0_BIT3_PIN, OUTPUT);
  pinMode(H1_BIT0_PIN, OUTPUT);
  pinMode(H1_BIT1_PIN, OUTPUT);

  //setup interrupt pins
  pinMode(SET_MINUTE_INTERRUPT_PIN, INPUT_PULLUP);
  pinMode(SET_HOUR_INTERRUPT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SET_MINUTE_INTERRUPT_PIN), incrementMinuteValue, FALLING);
  attachInterrupt(digitalPinToInterrupt(SET_HOUR_INTERRUPT_PIN), incrementHourValue, FALLING);
}

void loop()
{
  outputMinutes();
  outputHours();
  writeSecondIndicator();
  tick();
  delay(1000);
}
void outputMinutes(){
  int m0Value = getM0Value();
  int m1Value = getM1Value();
  writeM0Value(m0Value);
  writeM1Value(m1Value);
}
void outputHours(){
  int h0Value = getH0Value();
  int h1Value = getH1Value();
  writeH0Value(h0Value);
  writeH1Value(h1Value);
}
void writeM0Value(int m0Value){
  digitalWrite(M0_BIT0_PIN, bitRead(m0Value, 0));
  digitalWrite(M0_BIT1_PIN, bitRead(m0Value, 1));
  digitalWrite(M0_BIT2_PIN, bitRead(m0Value, 2));
  digitalWrite(M0_BIT3_PIN, bitRead(m0Value, 3));
}

void writeM1Value(int m1Value){
  digitalWrite(M1_BIT0_PIN, bitRead(m1Value, 0));
  digitalWrite(M1_BIT1_PIN, bitRead(m1Value, 1));
  digitalWrite(M1_BIT2_PIN, bitRead(m1Value, 2));
}

void writeH0Value(int h0Value){
  digitalWrite(H0_BIT0_PIN, bitRead(h0Value, 0));
  digitalWrite(H0_BIT1_PIN, bitRead(h0Value, 1));
  digitalWrite(H0_BIT2_PIN, bitRead(h0Value, 2));
  digitalWrite(H0_BIT3_PIN, bitRead(h0Value, 3));
}

void writeH1Value(int h1Value){
  digitalWrite(H1_BIT0_PIN, bitRead(h1Value, 0));
  digitalWrite(H1_BIT1_PIN, bitRead(h1Value, 1));
}

void writeSecondIndicator(){
  digitalWrite(SECOND_INDICATOR_PIN, bitRead(gSecondValue, 0));
}
void tick(){
  // there are 86,400 seconds in a day!
  gSecondValue = (gSecondValue + 1) % 86400;
  //gMinuteValue = (int)floor(gSecondValue / 60) % 60;
  //gHourValue = (int)floor(gSecondValue / 3600) % 24;
  if(gSecondValue % 60 == 0) incrementMinuteValue();
  if(gSecondValue % 3600 == 0) incrementHourValue();
}

int getM0Value(){
  int minutes = gMinuteValue;
  return minutes % 10;
}

int getM1Value(){
  int minutes = gMinuteValue;
  minutes = floor(minutes/10); //shift least significant number out
  return minutes % 10;
}

int getH0Value(){
 int hours = gHourValue;
 return hours % 10;
}

int getH1Value(){
  int hours = gHourValue;
  hours = floor(hours/10);
  return hours % 10;
}

void incrementMinuteValue(){
  //used to debounce button press
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > DECOUNCE_WAIT_TIME_MS) 
  {
    //increment minute value and write out to LEDs
    gMinuteValue = (gMinuteValue + 1) % 60;
    outputMinutes();
  }
  last_interrupt_time = interrupt_time;
}

void incrementHourValue(){
  //used to debounce button press
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > DECOUNCE_WAIT_TIME_MS) 
  {
    //increment hour value and write to LEDs
    gHourValue = (gHourValue + 1) % 24;
    outputHours();
  }
  last_interrupt_time = interrupt_time;
}