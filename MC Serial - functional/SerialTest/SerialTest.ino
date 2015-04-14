#include <Wire.h>

#define S1 PUSH1
#define S2 PUSH2
#define LED1 GREEN_LED
#define LED2 RED_LED
#define LED3 75

#define PACKETIZED 0
#define RESOLUTION 7

#define M1FR 0
#define M1ST 64
#define M1FF 127

#define M2FR 128
#define M2ST 192
#define M2FF 255

#define ADDR 128
#define FORWARD 0x08
#define REVERSE 0x09
#define RIGHT 0x10
#define LEFT 0x11
#define FULL 127
#define STOP 0

unsigned int command1;
unsigned int command2;

unsigned int prev;

void setup()
{
  
  
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial.begin(9600);
  
  //Wire.begin();
  
  command1 = 0;
  command2 = 0;
  prev = 0;
  //delay(5000);
  
  //Serial1.write(0b01010101);
  
  pinMode(S1, INPUT_PULLUP);  
  pinMode(S2, INPUT_PULLUP);  
  
  pinMode(LED1, OUTPUT);
  
  delay(10000);
  
  digitalWrite(LED1, HIGH);
  //Serial1.write(0xAA);
  //Serial.println("blah");
}

void loop()
{
  while(true)
  {
    accelerate(FORWARD, 100, 0, 2000);
    delay(3000);
    decelerate(FORWARD, 0, 100, 1000);
    delay(1000);
    accelerate(RIGHT, 100, 0, 2000);
    delay(1000);
    decelerate(RIGHT, 0, 100, 1000);
    delay(1000);
    accelerate(LEFT, 100, 0, 1000);
    delay(1000);
    decelerate(LEFT, 0, 100, 2000);
    delay(3000);
    accelerate(REVERSE, 50, 0, 2000);
    delay(3000);
    decelerate(REVERSE, 0, 50, 1000);
    delay(60000);
  }
}

//Takes in a command and a % of the top speed to
//send to the motor controller. Valid commands
//are FORWARD, REVERSE, LEFT, and RIGHT.
//To command a stop, input a forward command
//with a data value of 0.
void transmit(int command, int data)
{
  if(PACKETIZED)
  {
    int factor = pow(2, RESOLUTION) / 2;
    int amount = (factor * data) / 100;
    
    Serial1.write(ADDR);
    Serial1.write(command);
    Serial1.write(data);
    Serial1.write((ADDR+command+data) &  0b01111111);
  }

  else
  {
    int factor = (int)(pow(2, RESOLUTION) / 2);
    int amount = (factor * data) / 100;
    
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
    
    if(command1 > M1FF)
      command1 -= (command1 - M1FF);
    if(command1 < M1FR)
      command1 += (M1FR + command1);
    if(command2 > M2FF)
      command2 -= (command2 - M2FF);
    if(command2 < M2FR)
      command2 += (M2FR + command2);
    
    Serial1.write(command1);
    Serial1.write(command2);
    Serial.println(command1);
    Serial.println(command2);
  }

}

void accelerate(int command, int final, int current, int rate)
{
  for(int i = current; i < final; i += 5)
  {
    transmit(command, i);
    delay(rate / ((final - current) / 5));
  }
  
  transmit(command, final);
}

void decelerate(int command, int final, int current, int rate)
{
  for(int i = current; i > final; i -= 5)
  {
    transmit(command, i);
    delay(rate / ((current - final) / 5));
  }
  
  transmit(command, final);
}
