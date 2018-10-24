#ifndef _COLLECTINGBALLS_H
#define _COLLECTINGBALLS_H

#include <math.h>

int ballsCollected = 0;
double distance = 0;

const int distanceIRPin = A6;

void distanceIRSetup();
int captureBall();
int getDistance();



int getDistance()
{
  int lastReading = analogRead(distanceIRPin);
  int currentReading = analogRead(distanceIRPin);
  int temp1 = 0;
  int temp2 = 0;
  int result = 0;
  
  temp1 = (139798 * pow(lastReading, -1.551));  
  temp2 = (139798 * pow(currentReading, -1.551));  
  Serial.print("IR Distance: ");
  Serial.println(temp1);
  if((temp1-temp2) > 40)
  {
    result = 1;
  }
  return result;
 
}

void distanceIRSetup()
{
  pinMode(distanceIRPin, INPUT);
}

int captureBall()
{//assuming millimeters
    if(getDistance() == 1)
    {
      //code to drop cage
      ballsCollected++;
      //code to raise cage
      return 1;
    }
        
}













#endif