#include <Arduino.h>

#include "ME401_Radio.h"
#include "ME401_PID_IR.h"
#include "pathoptimization.h"
#include "RobotsOnTheField.h"
#include "MotorControl.h"
#include "StateMachine.h"
#include "FindCorner.h"
#include "collectingBalls.h"



#define MY_ROBOT_ID 6




void setup() {
  Serial.begin(115200);
  setupMotors(30, 31);      //setup motor pins
  ME401_Radio_initialize(); // Initialize the RFM69HCW radio
  setupPIDandIR();
  distanceIRSetup();
  centerField.x = 1235;
  centerField.y = 1235;


}




void loop() {

  Serial.print("millis:");
  Serial.println(millis());
  updateRobotPoseAndBallPositions();
  RobotPose robot = getRobotPose(MY_ROBOT_ID);
  if (robot.valid == true)
  {
    Serial.println("The camera can see my robot");
    printRobotPose(robot);
  }
  
  toTheFront(robotPoses);      //Sorts our bot to the front of the list

  int numBalls = getBallPositions(ballPos);
  Serial.print("NUM BALLS: ");
  Serial.println(numBalls);
  printBallPositions(numBalls, ballPositions);

  BallPosition targetBall;               //Closest ball which we will go to
  targetBall = findNextBall(robotPoses, ballPos); //Closest ball which we will go to
  angleTo(robot,&targetBall);  //finds angle to turn to be pointed at target ball
  
  Serial.print("Angle to ball: ");
  Serial.println(targetBall.angleTo);
  //Serial.print("Our Angle: ");
  //Serial.println((double)robotPoses[0].theta/1000);
  //determineTurn(targetBall);
  //findCorner();
   getDistance();  //IR distance sensor testing
  
 /*
    switch(state)
    {
  
      case UNKNOWN:
  
        break;
  
      case BALL_SEARCH:
        STATE_SEARCH_FOR_BALL();
        break;
  
      case GO_TO_BALL:
        STATE_GO_TO_BALL();
        break;
      
      case GO_TO_CENTER:
         STATE_GO_TO_CENTER();
         break;
          
      case SEARCH_FOR_CORNER:
        STATE_SEARCH_FOR_CORNER();
        break;
  
      case GO_TO_CORNER:
        STATE_GO_TO_CORNER();
        break;
  
      case AVOID:
  
        break;
        
      case WAIT:
      
        break;
    }
    */


  delay(10);
}






