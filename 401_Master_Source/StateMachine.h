#ifndef _STATEMACHINE_H
#define _STATEMACHINE_H
#include "pathoptimization.h"
#include "MotorControl.h"


enum StateMachine{
  UNKNOWN = 0,
  BALL_SEARCH =1,
  GO_TO_BALL = 2,
  CORNER_SEARCH = 3,
  GO_TO_CORNER = 4,
  AVOID = 5,
};


void STATE_SEARCH_FOR_BALL();
void STATE_GO_TO_BALL(BallPosition target);
void STATE_SEARCH_FOR_CORNER();
void STATE_GO_TO_CORNER(int x, int y, int R);
void STATE_AVOID();

StateMachine state = BALL_SEARCH;
BallPosition ballPos[20];
BallPosition targetBall;               //Closest ball which we will go to



void STATE_SEARCH_FOR_BALL()
{
  targetBall = findNextBall(robotPoses, ballPos); //Closest ball which we will go to
  angleTo(robotPoses[0],&targetBall);  //finds angle to turn to be pointed at target ball
  state = GO_TO_BALL;
}

void STATE_GO_TO_BALL()
{
  determineTurn (targetBall);
}




































#endif
