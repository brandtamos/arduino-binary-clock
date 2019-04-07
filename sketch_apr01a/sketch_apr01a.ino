/* Blinking LED
 * ------------
 *
 * turns on and off a light emitting diode(LED) connected to a digital  
 * pin, in intervals of 2 seconds. Ideally we use pin 13 on the Arduino 
 * board because it an LED built-in
 *
 * Created 1 June 2005
 * copyleft 2005 DojoDave <http://www.0j0.org>
 * http://arduino.berlios.de
 *
 * based on an orginal by H. Barragan for the Wiring i/o board
 */

int ledPin = 13;                // LED connected to digital pin 13
int bit0pin = 7;
int bit1pin = 6;
int bit2pin = 5;
int bit3pin = 4;
int bit4pin = 3;
int bit5pin = 2;
int secondValue = 0;
long randNumber;
void setup()
{
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
  pinMode(bit0pin, OUTPUT);
  pinMode(bit1pin, OUTPUT);
  pinMode(bit2pin, OUTPUT);
  pinMode(bit3pin, OUTPUT);
  pinMode(bit4pin, OUTPUT);
  pinMode(bit5pin, OUTPUT);
  randomSeed(analogRead(0));
}

void loop()
{
  
  //digitalWrite(ledPin, HIGH);   // sets the LED on
  writeToLeds(secondValue);
  delay(1000);                  // waits for a second
  secondValue = (secondValue + 1) % 60;
  //digitalWrite(ledPin, LOW);    // sets the LED off
  //delay(1000);                  // waits for a second
}

void writeToLeds(int value){
    digitalWrite(bit0pin, bitRead(value, 0));
    digitalWrite(bit1pin, bitRead(value, 1));
    digitalWrite(bit2pin, bitRead(value, 2));
    digitalWrite(bit3pin, bitRead(value, 3));
    digitalWrite(bit4pin, bitRead(value, 4));
    digitalWrite(bit5pin, bitRead(value, 5));
  
}
