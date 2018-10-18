#include "ME401_Radio.h"
#include "ME401_PID_IR.h"
#include "pathoptimization.h"
#include "RobotsOnTheField.h"
#include "MotorControl.h"






void setup() {

  // Set up the serial port in case we want output or input
  Serial.begin(115200);

  //setup motors
  setupMotors(30,31);

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
  
  toTheFront(robotPoses);                //Sorts our bot to the front of the list

  int numBalls = getBallPositions(ballPos);
  Serial.print("NUM BALLS: ");
  Serial.println(numBalls);
  printBallPositions(numBalls, ballPositions);

  BallPosition targetBall;               //Closest ball which we will go to
  targetBall = findNextBall(robotPoses, ballPos);
  angleTo(robot,targetBall);  //finds angle to turn to be pointed at target ball
  testingAngle(targetBall);
  Serial.print("Angle: ");
  Serial.println(targetBall.angleTo);

  determineTurn(targetBall);
  
  delay(10);
}






