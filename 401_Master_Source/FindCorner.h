#ifndef _FIND_CORNER_H
#define _FIND_CORNER_H


// 38 kHz is the carrier frequency
// pin 1 out, pin 2 gnd, pin 3 Vs

#define CORNER 1
#define NO_CORNER_LOW      -1
#define NO_CORNER_HIGH      -2

void findCorner();
uint32_t Decoder(uint32_t currentTime);

void findCorner()
{
	 Serial.print("Val: ");
  int corner = readIRFrequency();
  if (corner == NO_CORNER_LOW)
    Serial.println("NO_CORNER_LOW (< 50)");
  else if (corner == CORNER)
    Serial.println("Corner found (Between 50 and 150");
  else if (corner == NO_CORNER_HIGH)
    Serial.println("NO_CORNER_HIGH (>50)");
    
  // Wait just a tad so we don't print too fast.  
  delay(100);
}


// This timer interrupt will determine which of the two beacons you are pointing at.
// Each beacon is sending either a 100Hz or 50Hz signal riding on a 38KHz carrier frequency
// The sensor itself demodulates the 38KHz carrier frequency, so the digital pin should be
// receiving just the 50Hz or 100 Hz signal.
// This timer interrupt counts the number of pulses over an amount of time specified by windowTime
// at and interval time specified by sampleTime, and computes the current frequency.
//int windowTime = 100;   // ms
//int sampleTime= 1;     // ms
//int windowIters = windowTime/sampleTime;

uint32_t Decoder(uint32_t currentTime) {

  static int lastVal = digitalRead(8);
  static int iters = 0;
  static int counter = 0;

  if (iters < windowIters)
  {
    int newVal = digitalRead(8);
    if (newVal==HIGH && lastVal == LOW)
    {
      counter++;
    }
    lastVal = newVal;
  }
  else
  {
    frequency = 1000.0*(float)counter/(float)windowTime;

    counter = 0;
    int newVal = digitalRead(8);    
    lastVal = newVal;
    iters = 0;
  }

  iters++;
  return (currentTime + CORE_TICK_RATE*sampleTime);
}





#endif
