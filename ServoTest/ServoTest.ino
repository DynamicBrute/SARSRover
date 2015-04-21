#include <Servo.h>

#define PING PE_5

#define msToCM(dur) ((dur / 29 / 2) * .01)

#define UPRIGHT 100
#define MAX_UP 130
#define MAX_DOWN 0
#define SEARCH_POSITION

Servo serv1;
Servo serv2;
int pos;

// Control and feedback pins
int servoPin = PC_7;
int feedbackPin = PC_6;
int servo2Pin = PC_5;
int feedback2Pin = PC_4;
 
// Calibration values
int minDegrees;
int maxDegrees;
int minFeedback;
int maxFeedback;
int tolerance = 2; // max feedback measurement error
 
/*
  This function establishes the feedback values for 2 positions of the servo.
  With this information, we can interpolate feedback values for intermediate positions
*/

 
 
void setup() 
{ 
  Serial.begin(9600);
  Serial.println("start");
  
  pinMode(feedbackPin, INPUT);
  pinMode(feedback2Pin, INPUT);
  
  serv1.attach(servoPin); 
  serv2.attach(servo2Pin);
  
  delay(100);
  
  armReset();
  
  //calibrate(serv1, feedbackPin, 20, 160);  // calibrate for the 20-160 degree range
  //calibrate(serv2, feedback2Pin, 20, 160);
} 
 
void loop()
{
  //serv1.write(10);
  //serv2.write(180);
  
  Serial.println(pos);
  
  while(pos > 45)
  {
    Serial.print(pollPing());
    Serial.print(" ");
    Serial.println(pos);
    delay(1000);
    armDown1();
  }
  
  armReset();
  
  
  /*
  while(pollPing() > .06 && pos > MAX_DOWN)
    armDown1();
  Serial.println("arm down");
  delay(2000);
  armUp(145);
  Serial.println("arm up");
  */
  //armDown(40);
  
  /*for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    serv1.write(pos);              // tell servo to go to position in variable 'pos' 
    serv2.write(180 - pos);
    delay(15);                       // waits 15ms for the servo to reach the position 
    //Serial.println(getPos(feedback));

  } 
  
  delay(3000);
  /*
  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    serv1.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
    Serial.println(getPos(PC_6));
  } 
  
  Serial.println("end loop");
  delay(3000);*/
}

int getPos(int analogPin)
{
  Serial.println(analogRead(PC_6));
  
  return map(analogRead(analogPin), minFeedback, maxFeedback, minDegrees, maxDegrees);
}

void calibrate(Servo servo, int analogPin, int minPos, int maxPos)
{
  // Move to the minimum position and record the feedback value
  servo.write(minPos);
  minDegrees = minPos;
  delay(2000); // make sure it has time to get there and settle
  minFeedback = analogRead(analogPin);
  
  // Move to the maximum position and record the feedback value
  servo.write(maxPos);
  maxDegrees = maxPos;
  delay(2000); // make sure it has time to get there and settle
  maxFeedback = analogRead(analogPin);
}

float pollPing()
{
  unsigned int duration;// inches;
  
  pinMode(PING, OUTPUT);          // Set pin to OUTPUT
  digitalWrite(PING, LOW);        // Ensure pin is low
  delay(2);
  digitalWrite(PING, HIGH);       // Start ranging
  delay(5);              //   with 5 microsecond burst
  digitalWrite(PING, LOW);        // End ranging
  pinMode(PING, INPUT);           // Set pin to INPUT
  duration = pulseIn(PING, HIGH); // Read echo pulse
  //Serial.println(msToCM(duration));
  return msToCM(duration);           // return result
}

void armReset()
{
  serv1.write(UPRIGHT);
  serv2.write(180 - UPRIGHT);
  
  pos = UPRIGHT;
}

void armUp(int tarDeg)
{
  while(pos <= tarDeg && pos <= MAX_UP)
  {
    pos++;
    serv1.write(pos);
    serv2.write(180 - pos);
    delay(25);
  }
  
}

void armUp1()
{
  if(pos <= MAX_UP)
  {
    pos++;
    serv1.write(pos);
    serv2.write(180 - pos);
  }
}

void armDown(int tarDeg)
{
  while(pos >= tarDeg && pos >= MAX_DOWN)
  {
    pos--;
    serv1.write(pos);
    serv2.write(180 - pos);
    delay(25);
  }
}

void armDown1()
{
  if(pos >= MAX_DOWN)
  {
    pos--;
    serv1.write(pos);
    serv2.write(180 - pos);
  }
}
