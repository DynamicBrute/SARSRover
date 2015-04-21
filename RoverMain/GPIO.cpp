#include "GPIO.h"

int revCount[7];

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

float pollPing()
{
  unsigned int duration;// inches;
  
  pinMode(PING, OUTPUT);          // Set pin to OUTPUT
  digitalWrite(PING, LOW);        // Ensure pin is low
  delay(2);
  digitalWrite(PING, HIGH);       // Start ranging
  delay(5);              //   with 5 microsecond burst
  digitalWrite(PING, LOW);        // End ranging
  pinMode(PING, INPUT);           // Set pin to INPUT
  duration = pulseIn(PING, HIGH); // Read echo pulse
  return msToCM(duration);           // return result
}

void countRevs()
{
  for(int i = 0; i < 100; i++)
  {
    if(!digitalRead(HE1))
      revCount[1]++;
      
    if(!digitalRead(HE2))
      revCount[2]++;
      
    if(!digitalRead(HE3))
      revCount[3]++;
      
    if(!digitalRead(HE4))
      revCount[4]++;
      
    if(!digitalRead(HE5))
      revCount[5]++;
      
    if(!digitalRead(HE6))
      revCount[6]++;
  }
}

int revRange()
{
  int max = -1;
  int min = 1000;
  
  for(int i = 1; i < 7; i++)
  {
    if(revCount[i] > max)
      max = revCount[i];
    if(revCount[i] < min)
      min = revCount[i];
  }
  
  return max - min;
}

//REFERENCE CODE
//LED off if H.E.S. is not reading a signal
  /*if(digitalRead(HE1))
    digitalWrite(LED, LOW);
  else
    digitalWrite(LED, HIGH);*/
