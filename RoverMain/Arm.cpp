#include "Arm.h"

Servo serv1;
Servo serv2;
int pos;


void startArm()
{
  serv1.attach(S1_D); 
  serv2.attach(S2_D);
  
  delay(100);
  
  armReset();
}

void armReset()
{
  serv1.write(UPRIGHT);
  serv2.write(180 - UPRIGHT);
  
  pos = UPRIGHT;
}

void armUp(int tarDeg)
{
  while(pos <= tarDeg && pos <= MAX_UP)
  {
    pos++;
    serv1.write(pos);
    serv2.write(180 - pos);
    delay(25);
  }
  
}

void armUp1()
{
  if(pos <= MAX_UP)
  {
    pos++;
    serv1.write(pos);
    serv2.write(180 - pos);
  }
}

void armDown(int tarDeg)
{
  while(pos >= tarDeg && pos >= MAX_DOWN)
  {
    pos--;
    serv1.write(pos);
    serv2.write(180 - pos);
    delay(25);
  }
}

void armDown1()
{
  if(pos >= MAX_DOWN)
  {
    pos--;
    serv1.write(pos);
    serv2.write(180 - pos);
  }
}
