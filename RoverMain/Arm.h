#define S1_D PC_7
#define S1_F PC_6
#define S2_D PC_5
#define S2_F PC_4

#define UPRIGHT 100
#define MAX_UP 130
#define MAX_DOWN 10
#define SEARCH_POSITION

#define ARM_REACH_DIST 11

#include <Servo.h>

extern Servo serv1;
extern Servo serv2;
extern int pos;

void startArm();

void armReset();

void armUp(int tarDeg);

void armUp1();

void armDown(int tarDeg);

void armDown1();
