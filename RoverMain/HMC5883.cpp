#include "HMC5883.h"
#include "RoverFi.h"

float magX, magY, magZ, curHead;

uint8_t xhi, xlo, zhi, zlo, yhi, ylo;

void startCompass()
{
  Wire.setModule(0);
  
  delay(100);
  
  write8Mag(HMC5883_ADDRESS_MAG, 0x00, 0x70);
  write8Mag(HMC5883_ADDRESS_MAG, 0x01, 0x20);
  write8Mag(HMC5883_ADDRESS_MAG, 0x02, 0x00);
  
  delay(100);
}

void write8Mag(byte address, byte reg, byte value)
{
  Wire.beginTransmission((uint8_t)HMC5883_ADDRESS_MAG);
  Wire.write((uint8_t)reg);
  Wire.write((uint8_t)value);
  Wire.endTransmission();
}

void readMag()
{
  // Read the magnetometer
  Wire.beginTransmission((uint8_t)(HMC5883_ADDRESS_MAG));
  Wire.write((uint8_t)0x03);
  Wire.endTransmission();
  delay(1000);

  Wire.requestFrom((uint8_t)HMC5883_ADDRESS_MAG, (uint8_t)0x06);

  // Wait around until enough data is available
  while (Wire.available() < 6);

  // Note high before low (different than accel)  
    xhi = Wire.read();
    xlo = Wire.read();
    zhi = Wire.read();
    zlo = Wire.read();
    yhi = Wire.read();
    ylo = Wire.read();
    /*
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
  */
  //Serial.println(Wire.available());
  
  // Shift values to create properly formed integer (low byte first)
  magX = (int16_t)(xlo | ((int16_t)xhi << 8)) / _hmc5883_Gauss_LSB_XY * SENSORS_GAUSS_TO_MICROTESLA;
  magY = (int16_t)(ylo | ((int16_t)yhi << 8)) / _hmc5883_Gauss_LSB_Z * SENSORS_GAUSS_TO_MICROTESLA;
  magZ = (int16_t)(zlo | ((int16_t)zhi << 8)) / _hmc5883_Gauss_LSB_XY * SENSORS_GAUSS_TO_MICROTESLA;
  /*
  Serial.print("X: "); Serial.print(magX); Serial.print("  ");
  Serial.print("Y: "); Serial.print(magY); Serial.print("  ");
  Serial.print("Z: "); Serial.print(magZ); Serial.print("  ");Serial.println("uT");
  */
  
  // ToDo: Calculate orientation
  // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  float heading = atan2(magX, magZ);
  
  // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // Find yours here: http://www.magnetic-declination.com/
  // Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
  // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
  heading += declinationAngle + degreesToRadians(angleCorrection);
  
  // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2*PI;
    
  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
   
  // Convert radians to degrees for readability.
  curHead = heading * 180/M_PI; 
  
  Serial.print("Heading (degrees): "); Serial.println(curHead);
  debugClient.print("Heading (degrees): "); debugClient.println(curHead);
}

void setMagGain(hmc5883MagGain gain)
{
  write8Mag(HMC5883_ADDRESS_MAG, HMC5883_REGISTER_MAG_CRB_REG_M, (byte)gain);
 
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
