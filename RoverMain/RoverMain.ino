#include "RoverMain.h"
#include "RoverFi.h"
#include "MC.h"
#include "GPS.h"
#include "HMC5883.h"
#include "Navigation.h"
#include "GPIO.h"



#include <Wire.h>
#include <Servo.h>
#include <SPI.h>
#include <WiFi.h>



#define LED RED_LED

#define S1 PUSH1
#define S2 PUSH2



void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(S1, INPUT_PULLUP);
  
  //Debug serial
  Serial.begin(9600);
  Serial.println("Starting");
  
  //PING))) and Hall Effect
  startGPIO();
  
  //Sabertooth
  //startSbth(true);
  startSbth(false);
  
  ledCode(1);
  //GPS
  startGPS();
  
  ledCode(2);
  //Compass
  startCompass();
  
  ledCode(3);
  //CC3100
  startWiFi();
  mainServer.begin();
   
  
  
  //
  alreadyConnected = false;
  alreadyConnectedMain = false;
  //debugClientdebugServer.begin();
  
  char serverIP[] = "192.168.1.102";
    
  //Serial.println("Attempt to connect to debug server");
  //while(debugClient.connect(serverIP, 3284) == 0);
  /*
  while(!alreadyConnected)
  {
    debugClient = debugServer.available();
    digitalWrite(LED, HIGH);
    if (debugClient) {
      if (!alreadyConnected) {
        // clead out the input buffer:
        debugClient.flush();
        Serial.println("We have a new client");
        debugClient.println("Hello, client!");
        alreadyConnected = true;
      }
    }
    delay(100);
    digitalWrite(LED, LOW);
    delay(100);
  }*/
  
  curLon = -81.202980;
  curLat = 28.582378;
  tarLat = 28.582183f;
  tarLon = -81.202770f;
  
  Serial.print(curLat);
  Serial.print(" ");
  Serial.println(curLon);
  Serial.print(tarLat);
  Serial.print(" ");
  Serial.println(tarLon);
  
  
  RS = IN_TRANSIT;
  OBJ_RETRIEVED = false;  
}

void loop()
{
  //if(pollPing() < 100 && RS != WAIT_FOR_TARGET && !atDestination())
    //RS = OBST_AVOID;
  
  switch(RS)
  {
    case WAIT_FOR_TARGET:
          ledCode(4);
          waitForTarget();
          RS = ORIENT_TO_TARGET;
          
          break;
    
    case ORIENT_TO_TARGET:
          ledCode(5);
          //pullCurrentLocation();
          ledCode(6);
          getTargetHeading();
          ledCode(7);
          turnToHeading();
          
          RS = IN_TRANSIT;
          
          break;
    
    case IN_TRANSIT:
          ledCode(8);
          //if necesssary, correct heading
          
          if(!inHeadingRange())
          {
            RS = ORIENT_TO_TARGET;
            break;
          }
          
          //Destination reached, begin object retrieval
          if(atDestination() && !OBJ_RETRIEVED)
          {
            RS = OBJ_RETR;
            break;
          }
          
          //Mission complete, wait for a new mission 
          if(atDestination() && OBJ_RETRIEVED)
          {
            RS = WAIT_FOR_TARGET;
            break;
          }
          
          if(curSpeed < DRIVE_SPEED)
          {
            setAccel(FORWARD, DRIVE_SPEED, (DRIVE_SPEED - curSpeed) * 100);
            RS = ACCELERATING;
          }
          else
          {
            setAccel(FORWARD, 0, (curSpeed - 0) * 100);
            RS = DECELERATING;
          }
          
          break;
    
    case ACCELERATING:
          if(curSpeed != finalSpeed)
            {accelerate();}
          else
          {
            RS = IN_TRANSIT;
          }
          break;
    
    case DECELERATING:
          if(curSpeed != finalSpeed)
            {decelerate();}
          else
          {
            RS = IN_TRANSIT;
          }
          break;
    
    case OBST_AVOID:
    
          break;
    
    case OBJ_RETR:
          
          OBJ_RETRIEVED = true;
          RS = RETURN_HOME;
          
          break;
          
    case RETURN_HOME:
          tarLat = homeLat;
          tarLon = homeLon;
          RS = ORIENT_TO_TARGET;
          
          break;
  }
  
  /*
  Serial.println(distToTar());
  //debugClient.println(distToTar());
  
  if(atDestination())
  {
    digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(LED, LOW);
  }
  /*
  else
  {
    Serial.println("reading");
    readMag();
    //getTargetHeading();
    Serial.println(tarHead);
    Serial.println(curHead);
    //if(inHeadingRange())
    //turnToHeading();
  //}
  */
  //delay(1000);
  
}

void ledCode(int value)
{
  digitalWrite(LED4, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED1, LOW);
  
  if(value % 2 != 0 && value > 0)
    digitalWrite(LED4, HIGH);
  
  value /= 2;
  
  if(value % 2 != 0 && value > 0)
    digitalWrite(LED3, HIGH);
  
  value /= 2;
  
  if(value % 2 != 0 && value > 0)
    digitalWrite(LED2, HIGH);
  
  value /= 2;
  
  if(value % 2 != 0 && value > 0)
    digitalWrite(LED1, HIGH);
}





//REFERENCE CODE
//LED off if H.E.S. is not reading a signal
  /*if(digitalRead(HE1))
    digitalWrite(LED, LOW);
  else
    digitalWrite(LED, HIGH);*/

