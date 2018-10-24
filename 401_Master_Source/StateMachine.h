#ifndef _STATEMACHINE_H
#define _STATEMACHINE_H

#include "MotorControl.h"
#include "pathoptimization.h"
#include "ME401_Radio.h"

int competition = 0;


enum StateMachine{
  UNKNOWN = 0,
  BALL_SEARCH =1,
  GO_TO_BALL = 2,
  GO_TO_CENTER = 3,
  SEARCH_FOR_CORNER = 4,
  GO_TO_CORNER = 5,
  AVOID = 6,
};


void STATE_SEARCH_FOR_BALL();
void STATE_GO_TO_BALL();
void STATE_SEARCH_FOR_CORNER();
void STATE_GO_TO_CORNER();
<<<<<<< HEAD
void STATE_GO_TO_CENTER();
void STATE_AVOID();
void STATE_STOP();



int leftSwitch = 10;
int rightSwitch = 7;
void limitSwitchSetUp();

=======
void STATE_AVOID();
void STATE_GO_TO_CENTER();
>>>>>>> parent of eb08429... still working on states

StateMachine state = BALL_SEARCH;
BallPosition ballPos[20];
BallPosition targetBall;               //Closest ball which we will go to


/* determines the distance from us to all of the balls to find the ball closest to us
 determines the angle from us to the ball closest to us
 changes state variable to GO_TO_BALL once that data is calculated and stored*/
void STATE_SEARCH_FOR_BALL()
{
  targetBall = findNextBall(robotPoses, ballPos); //Closest ball which we will go to
  angleTo(robotPoses[0],&targetBall);  //finds angle to turn to be pointed at target ball
  
  state = GO_TO_BALL;
}

/* takes the data calculated in SEARCH_FOR_BALL and navigates to the ball based on the angle from us to the ball
 * There are to 'modes' in this state
 * 1: when we demo we will pick up a single ball and then go to a corner
 * 2: for the 'competition' we can set when we want to go to the corner based on how many balls are still on the field*/
void STATE_GO_TO_BALL()
{
  determineTurn (targetBall);
  if(competition == 0)
    state = GO_TO_CENTER;
  else if(numBalls == 0)
    state = GO_TO_CENTER;
}

/*  creates a BallPosition object to store the distance and angle data for the center of the field
 *  once at the center the state variable is set to SEARCH_FOR_CORNER
 */
void STATE_GO_TO_CENTER()
{
 //determine distance and angle to the center
 //store that data in centerField
 distanceToTarget(robotPoses[0], &centerField);
 angleTo(robotPoses[0], &centerField);
 
 //go to the center
 determineTurn(centerField);

 state = SEARCH_FOR_CORNER;
  
}

void STATE_SEARCH_FOR_CORNER()
{

<<<<<<< HEAD
void STATE_GO_TO_CORNER()
{

  //determine distance and angle to the corner
  //store that data in corner
  distanceToTarget(robotPoses[0], &corner);
  angleTo(robotPoses[0], &corner);

  //go to the corner
  //while (digitalRead(leftSwitch) == LOW && digitalRead(rightSwitch) == LOW)
  //{
    determineTurn(corner);
  //}
  state = WAIT;

 //determine distance and angle to the corner
 //store that data in corner
 distanceToTarget(robotPoses[0], &corner);
 angleTo(robotPoses[0], &corner);
 
 //go to the corner
 while (digitalRead(leftSwitch) == LOW && digitalRead(rightSwitch) == LOW)
 {
 determineTurn(corner);
 }
 state = STOP;

}

void STATE_STOP()
{
=======
>>>>>>> parent of eb08429... still working on states
  
}




































#endif
