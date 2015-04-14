#include "GPIO.h"

void startGPIO()
{
  //H.E.S.
  pinMode(HE1, INPUT);
  pinMode(HE2, INPUT);
  pinMode(HE3, INPUT);
  pinMode(HE4, INPUT);
  pinMode(HE5, INPUT);
  pinMode(HE6, INPUT);
  
  //PING
  pinMode(PING, INPUT);
}

int pollPing()
{
  unsigned int duration, inches;
  
  pinMode(PING, OUTPUT);          // Set pin to OUTPUT
  digitalWrite(PING, LOW);        // Ensure pin is low
  delay(2);
  digitalWrite(PING, HIGH);       // Start ranging
  delay(5);              //   with 5 microsecond burst
  digitalWrite(PING, LOW);        // End ranging
  pinMode(PING, INPUT);           // Set pin to INPUT
  duration = pulseIn(PING, HIGH); // Read echo pulse
  inches = duration / 74 / 2;        // Convert to inches
  return inches;           // return result
}
