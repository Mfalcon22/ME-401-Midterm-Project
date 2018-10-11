#ifndef _ROBOTSONTHEFIELD_H
#define _ROBOTSONTHEFIELD_H


#include <stdio.h>
#include <math.h>
#include "ME401_Radio.h"



void sortOurBot (RobotPose bots[])
{

  RobotPose temp = bots[0];
  for (int i=1; i < NUM_ROBOTS; i++)
  {
    
    if(bots[i].ID == MY_ROBOT_ID)
      {
        bots[0] = bots[i];
        bots[i] = temp;
      }  
  }

}


#endif
