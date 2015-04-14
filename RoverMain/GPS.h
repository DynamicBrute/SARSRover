//#include "RoverMain.h"
#include <Energia.h>

#include "Adafruit_GPS.h"
#include "RoverFi.h"

#define MAX_LINE_LEN 120

extern uint8_t hour, minute, seconds, year, month, day;
extern uint16_t milliseconds;

extern boolean updated;

// Floating point latitude and longitude value in degrees.
extern float latitude, longitude;

// Fixed point latitude and longitude value with degrees stored in units of 1/100000 degrees,
// and minutes stored in units of 1/100000 degrees.
extern int32_t latitude_fixed, longitude_fixed;

extern float homeLat, homeLon, curLat, curLon, tarLat, tarLon;
extern float geoidheight, altitude;
extern float speed, angle, magvariation, HDOP;
extern char lat, lon, mag;
extern boolean fix;
extern uint8_t fixquality, satellites;
 
extern char line[MAX_LINE_LEN];
extern int indx;

void startGPS();

//Parses an NMEA sentence to search for specified data (RMC)
boolean parse(char *nmea);

//Read integer out of an ASCII character
uint8_t parseHex(char c);

//Debug function to print all values read from the GPS
void printRMC();

//Update GPS data
void pullCurrentLocation();
