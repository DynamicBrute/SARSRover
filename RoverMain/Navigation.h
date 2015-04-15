#include <Energia.h>
#include "HMC5883.h"
#include "GPS.h"
#include "MC.h"

#define M_PI 3.14159265359

// Converts degrees to radians.
#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)
 
// Converts radians to degrees.
#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / M_PI)

#define headingLimit 20

extern float tarHead;
extern boolean avoidObst;

//Calculate the target heading based on current GPS location
//and target GPS location
void getTargetHeading();

//Command the rover to turn to the calculated target heading,
//if the rover goes past the target heading, it will readjust
boolean turnToHeading();

//Decide if a left turn or a right turn will reach the target
//heading quicker
int getDirCommand();

//Check if the rover is pointed within 5% of the target heading
boolean inHeadingRange();

//Return true if the rover has reached its destination coordinates
boolean atDestination();

//Return the distance between the current and target coordinates in
//meters
float distToTar();
