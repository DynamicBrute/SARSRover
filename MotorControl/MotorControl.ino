#include "MC.h"

void setup()
{
  Serial.begin(9600);
  Serial.println("starting");
  
  // put your setup code here, to run once:
  startSbth(true);
  
  delay(10000);
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
  
  
  transmit(RIGHT, TURN_SPEED+10);
  delay(300);
  transmit(RIGHT, TURN_SPEED);
  delay(3000);
  transmit(RIGHT, STOP);
  delay(2000);
  transmit(LEFT, TURN_SPEED+10);
  delay(300);
  transmit(LEFT, TURN_SPEED);
  delay(3000);
  transmit(LEFT, STOP);
  delay(10000);
  
}
