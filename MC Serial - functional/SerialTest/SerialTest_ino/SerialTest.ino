#define S1 USR_SW1
#define S2 USR_SW2

#define MCPin 4

#define M1 1
#define M2 128
#define STOP 0

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop()
{
  // put your main code here, to run repeatedly:
  
  if(S1)
  {
    Serial.print(M1 + 50);
  }
  
  if(S2)
  {
    Serial.print(M2 + 50);
  }
  
  if(S1 && S2)
  {
    Serial.print(STOP);
  }
}
