#ifndef _PATHOPTIMIZATION_H
#define _PATHOPTIMIZATION_H


#include <stdio.h>
#include <math.h>
#include "ME401_Radio.h"


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

void AngleTo(RobotPose us, BallPosition arr[])
{
  for(int i = 0; i < NUM_BALLS ; i++)
  {
  double unitX = arr[i].x/arr[i].distanceTo;
  double unitY = arr[i].y/arr[i].distanceTo;
  
  arr[i].angleTo = acos(dotProd(us.x, us.y,unitX,unitY));
  }
}

double dotProd(int x1, int y1, int x2, int y2)
{
  return (x1*x2)+(y1*y2)o;
}



#endif





