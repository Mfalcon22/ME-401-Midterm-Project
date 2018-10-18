#ifndef _PID_TURNING_H
#define _PID_TURNING_H

#include <PID_v1.h>

const int MOTOR1 = 30;
const int MOTOR2 = 31;

// PID tuning gains
float ku = 30.5; // ultimate gain
float Tu = 0.13; // seconds
double kp=0.8*ku,ki=0.0,kd=0.8*ku*Tu*0.125; // classic PD


// Global variables for the timer interrupt handling
int pidSampleTime = 10;
long counterPID=1;


// Global variables for the PID controller
double input=0, output=0, setpoint=0;
PID myPID(&input, &output, &setpoint,kp,ki,kd, DIRECT);

// Forward declaration of functions to be used that are defined later than their first use
uint32_t MyCallback(uint32_t currentTime);

void setupPID(void)
{

  // Set up the motor outputs
  pinMode(MOTOR1, OUTPUT);
  pinMode(MotorDirectionPin, OUTPUT);

  digitalWrite(MotorPWMPin,0);
  digitalWrite(MotorDirectionPin,0);

  
  pinMode(MotorPWMPin, OUTPUT);

  //Setup the pid 
  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(pidSampleTime);
  myPID.SetOutputLimits(-2400,2400);

  // Initialize the sensor on pin 8 as an input
  pinMode(IRSensorInputPin,INPUT);

  // Initialize the timer interrupt that decodes the IR beacon signal
  attachCoreTimerService(MyCallback);
}

uint32_t MyCallback(uint32_t currentTime) {
  char newLeftA = digitalRead(EncoderAPin);
  char newLeftB = digitalRead(EncoderBPin);

  position += (newLeftA ^ lastLeftB) - (lastLeftA ^ newLeftB); 

  if((lastLeftA ^ newLeftA) & (lastLeftB ^ newLeftB))
  {
    errorLeft = true;
  }

  lastLeftA = newLeftA;
  lastLeftB = newLeftB;

  if (counterPID % 100*pidSampleTime == 0)
  {
    angle = position*0.133333;
    input = angle;      

    myPID.Compute();

    if (output < 0)
    {
      digitalWrite(MotorDirectionPin,1);
    }
    else
    {
      digitalWrite(MotorDirectionPin,0);
    }  
  analogWrite(MotorPWMPin,abs(output));
  counterPID = 0;
  }
  counterPID++;
  
  if (counterIR % 100*irSampleTime == 0)
  {
    static int lastVal = digitalRead(IRSensorInputPin);
    static int iters = 0;
    static int ircounter = 0;

    if (iters < windowIters)
    {
      int newVal = digitalRead(IRSensorInputPin);
      if (newVal==HIGH && lastVal == LOW)
      {
        ircounter++;
      }
      lastVal = newVal;
    }
    else
    {
      frequency = 1000.0*(float)ircounter/(float)windowTime;
  
      ircounter = 0;
      int newVal = digitalRead(IRSensorInputPin);    
      lastVal = newVal;
      iters = 0;
    }
  
    iters++;
    
    counterIR=0;
  }
  counterIR++;

  return (currentTime + CORE_TICK_RATE/100);
}





#endif