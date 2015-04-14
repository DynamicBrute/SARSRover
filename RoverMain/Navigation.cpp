#include "Navigation.h"

float tarHead;

void getTargetHeading()
{
//  var R = 6371000; // metres
//var φ1 = lat1.toRadians();
//var φ2 = lat2.toRadians();
//var Δφ = (lat2-lat1).toRadians();
//var Δλ = (lon2-lon1).toRadians();
  readMag();
  Serial.print("heading: " );
  Serial.println(curHead);
  //tarHead = tan((tarLon - curLon) / (tarLat - curLat));
  //tarHead = atan2( sin(degreesToRadians(tarLon - curLon)) * cos(degreesToRadians(tarLat)), cos(degreesToRadians(curLat)) * sin(degreesToRadians(tarLat)) - sin(degreesToRadians(curLat)) * cos(degreesToRadians(tarLat)) * cos(degreesToRadians(tarLon - curLon)) );
  tarHead = atan2(cos(degreesToRadians(curLat)) * sin(degreesToRadians(tarLat)) - sin(degreesToRadians(curLat)) * cos(degreesToRadians(tarLat)) * cos(degreesToRadians(tarLon - curLon)), sin(degreesToRadians(tarLon - curLon)) * cos(degreesToRadians(tarLat)));
  //θ = atan2( sin Δλ ⋅ cos φ2 , cos φ1 ⋅ sin φ2 − sin φ1 ⋅ cos φ2 ⋅ cos Δλ )
  Serial.print("target heading rads: ");
  Serial.println(tarHead, 8);
  tarHead = radiansToDegrees(tarHead);
  if(tarHead < 0)
    tarHead += 360;
  Serial.print("target heading: ");
  Serial.println(tarHead);
}

boolean turnToHeading()
{
  readMag();
  
  int dirCommand = getDirCommand();
  
  transmit(dirCommand, 45);
  
  while(!inHeadingRange())// && getDirCommand() == dirCommand)
  {
    readMag();
  }
  
  delay(200);
  transmit(LEFT, 0);
  
  if(!inHeadingRange())
    turnToHeading();
  
  return true;
}

int getDirCommand()
{
  int dirCommand = LEFT;
  
  if((int)(curHead + 180) % 360 >= tarHead)
    dirCommand = RIGHT;
    
  return dirCommand;
}

boolean inHeadingRange()
{
  int angleDiff = (int)(curHead - tarHead + 180) % 360 - 180;
  
  return (angleDiff <= headingLimit && angleDiff >= headingLimit * -1);
}

boolean atDestination()
{
  pullCurrentLocation(); 
  if(distToTar() < 3)
      return true; 
  
    return false;
}

float distToTar()
{
    float R = 6371000; // m
    float temp1 = tarLat - curLat;
    float temp2 = tarLon - curLon;
    float dLat = degreesToRadians(temp1);
    float dLon = degreesToRadians(temp2); 
    float a = sin(dLat/2) * sin(dLat/2) +
        cos(degreesToRadians(curLat)) * cos(degreesToRadians(tarLat)) * 
        sin(dLon/2) * sin(dLon/2); 
    float c = 2 * atan2(sqrt(a), sqrt(1-a)); 
    float d = R * c;
    return d;
}