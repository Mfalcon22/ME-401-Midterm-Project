#ifndef _PATHOPTIMIZATION_H
#define _PATHOPTIMIZATION_H


#include <stdio.h>
#include <math.h>
#include "ME401_Radio.h"



void distanceTo(RobotPose us, BallPosition arr[]);
void angleTo(RobotPose us, BallPosition target);
double dotProd(int x1, int y1, int x2, int y2);
int comparator(const void *a, const void *b);
BallPosition findNextBall(RobotPose robotPoses[], BallPosition ballPos[]);



void distanceTo(RobotPose us, BallPosition arr[])

void DistanceTo(RobotPose us, BallPosition target);
void AngleTo(RobotPose us, BallPosition target);
double dotProd(int x1, int y1, int x2, int y2);


void DistanceTo(RobotPose us, BallPosition arr[])

{
  for(int i = 0; i < NUM_BALLS ; i++)
  {
  double b = pow((arr[i].y - us.y), 2);
  double c = pow((arr[i].x - us.x), 2);
  arr[i].distanceTo = (sqrt(b + c));
  }  
}

void angleTo(RobotPose us, BallPosition target)
{

  int usX = tan((us.theta));
  int usY = 1;
  double usMag = sqrt(usX^2+1);
  double angle = 0;
  //for(int i = 0; i < NUM_BALLS ; i++)
  //{
    //unit vectors towards the ball
  double unitX = target.x/target.distanceTo;
  double unitY = target.y/target.distanceTo;


  angle = acos(dotProd(usX,usY,unitX,unitY)/(target.distanceTo * usMag));

  if(target.x > us.x)
  target.angleTo = angle;
  else
  target.angleTo = -angle;
  //}

    
  

double dotProd(int x1, int y1, int x2, int y2)
{
  return (x1*x2)+(y1*y2);
}

int comparator(const void *a, const void *b)
{
  int l = ((BallPosition *)a)->distanceTo;
  int r = ((BallPosition *)b)->distanceTo;
  return (l - r);
}

/*
 This functions determines the linear distance from us to every ball on the field
 That distance is stored in the BallPosition struct for each ball
 The array of ball positions is sorted
 The array is iterated through and the closed ball that is not behind or to the side of us (y coordinate for the ball < our y coordinate)
 The BallPosition object of the closest ball is returned
 */
 
BallPosition findNextBall(RobotPose robotPoses[], BallPosition ballPos[])
{

  distanceTo(robotPoses[0], ballPos);  //determines the distance from us to all of the balls 
  //angleTo(robotPoses[0], ballPos);              //determines the angle from us to the ball clockwise
  qsort((void*)ballPos,NUM_BALLS,sizeof(BallPosition),comparator);    //sorts the balls based on distance from us

  for(int i = 0; i<NUM_BALLS; i++)
  {
    if(ballPos[i].y > robotPoses[0].y)
      return ballPos[i];
  }
}









#endif





