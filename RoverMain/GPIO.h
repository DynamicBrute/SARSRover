#include <Energia.h>

//Hall effect sensors////////////////////////////
#define HE1 PD_3
#define HE2 PD_1
#define HE3 PD_0
#define HE4 PQ_0
#define HE5 PQ_1
#define HE6 PQ_2
/////////////////////////////////////////////////


extern int revCount[7];

void countRevs();

int revRange();

//PING)))////////////////////////////////////////
#define PING PE_5

#define msToCM(dur) ((dur / 29 / 2) * .01)

//Get the distance in inches to the nearest object in front
//of the PING)))
float pollPing();
/////////////////////////////////////////////////

void startGPIO();
