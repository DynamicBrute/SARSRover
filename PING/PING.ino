#define PING PE_5

#define msToCM(dur) ((dur / 29 / 2) * .01)

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  //PING
  pinMode(PING, INPUT);
}



void loop()
{
  // put your main code here, to run repeatedly:
  Serial.println(pollPing());
  delay(1000);
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
  return msToCM(duration);           // return result
}
