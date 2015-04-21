#include "MC.h"

void setup()
{
  Serial.begin(9600);
  Serial.println("starting");
  
  // put your setup code here, to run once:
  startSbth(true);
  
  delay(5000);
}

void loop()
{
  
  Serial.println("loop");
  
  /*
  // put your main code here, to run repeatedly:
  setAccel(FORWARD, DRIVE_SPEED, 1);
  
  while(curSpeed < DRIVE_SPEED)
  {
    Serial.println("accel"); 
    accelerate();
  }
  
  delay(10000);
  
  setAccel(FORWARD, STOP, 1);
  
  while (curSpeed > 0)
  {
    Serial.println("decel");
    decelerate();
  }
  
  delay(30000);*/
  
  for(int i = 0; i < 10; i++)
  {
    transmit(RIGHT, TURN_SPEED+20);
    delay(100);
    transmit(RIGHT, TURN_SPEED-10);
    delay(100);
  }
  transmit(RIGHT, STOP);
  delay(2000);
  
  for(int i = 0; i < 10; i++)
  {
    transmit(LEFT, TURN_SPEED+20);
    delay(100);
    transmit(LEFT, TURN_SPEED-10);
    delay(100);
  }

  transmit(LEFT, STOP);
  delay(10000);
  
}
