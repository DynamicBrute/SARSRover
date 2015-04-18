#include "HMC5883.h"
#include <Wire.h>

#define declinationAngle  .1027

#define S1 PUSH1
#define DR PE_5

// Converts degrees to radians.
#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)
 
// Converts radians to degrees.
#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / M_PI)

float magX, magY, magZ, headingDegrees;

uint8_t xhi, xlo, zhi, zlo, yhi, ylo;

static float _hmc5883_Gauss_LSB_XY = 1100.0F;  // Varies with gain
static float _hmc5883_Gauss_LSB_Z  = 980.0F;   // Varies with gain

void setup()
{
  Serial.begin(9600);
  pinMode(S1, INPUT_PULLUP);
  pinMode(DR, INPUT);
  
  Serial.println("Welcome");
  
  uint8_t x = 0xAA;
  int y = x;
  
  Serial.println(y);
  
  uint8_t z = y;
  
  Serial.println(z);
  
  Wire.setModule(0);
  
  Serial.println("Wire opened");
  
  delay(1000);
  
  //Serial.println(Wire.available());
  
  write8Mag(HMC5883_ADDRESS_MAG, 0x00, 0x70);
  write8Mag(HMC5883_ADDRESS_MAG, 0x01, 0x20);
  write8Mag(HMC5883_ADDRESS_MAG, 0x02, 0x00);
  
  delay(1000);
  
  //Wire.beginTransmission((uint8_t)HMC5883_ADDRESS_MAG);
  //Wire.write((uint8_t)HMC5883_ADDRESS_MAG_READ);
  //Wire.write((uint8_t)0x09);
  //Wire.endTransmission();
  
  delay(100);
  /*
  Wire.requestFrom((byte)HMC5883_ADDRESS_MAG, (byte)1);
  
  Serial.print("Status: ");
  Serial.print(Wire.read());
  Serial.println();
  */
}

void loop()
{
  
  readMag();
  
  float curLat = 28.628305;
  float curLon = -81.199620;
  float tarLat = 28.628391;
  float tarLon = -81.200013;
  float curLatR = degreesToRadians(curLat);
  float curLonR = degreesToRadians(curLon);
  float tarLatR = degreesToRadians(tarLat);
  float tarLonR = degreesToRadians(tarLon);
  
  Serial.print(curLatR);
  Serial.print(" ");
  Serial.println(curLonR);
  Serial.print(tarLatR);
  Serial.print(" ");
  Serial.println(tarLonR);
  
  float tarHead = atan2(cos(degreesToRadians(curLat)) * sin(degreesToRadians(tarLat)) - sin(degreesToRadians(curLat)) * cos(degreesToRadians(tarLat)) * cos(degreesToRadians(tarLon - curLon)), sin(degreesToRadians(tarLon - curLon)) * cos(degreesToRadians(tarLat)));
  float tarHead2 = atan2(sin(tarLonR - curLonR) * cos(tarLatR), cos(curLatR) * sin(tarLatR) - sin(curLatR) * cos(tarLatR) * cos(tarLonR - curLonR));
  
  Serial.print("target heading: ");
  Serial.println(radiansToDegrees(tarHead));
  Serial.print("target heading2: ");
  Serial.println((radiansToDegrees(tarHead2) + 360));
  
  
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
    
  Serial.print("target distance: ");
  Serial.println(radiansToDegrees(d));
  
  delay(1000);
  //Serial.println();
  /*
  Wire.beginTransmission((uint8_t)HMC5883_ADDRESS_MAG);
  Wire.write((uint8_t)HMC5883_ADDRESS_MAG_WRITE);
  Wire.write((uint8_t)0x03);
  Wire.endTransmission();
  Serial.println();
  delay(1000);*/
  
}

void write8Mag(byte address, byte reg, byte value)
{
  Serial.println("Transmitting");
  Wire.beginTransmission((uint8_t)HMC5883_ADDRESS_MAG);
  Serial.println("Line Opened");
  //Wire.write((uint8_t)address);
  Wire.write((uint8_t)reg);
  Wire.write((uint8_t)value);
  Serial.println("Data Sent");
  Serial.println(Wire.endTransmission());
  Serial.println("Transmission Complete");
}

void readMag()
{
  // Read the magnetometer
  Wire.beginTransmission((uint8_t)(HMC5883_ADDRESS_MAG));
  //Wire.write((uint8_t)HMC5883_ADDRESS_MAG_READ);
  Wire.write((uint8_t)0x03);
  Wire.endTransmission();
  //Serial.println(Wire.endTransmission());
  delay(1000);
  //Serial.println("pre-request");
  //Serial.println(Wire.available());
  //Serial.println(Wire.requestFrom((uint8_t)HMC5883_ADDRESS_MAG, (uint8_t)0x06));
  Wire.requestFrom((uint8_t)HMC5883_ADDRESS_MAG, (uint8_t)0x06);
  //Serial.println("post-request");
  Serial.println(Wire.available());
  // Wait around until enough data is available
  while (Wire.available() < 6);
 /* {
    Serial.print("Waiting ");
    Serial.print(Wire.available());
    Serial.println();
  }
  
  
  for(int i = 0; i < 6; i++)
  {
    Serial.println((uint8_t)Wire.read());
  }*/
    //for(int i = 0; i < 54; i++)
      //Wire.read();
  
  // Note high before low (different than accel)  
    xhi = Wire.read();
    xlo = Wire.read();
    zhi = Wire.read();
    zlo = Wire.read();
    yhi = Wire.read();
    ylo = Wire.read();
    
    Serial.print(xhi);
    Serial.print(" ");
    Serial.print(xlo);
    Serial.print(" ");
    Serial.print(zhi);
    Serial.print(" ");
    Serial.print(zlo);
    Serial.print(" ");
    Serial.print(yhi);
    Serial.print(" ");
    Serial.print(ylo);
    Serial.println();
  
  //Serial.println(Wire.available());
  
  // Shift values to create properly formed integer (low byte first)
  magX = (int16_t)(xlo | ((int16_t)xhi << 8)) / _hmc5883_Gauss_LSB_XY * SENSORS_GAUSS_TO_MICROTESLA;
  magY = (int16_t)(ylo | ((int16_t)yhi << 8)) / _hmc5883_Gauss_LSB_Z * SENSORS_GAUSS_TO_MICROTESLA;
  magZ = (int16_t)(zlo | ((int16_t)zhi << 8)) / _hmc5883_Gauss_LSB_XY * SENSORS_GAUSS_TO_MICROTESLA;
  
  Serial.print("X: "); Serial.print(magX); Serial.print("  ");
  Serial.print("Y: "); Serial.print(magY); Serial.print("  ");
  Serial.print("Z: "); Serial.print(magZ); Serial.print("  ");Serial.println("uT");
  
  
  // ToDo: Calculate orientation
  // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  float heading = atan2(magX, magZ);
  
  // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // Find yours here: http://www.magnetic-declination.com/
  // Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
  // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
  heading += declinationAngle;
  
  // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2*PI;
    
  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
   
  // Convert radians to degrees for readability.
  headingDegrees = heading * 180/M_PI; 
  
  Serial.print("Heading (degrees): "); Serial.println(headingDegrees);
}

void setMagGain(hmc5883MagGain gain)
{
  write8Mag(HMC5883_ADDRESS_MAG_WRITE, HMC5883_REGISTER_MAG_CRB_REG_M, (byte)gain);
 
  switch(gain)
  {
    case HMC5883_MAGGAIN_1_3:
      _hmc5883_Gauss_LSB_XY = 1100;
      _hmc5883_Gauss_LSB_Z  = 980;
      break;
    case HMC5883_MAGGAIN_1_9:
      _hmc5883_Gauss_LSB_XY = 855;
      _hmc5883_Gauss_LSB_Z  = 760;
      break;
    case HMC5883_MAGGAIN_2_5:
      _hmc5883_Gauss_LSB_XY = 670;
      _hmc5883_Gauss_LSB_Z  = 600;
      break;
    case HMC5883_MAGGAIN_4_0:
      _hmc5883_Gauss_LSB_XY = 450;
      _hmc5883_Gauss_LSB_Z  = 400;
      break;
    case HMC5883_MAGGAIN_4_7:
      _hmc5883_Gauss_LSB_XY = 400;
      _hmc5883_Gauss_LSB_Z  = 255;
      break;
    case HMC5883_MAGGAIN_5_6:
      _hmc5883_Gauss_LSB_XY = 330;
      _hmc5883_Gauss_LSB_Z  = 295;
      break;
    case HMC5883_MAGGAIN_8_1:
      _hmc5883_Gauss_LSB_XY = 230;
      _hmc5883_Gauss_LSB_Z  = 205;
      break;
  } 
}
