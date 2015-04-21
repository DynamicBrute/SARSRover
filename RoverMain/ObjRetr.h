#include "MC.h"
#include "Arm.h"
#include "GPIO.h"
#include "HMC5883.h"
#include "Navigation.h"

#define MOVE_TIME 1000

extern boolean inRange;

boolean searchForObject();

boolean search360();

boolean goAndGet();
