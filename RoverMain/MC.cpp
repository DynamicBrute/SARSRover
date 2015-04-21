#include "MC.h"

unsigned int command1;
unsigned int command2;
unsigned int curSpeed;

unsigned int TURN_SPEED;

int ADCommand, finalSpeed, currentSpeed, initialSpeed, rate;

boolean motorEnable;

void startSbth(boolean enable)
{
  Serial6.begin(9600);
  
  command1 = 0;
  command2 = 0;
  curSpeed = 0;
  
  ADCommand = FORWARD;
  finalSpeed = 0;
  currentSpeed = 0;
  initialSpeed = 0;
  rate = 0;
  
  motorEnable = enable;
}

void transmit(int command, int data)
{
  
  
  if(PACKETIZED)
  {
    int factor = pow(2, RESOLUTION) / 2;
    int amount = (factor * data) / 100;
    
    Serial6.write(ADDR);
    Serial6.write(command);
    Serial6.write(data);
    Serial6.write((ADDR+command+data) &  0b01111111);
  }

  else
  {
    int factor = (int)(pow(2, RESOLUTION) / 2);
    int amount = (factor * data) / 100;
    int reduction = (factor * (data - 3) / 100);
    int DS = (factor * DRIVE_SPEED) / 100;
    
    if(command == FORWARD)
    {
      command1 = M1ST + amount;
      command2 = M2ST + amount;
    }
    else if(command == REVERSE)
    {
      command1 = M1ST - amount;
      command2 = M2ST - amount;
    }
    else if(command == LEFT)
    {
      command1 = M1ST - amount;
      command2 = M2ST + amount;
    }
    else if(command == RIGHT)
    {
      command1 = M1ST + amount;
      command2 = M2ST - amount;
    }
    
    //if(command2 > M2ST + (DS / 2))
      command2 -= 2;//reduction;
    
    
    if(command1 > M1FF)
      command1 -= (command1 - M1FF);
    if(command1 < M1FR)
      command1 += (M1FR + command1);
    if(command2 > M2FF)
      command2 -= (command2 - M2FF);
    if(command2 < M2FR)
      command2 += (M2FR + command2);
    
    if(motorEnable)
    {
      //Serial.print("transmitting ");
      //Serial.print(data);
      //Serial.print(" ");
      //Serial.print(command1);
      //Serial.print(" ");
      //Serial.println(command2);
      
      Serial6.write(command1);
      Serial6.write(command2);
    }
    
    curSpeed = data;
  }

}

void setAccel(int command, int finalS, int accRate)
{
  ADCommand = command;
  finalSpeed = finalS;
  initialSpeed = curSpeed;
  currentSpeed = curSpeed;
  rate = accRate;
}

void accelerate()
{
  //Serial.print(ADCommand);
  //Serial.print(" ");
  //Serial.print(finalSpeed);
  //Serial.print(" ");
  //Serial.print(initialSpeed);
  //Serial.print(" ");
  //Serial.print(currentSpeed);
  //Serial.print(" ");
  //Serial.println(rate);
  currentSpeed += ACCEL_STEP;  
  transmit(ADCommand, currentSpeed);
  delay(20);//rate / ((finalSpeed - initialSpeed) / ACCEL_STEP));
}

void decelerate()
{
  //Serial.print(ADCommand);
  //Serial.print(" ");
  //Serial.print(finalSpeed);
  //Serial.print(" ");
  //Serial.print(initialSpeed);
  //Serial.print(" ");
  //Serial.print(currentSpeed);
  //Serial.print(" ");
  //Serial.println(rate);  
  currentSpeed -= ACCEL_STEP;  
    transmit(ADCommand, currentSpeed);
    delay(20);//rate / ((initialSpeed - finalSpeed) / ACCEL_STEP));
}

boolean calibrate()
{
  while(true)
  {
    transmit(RIGHT, TURN_SPEED);
    
    countRevs();
    
    transmit(RIGHT, STOP);
    
    if(revRange() < REV_DIFF_LIM)
      return true;
      
    TURN_SPEED += 3;
    
    if(TURN_SPEED > 80)
      return false;
  }
}
