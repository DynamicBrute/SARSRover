#include <Servo.h>

Servo myservo;
int pos;

// Control and feedback pins
int servoPin = PC_7;
int feedbackPin = PC_6;
 
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
  
  pinMode(PC_6, INPUT);
  
  myservo.attach(servoPin); 
  
  calibrate(myservo, feedbackPin, 20, 160);  // calibrate for the 20-160 degree range
} 
 
void loop()
{
  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
    Serial.println(getPos(PC_6));

  } 
  
  delay(3000);
  
  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
    Serial.println(getPos(PC_6));
  } 
  
  Serial.println("end loop");
  delay(3000);
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
