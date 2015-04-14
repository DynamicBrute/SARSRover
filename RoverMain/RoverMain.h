/*
Main header file for Rover Control software.
*/

/*
HARDWARE LOCATIONS

HE1 PD_3 - 46
HE2 PD_1 - 48
HE3 PD_0 - 50
HE4 PQ_0 - 51
HE5 PQ_1 - 53
HE6 PQ_2 - 55

PING))) PE_5 - 24

SABERTOOTH U1Tx PP_1 - 56

COMPASS I2C0_SCL PB_2 - 67
COMPASS I2C0_SDA PB_3 - 69

GPS U2Tx PA_7 - 27
GPS U2Rx PA_6 - 25

SERVO1_DATA PC_7 - 17
SERVO1_FEEDBACK PC_6 - 19
SERVO2_DATA PC_5 - 21
SERVO2_FEEDBACK PC_4 - 23

CC3100 BoosterPack 1 (USB facing through-holes
*/

#include <Energia.h>

/*HARDWARE DEFINITIONS/FUNCTIONS*****************************************/

//Dev board//////////////////////////////////////
#define LED1 PN_1
#define LED2 PN_0
#define LED3 PF_4
#define LED4 PF_0
/////////////////////////////////////////////////


//SERVOS/////////////////////////////////////////
#define S1_D PC_7
#define S1_F PC_6
#define S2_D PC_5
#define S2_F PC_4

#include <Servo.h>

Servo S1;
Servo S2;

/************************************************************************/

/*SOFTWARE DEFINITIONS/FUNCTIONS*****************************************/

typedef enum {WAIT_FOR_TARGET, IN_TRANSIT, ACCELERATING, DECELERATING,
				OBST_AVOID, OBJ_RETR, ORIENT_TO_TARGET, RETURN_HOME} ROVER_STATE;

ROVER_STATE RS;

boolean OBJ_RETRIEVED;

//Wireless Communication/////////////////////////


/////////////////////////////////////////////////


//Navigation/////////////////////////////////////

/////////////////////////////////////////////////

/************************************************************************/
