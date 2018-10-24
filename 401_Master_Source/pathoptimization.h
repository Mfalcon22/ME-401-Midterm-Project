#ifndef _PATHOPTIMIZATION_H
#define _PATHOPTIMIZATION_H


#include <stdio.h>
#include <math.h>
#include "ME401_Radio.h"



void distanceTo(RobotPose us, BallPosition arr[]);
void angleTo(RobotPose us, BallPosition* target);
double dotProd(double x1, double y1, double x2, double y2);
int comparator(const void *a, const void *b);
BallPosition findNextBall(RobotPose robotPoses[], BallPosition ballPos[]);
void distanceToTarget(RobotPose us, BallPosition* target);
double dotProd(int x1, int y1, int x2, int y2);


void distanceTo(RobotPose us, BallPosition arr[])

{
  for(int i = 0; i < NUM_BALLS ; i++)
  {
  double b = pow((fabs(arr[i].y) - fabs(us.y)), 2);
  double c = pow((fabs(arr[i].x) - fabs(us.x)), 2);
  arr[i].distanceTo = (sqrt(b + c));
  }  
}

void distanceToTarget(RobotPose us, BallPosition* target)
{
  
  double b = pow((fabs(target->y) - fabs(us.y)), 2);
  double c = pow((fabs(target->x) - fabs(us.x)), 2);
  target->distanceTo = (sqrt(b + c)); 
}


void angleTo(RobotPose us, BallPosition* target)
{
<<<<<<< HEAD
  double ourAngle = (double)(us.theta)/1000.0;
  double usX = tan(ourAngle+(PI));
  double usY = 1;
//  double usMag = sqrt((pow(usX,2))+1);
  double targetX = target->x - usX;
  double targetY = target->y - usY;
  
=======

  int16_t usX = tan(((us.theta)/1000));
  int16_t usY = 1;
  double usMag = sqrt(usX^2+1);
>>>>>>> parent of 6f3feea... Fixed angleTo
  //for(int i = 0; i < NUM_BALLS ; i++)
  //{
    //unit vectors towards the ball
 // double unitX = target.x/target.distanceTo;
  //double unitY = target.y/target.distanceTo;

    
<<<<<<< HEAD
  //target->angleTo = acos((dotProd(usX,usY,targetX,targetY))/(target->distanceTo * usMag));
 
  target->angleTo = (atan2((double)(target->x - us.x), (double)(target->y - us.y)) + (double)us.theta/1000)*(180/PI);
=======
  target->angleTo = acos((dotProd(usX,usY,target->x,target->y))/(target->distanceTo * usMag));
>>>>>>> parent of 6f3feea... Fixed angleTo
  //}
}

double dotProd(double x1, double y1, double x2, double y2)
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

//  for(int i = 0; i<NUM_BALLS; i++)
//  {
//    if(ballPos[i].y > robotPoses[0].y)
//      return ballPos[i];
//  }
  return ballPos[0];
}









#endif





