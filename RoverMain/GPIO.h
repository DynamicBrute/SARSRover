#include <Energia.h>

//Hall effect sensors////////////////////////////
#define HE1 PD_3
#define HE2 PD_1
#define HE3 PD_0
#define HE4 PQ_0
#define HE5 PQ_1
#define HE6 PQ_2
/////////////////////////////////////////////////


//PING)))////////////////////////////////////////
#define PING PE_5

//Get the distance in inches to the nearest object in front
//of the PING)))
int pollPing();
/////////////////////////////////////////////////

void startGPIO();
