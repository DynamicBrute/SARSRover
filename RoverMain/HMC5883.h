#ifndef __HMC5883_H__
#define __HMC5883_H__

#include <Wire.h>
#include <Energia.h>
#include "Navigation.h"
//#include "RoverFi.h"

/*=========================================================================
    I2C ADDRESS/BITS
    -----------------------------------------------------------------------*/
    #define HMC5883_ADDRESS_MAG					0x1E
	#define HMC5883_ADDRESS_MAG_WRITE            0x3C         // 00111100
	#define HMC5883_ADDRESS_MAG_READ            0x3D         // 00111101
/*=========================================================================*/

#define SENSORS_GAUSS_TO_MICROTESLA       (100)                   /**< Gauss to micro-Tesla multiplier */

/*=========================================================================
    REGISTERS
    -----------------------------------------------------------------------*/
    typedef enum
    {
      HMC5883_REGISTER_MAG_CRA_REG_M             = 0x00,
      HMC5883_REGISTER_MAG_CRB_REG_M             = 0x01,
      HMC5883_REGISTER_MAG_MR_REG_M              = 0x02,
      HMC5883_REGISTER_MAG_OUT_X_H_M             = 0x03,
      HMC5883_REGISTER_MAG_OUT_X_L_M             = 0x04,
      HMC5883_REGISTER_MAG_OUT_Z_H_M             = 0x05,
      HMC5883_REGISTER_MAG_OUT_Z_L_M             = 0x06,
      HMC5883_REGISTER_MAG_OUT_Y_H_M             = 0x07,
      HMC5883_REGISTER_MAG_OUT_Y_L_M             = 0x08,
      HMC5883_REGISTER_MAG_SR_REG_Mg             = 0x09,
      HMC5883_REGISTER_MAG_IRA_REG_M             = 0x0A,
      HMC5883_REGISTER_MAG_IRB_REG_M             = 0x0B,
      HMC5883_REGISTER_MAG_IRC_REG_M             = 0x0C,
      HMC5883_REGISTER_MAG_TEMP_OUT_H_M          = 0x31,
      HMC5883_REGISTER_MAG_TEMP_OUT_L_M          = 0x32
    } hmc5883MagRegisters_t;
/*=========================================================================*/

/*=========================================================================
    MAGNETOMETER GAIN SETTINGS
    -----------------------------------------------------------------------*/
    typedef enum
    {
      HMC5883_MAGGAIN_1_3                        = 0x20,  // +/- 1.3
      HMC5883_MAGGAIN_1_9                        = 0x40,  // +/- 1.9
      HMC5883_MAGGAIN_2_5                        = 0x60,  // +/- 2.5
      HMC5883_MAGGAIN_4_0                        = 0x80,  // +/- 4.0
      HMC5883_MAGGAIN_4_7                        = 0xA0,  // +/- 4.7
      HMC5883_MAGGAIN_5_6                        = 0xC0,  // +/- 5.6
      HMC5883_MAGGAIN_8_1                        = 0xE0   // +/- 8.1
    } hmc5883MagGain;	
/*=========================================================================*/

/*=========================================================================
    INTERNAL MAGNETOMETER DATA TYPE
    -----------------------------------------------------------------------*/
    typedef struct hmc5883MagData_s
    {
        float x;
        float y;
        float z;
      float orientation;
    } hmc5883MagData;
/*=========================================================================*/

/*=========================================================================
    CHIP ID
    -----------------------------------------------------------------------*/
    #define HMC5883_ID                     (0b11010100)
/*=========================================================================*/


#define declinationAngle  .1027
#define angleCorrection 30

extern float magX, magY, magZ, curHead;

extern uint8_t xhi, xlo, zhi, zlo, yhi, ylo;

static float _hmc5883_Gauss_LSB_XY = 1100.0F;  // Varies with gain
static float _hmc5883_Gauss_LSB_Z  = 980.0F;   // Varies with gain

void startCompass();

//I2C data write to the specified address. Sends the 
//specified register and the value to be placed in that
//register
void write8Mag(byte address, byte reg, byte value);

//Read in the values from the magnetometer and calculate
//the current heading in degrees
void readMag();

//Set the gain of the magnetometer
void setMagGain(hmc5883MagGain gain);

#endif
