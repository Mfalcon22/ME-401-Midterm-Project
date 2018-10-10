#ifndef _PATHOPTIMIZATION_H
#define _PATHOPTIMIZATION_H


#include <stdio.h>
#include <math.h>
#include "ME401_Radio.h"


void distanceTo(RobotPose us, BallPosition target);
void angleTo(RobotPose us, BallPosition target);
double dotProd(int x1, int y1, int x2, int y2);


void distanceTo(RobotPose us, BallPosition arr[])
{
  for(int i = 0; i < NUM_BALLS ; i++)
  {
  double b = pow((arr[i].y - us.y), 2);
  double c = pow((arr[i].x - us.x), 2);
  arr[i].distanceTo = (sqrt(b + c));
  }  
}

void angleTo(RobotPose us, BallPosition arr[])
{

  int usX = tan(us.theta);
  int usY = 1;
  double usMag = sqrt(usX^2+1);
  for(int i = 0; i < NUM_BALLS ; i++)
  {
    //unit vectors towards the ball
  double unitX = arr[i].x/arr[i].distanceTo;
  double unitY = arr[i].y/arr[i].distanceTo;

    
  arr[i].angleTo = acos(dotProd(usX,usY,unitX,unitY)/(arr[i].distanceTo * usMag));
  }
}

double dotProd(int x1, int y1, int x2, int y2)
{
  return (x1*x2)+(y1*y2);
}

int comparator(double* a, double* b)
{
  int temp = 0;
  if(*a<*b)
    temp = -1;
  else if(*a>*b)
    temp = 1;

  return temp;
  
}



#endif





