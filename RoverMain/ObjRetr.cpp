#include "ObjRetr.h"

boolean inRange;

boolean searchForObject()
{
  if(search360())
    if(goAndGet())
      return true;
      
  transmit(FORWARD, SEARCH_SPEED);
  delay(MOVE_TIME);
  transmit(FORWARD, STOP);
  
  if(search360())
    if(goAndGet())
      return true;
      
  transmit(REVERSE, SEARCH_SPEED);
  delay(MOVE_TIME);
  transmit(REVERSE, STOP);
  
  readMag();
  tarHead = (int)(curHead + 90) % 360;
  
  turnToHeading();
  
  transmit(FORWARD, SEARCH_SPEED);
  delay(MOVE_TIME);
  transmit(FORWARD, STOP);
  
  if(search360())
    if(goAndGet())
      return true;
      
  transmit(REVERSE, SEARCH_SPEED);
  delay(MOVE_TIME);
  transmit(REVERSE, STOP);
  
  readMag();
  tarHead = (int)(curHead + 90) % 360;
  
  turnToHeading();
  
  transmit(FORWARD, SEARCH_SPEED);
  delay(MOVE_TIME);
  transmit(FORWARD, STOP);
  
  if(search360())
    if(goAndGet())
      return true;
      
  transmit(REVERSE, SEARCH_SPEED);
  delay(MOVE_TIME);
  transmit(REVERSE, STOP);
  
  return false;
}

boolean search360()
{
  readMag();
  tarHead = curHead;
  
  for(int i = 0; i < 180; i++)
  {
    transmit(LEFT, TURN_SPEED);
    delay(25);
    transmit(LEFT, STOP);
    delay(50);
    
    if(pollPing() < 3)
    {      
      inRange = true;
      return true;
    }
  }
  
  turnToHeading();
  
  return false;
}

boolean goAndGet()
{
  float prevPing = pollPing();
  float curPing = pollPing();
  
  while(curPing <= prevPing)
  {
    prevPing = curPing;
    
    transmit(FORWARD, SEARCH_SPEED);
    
    curPing = pollPing();
    
    if(curPing <= ARM_REACH_DIST)
    {
      armDown(MAX_DOWN);
      
      delay(1000);
      
      armUp(MAX_UP);
      
      return true;
    }
  }
  
  return false;
}
