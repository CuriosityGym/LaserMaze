#include <CGShield.h>
#include <Wire.h>         // Require for I2C communication
CGShield fs;             // Instanciate CGShield instance

#define IDLEMODE 0
#define ARMEDMODE 1
#define TRIGMODE 2
#define ARMAFTER 5000
#define TRIGGERAFTER 50

byte RED[] =  { 255,   0,   0};
byte GREEN[] ={   0, 255,   0};
byte BLUE[] = {   0,   0, 255};

int lastCheckedTime=millis();
int lastCheckedArmedTime=millis();
byte currentmode=IDLEMODE;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  pinMode(A2, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop()
{
  
  int sensorValue = analogRead(A0);
  
  if(sensorValue<100 && currentmode==IDLEMODE)// Laser light fell on the Sensor
  {
    //Serial.println("Inside");
    //Serial.println(millis()-lastCheckedTime);
    if((millis()-lastCheckedTime)>ARMAFTER)
    {
      currentmode=ARMEDMODE;
    }
    
  }
  else
  {
    lastCheckedTime=millis();
  }
  
// Device was armed successfully, but the laser has been interrupted, sensor value went above threshold
  if(sensorValue>100 && currentmode==ARMEDMODE )
  {
    if((millis()-lastCheckedArmedTime)>TRIGGERAFTER)//Wait for TRIGGERAFTER milliseconds to ensure the laser has been triggered
    {
      currentmode=TRIGMODE;
    }
  }
  else
  {
    lastCheckedArmedTime=millis();
  }

  if(currentmode==IDLEMODE)
  {
    RGB(BLUE); 
  }

  if(currentmode==ARMEDMODE)
  {
     RGB(GREEN);
  }

  if(currentmode==TRIGMODE)
  {
     RGB(RED);
     digitalWrite(A2, HIGH);
  }
  
  
}
