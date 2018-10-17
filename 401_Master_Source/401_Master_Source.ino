#include "ME401_Radio.h"
#include "ME401_PID_IR.h"
#include "pathoptimization.h"

#include "RobotsOnTheField.h"




//test

#define MY_ROBOT_ID 6


void setup() {

  // Set up the serial port in case we want output or input
  Serial.begin(115200);

  // Initialize the RFM69HCW radio
  ME401_Radio_initialize();

  // Initialize the PID and IR interrupts
  // TODO: Change the kp, ki, kd in the ME491_PID_IR.h file to match your new tunings
  //       that you did after installing the sensor on your robot
  setupPIDandIR();

  
}

void loop() {

  Serial.print("millis:");
  Serial.println(millis());


  // TODO: This is where you implement all of your code for your robot. 
  // REMEMBER: You must implement a state machine and have a good diagram of that state machine.
  //           I HIGHLY recommend that you discuss this with the TAs and professor before starting to code.


  // Here are a few examples of some of the core functionalities of the robot. If things ever stop working, I would
  // recommend keeping a copy of this original template around so that you can load it to your robot and check whether
  // you have a software issue or whether there is a hardware/wiring issue.

  
  

  // Simple example of looking for the corner beacon
  if (readIRFrequency() == CORNER)
  {
    Serial.println("I see the corner");
  }
  else
  {
    Serial.print("Can't see the corner:");
    Serial.println(frequency);
  }

  // Simple example of reading the robot and ball positions from the radio
  updateRobotPoseAndBallPositions();
  RobotPose robot = getRobotPose(MY_ROBOT_ID);
  if (robot.valid == true)
  {
    Serial.println("The camera can see my robot");
    printRobotPose(robot);
  }

  BallPosition ballPos[20];

  
  toTheFront(robotPoses);                //Sorts our bot to the front of the list



  int numBalls = getBallPositions(ballPos);
  Serial.print("NUM BALLS: ");
  Serial.println(numBalls);
  printBallPositions(numBalls, ballPositions);

  BallPosition targetBall;               //Closest ball which we will go to
  targetBall = findNextBall(robotPoses, ballPos);
  angleTo(robot,targetBall);  //finds angle to turn to be pointed at target ball


  delay(10);
}


