#include <Energia.h>

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

#define DRIVE_SPEED 30
#define TURN_SPEED 43
#define SEARCH_SPEED 25

#define ACCEL_STEP 5

extern unsigned int command1;
extern unsigned int command2;
extern unsigned int curSpeed;

extern int ADCommand, finalSpeed, currentSpeed, initialSpeed, rate;

extern boolean motorEnable;


void startSbth(boolean enable);

//Takes in a rover movement command and a data value (% of 100)
//to transmit to the Sabertooth
void transmit(int command, int data);

//Will invoke a series of "transmit" commands to advance the motors
//from the current value to the final value over a specified amount of
//time in milliseconds
void setAccel(int command, int final, int rate);
void accelerate();
void decelerate();
