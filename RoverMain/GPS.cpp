#include "GPS.h"
#include "RoverFi.h"

uint8_t hour, minute, seconds, year, month, day;
uint16_t milliseconds;

boolean updated;

// Floating point latitude and longitude value in degrees.
float latitude, longitude;

// Fixed point latitude and longitude value with degrees stored in units of 1/100000 degrees,
// and minutes stored in units of 1/100000 degrees.
int32_t latitude_fixed, longitude_fixed;

float homeLat, homeLon, curLat, curLon, tarLat, tarLon;
float geoidheight, altitude;
float speed, angle, magvariation, HDOP;
char lat, lon, mag;
boolean fix;
uint8_t fixquality, satellites;
 
char line[MAX_LINE_LEN];
int indx = 0;

void startGPS()
{
  Serial2.begin(9600);
  
  Serial2.println(PMTK_SET_BAUD_57600);
  
  Serial2.begin(57600);
  
  Serial2.println(PMTK_SET_NMEA_UPDATE_10HZ);
  Serial2.println(PMTK_API_SET_FIX_CTL_5HZ);
  Serial2.println(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  
  
  updated = false;
  while(!fix && !pullCurrentLocation());
    //pullCurrentLocation();
  
  homeLat = curLat;
  homeLon = curLon;
  
  Serial.print("Home: ");
  Serial.print(homeLat);
  Serial.print(", ");
  Serial.println(homeLon);
  //debugClient.print("Home: ");
  //debugClient.print(homeLat);
  //debugClient.print(", ");
  //debugClient.println(homeLon);
}

boolean parse(char *nmea)
{
  Serial.println("parsing");
  
  // do checksum check

  // first look if we even have one
  if (nmea[strlen(nmea)-4] == '*') {
    uint16_t sum = parseHex(nmea[strlen(nmea)-3]) * 16;
    sum += parseHex(nmea[strlen(nmea)-2]);
    
    // check checksum 
    for (uint8_t i=1; i < (strlen(nmea)-4); i++) {
      sum ^= nmea[i];
    }
    if (sum != 0) {
      // bad checksum :(
      //return false;
    }
  }
  
  int32_t degree;
  long minutes;
  char degreebuff[10];
  
  if (strstr(nmea, "$GPRMC")) {
   updated = true;
   
  //curLon = -81.202980;
  //curLat = 28.582378;
  
    // found RMC
    char *p = nmea;

    // get time
    p = strchr(p, ',')+1;
    float timef = atof(p);
    uint32_t time = timef;
    hour = time / 10000;
    minute = (time % 10000) / 100;
    seconds = (time % 100);

    milliseconds = fmod(timef, 1.0) * 1000;

    p = strchr(p, ',')+1;
    // Serial.println(p);
    if (p[0] == 'A') 
      fix = true;
    else if (p[0] == 'V')
      fix = false;
      //fix = true;//////////////////////////////////////////////////////////////////////////////////////////////////////////
    else
      return false;
    
    // parse out latitude
    p = strchr(p, ',')+1;
    if (',' != *p)
    {
      strncpy(degreebuff, p, 2);
      p += 2;
      degreebuff[2] = '\0';
      long degree = atol(degreebuff) * 10000000;
      strncpy(degreebuff, p, 2); // minutes
      p += 3; // skip decimal point
      strncpy(degreebuff + 2, p, 4);
      degreebuff[6] = '\0';
      long minutes = 50 * atol(degreebuff) / 3;
      latitude_fixed = degree + minutes;
      latitude = degree / 100000 + minutes * 0.000006F;
      curLat = (latitude-100*int(latitude/100))/60.0;
      curLat += int(latitude/100);
    }
    
    p = strchr(p, ',')+1;
    if (',' != *p)
    {
      if (p[0] == 'S') curLat *= -1.0;
      if (p[0] == 'N') lat = 'N';
      else if (p[0] == 'S') lat = 'S';
      else if (p[0] == ',') lat = 0;
      else return false;
    }
    
    // parse out longitude
    p = strchr(p, ',')+1;
    if (',' != *p)
    {
      strncpy(degreebuff, p, 3);
      p += 3;
      degreebuff[3] = '\0';
      degree = atol(degreebuff) * 10000000;
      strncpy(degreebuff, p, 2); // minutes
      p += 3; // skip decimal point
      strncpy(degreebuff + 2, p, 4);
      degreebuff[6] = '\0';
      minutes = 50 * atol(degreebuff) / 3;
      longitude_fixed = degree + minutes;
      longitude = degree / 100000 + minutes * 0.000006F;
      curLon = (longitude-100*int(longitude/100))/60.0;
      curLon += int(longitude/100);
    }
    
    p = strchr(p, ',')+1;
    if (',' != *p)
    {
      if (p[0] == 'W') curLon *= -1.0;
      if (p[0] == 'W') lon = 'W';
      else if (p[0] == 'E') lon = 'E';
      else if (p[0] == ',') lon = 0;
      else return false;
    }
    // speed
    p = strchr(p, ',')+1;
    if (',' != *p)
    {
      speed = atof(p);
    }
    /*
    // angle
    p = strchr(p, ',')+1;
    if (',' != *p)
    {
      float tempAngle = atof(p);
      
      angle = tempAngle;
        
    }
    
    p = strchr(p, ',')+1;
    if (',' != *p)
    {
      uint32_t fulldate = atof(p);
      day = fulldate / 10000;
      month = (fulldate % 10000) / 100;
      year = (fulldate % 100);
    }*/
    // we dont parse the remaining, yet!
    return true;
  }
  
  return false;
}

uint8_t parseHex(char c) {
    if (c < '0')
      return 0;
    if (c <= '9')
      return c - '0';
    if (c < 'A')
       return 0;
    if (c <= 'F')
       return (c - 'A')+10;
    // if (c > 'F')
    return 0;
}

void printRMC()
{
  /*Serial.print("\nTime: ");
    Serial.print(hour, DEC); Serial.print(':');
    Serial.print(minute, DEC); Serial.print(':');
    Serial.print(seconds, DEC); Serial.print('.');
    Serial.println(milliseconds);
    Serial.print("Date: ");
    Serial.print(month, DEC); Serial.print('/');
    Serial.print(day, DEC); Serial.print("/20");
    Serial.println(year, DEC);*/
    Serial.print("Fix: "); Serial.print((int)fix);
    Serial.print(" quality: "); Serial.println((int)fixquality); 
    if (fix) {
      //Serial.print("Location: ");
      //Serial.print(latitude, 4); Serial.print(lat);
      //Serial.print(", "); 
      //Serial.print(longitude, 4); Serial.println(lon);
      Serial.print("Location (in degrees, works with Google Maps): ");
      Serial.print(curLat, 8);
      Serial.print(", "); 
      Serial.println(curLon, 8);
      
      Serial.print("Speed (knots): "); Serial.println(speed);
      //Serial.print("Angle: "); Serial.println(angle);
      //Serial.print("Altitude: "); Serial.println(altitude);
      //Serial.print("Satellites: "); Serial.println((int)satellites);
   }
   /*
   debugClient.print("\nTime: ");
    debugClient.print(hour, DEC); debugClient.print(':');
    debugClient.print(minute, DEC); debugClient.print(':');
    debugClient.print(seconds, DEC); debugClient.print('.');
    debugClient.println(milliseconds);
    debugClient.print("Date: ");
    debugClient.print(month, DEC); debugClient.print('/');
    debugClient.print(day, DEC); debugClient.print("/20");
    debugClient.println(year, DEC);
    debugClient.print("Fix: "); debugClient.print((int)fix);
    debugClient.print(" quality: "); debugClient.println((int)fixquality); 
    if (fix) {
      debugClient.print("Location: ");
      debugClient.print(latitude, 4); debugClient.print(lat);
      debugClient.print(", "); 
      debugClient.print(longitude, 4); debugClient.println(lon);
      debugClient.print("Location (in degrees, works with Google Maps): ");
      debugClient.print(curLat, 4);
      debugClient.print(", "); 
      debugClient.println(curLon, 4);
      
      debugClient.print("Speed (knots): "); debugClient.println(speed);
      debugClient.print("Angle: "); debugClient.println(angle);
      debugClient.print("Altitude: "); debugClient.println(altitude);
      debugClient.print("Satellites: "); debugClient.println((int)satellites);
   }*/
}

boolean pullCurrentLocation()
{

    //delay(100);
    char c;
    if(Serial2.available())
    {
      c = Serial2.read();
    }
    
    if(c != NULL)
    {
      line[indx] = c;
      indx++;
      
      if(indx >= MAX_LINE_LEN)
      {
        indx = MAX_LINE_LEN - 1;
      }
      
      if(c == '\n')
      {
        //boolean result = parse(line);
        //parse(line);
        parse(line);
        if(updated)
        {
          updated = false;
          //Serial.println("VALID");
          Serial.println(line);
          //delay(1000);
          //debugClient.println("VALID");
          //success = true;
          //Serial.println("about to print");
          printRMC();
          return true;
        }/*
        else
        {
          Serial.println("INVALID");
          Serial.println(line);
        }*/
  
        indx = 0;
        //c = NULL;
      }
  
    }
    
    return false;
}
