#include "ME401_Radio.h"
#include "ME401_PID_IR.h"
#include "pathoptimization.h"
#include "RobotsOnTheField.h"
#include "MotorControl.h"
#include "StateMachine.h"

enum States{
  UNKNOWN = 0;
  BALL_SEARCH = 1;
  GO_TO_BALL = 2;
  CORNER_SEARCH = 3;
  GO_TO_CORNER = 4;
  AVOID = 5;
}

#define MY_ROBOT_ID 6


void setup() {
  Serial.begin(115200);
  setupMotors(30,31);       //setup motor pins
  ME401_Radio_initialize(); // Initialize the RFM69HCW radio
  // Initialize the PID and IR interrupts
  // TODO: Change the kp, ki, kd in the ME491_PID_IR.h file to match your new tunings
  //       that you did after installing the sensor on your robot
  setupPIDandIR();

  
}

void loop() {

  Serial.print("millis:");
  Serial.println(millis());



 
//  // Simple example of looking for the corner beacon
//  if (readIRFrequency() == CORNER)
//  {
//    Serial.println("I see the corner");
//  }
//  else
//  {
//    Serial.print("Can't see the corner:");
//    Serial.println(frequency);
//  }

  

  // Simple example of reading the robot and ball positions from the radio
  updateRobotPoseAndBallPositions();
  RobotPose robot = getRobotPose(MY_ROBOT_ID);
  if (robot.valid == true)
  {
    Serial.println("The camera can see my robot");
    printRobotPose(robot);
  }

  BallPosition ballPos[20];

  toTheFront(robotPoses);      //Sorts our bot to the front of the list

  int numBalls = getBallPositions(ballPos);
  Serial.print("NUM BALLS: ");
  Serial.println(numBalls);
  printBallPositions(numBalls, ballPositions);




  BallPosition targetBall;               //Closest ball which we will go to
  targetBall = findNextBall(robotPoses, ballPos); //Closest ball which we will go to

  angleTo(robot,&targetBall);  //finds angle to turn to be pointed at target ball
  testingAngle(targetBall);
  Serial.print("Angle: ");
  Serial.println(targetBall.angleTo);


  determineTurn(targetBall);
  
  delay(10);
}






