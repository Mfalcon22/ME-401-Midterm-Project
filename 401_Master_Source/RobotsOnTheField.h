#ifndef _ROBOTSONTHEFIELD_H
#define _ROBOTSONTHEFIELD_H


#include <stdio.h>
#include <math.h>
#include "ME401_Radio.h"


void toTheFront (RobotPose bots[]);
int masterSort(BallPosition arr[], int counter);




void toTheFront (RobotPose bots[])
{

  RobotPose temp = bots[0];
  for (int i = 1; i < NUM_ROBOTS; i++)
  {

    if (bots[i].ID == MY_ROBOT_ID)
    {
      bots[0] = bots[i];
      bots[i] = temp;
    }
  }
}

int masterSort(BallPosition arr[], int counter)
{

  if (counter == NUM_BALLS)
    return 0;
  else {
    counter++;
    qsort((void*)arr[counter], NUM_BALLS, sizeof(BallPosition), comparator);
    masterSort(arr++, counter);
  }

}


#endif
