#ifndef _MOTORCONTROL_H
#define _MOTORCONTROL_H
#include <Servo.h>
Servo myservo1;  // create servo object to control a servo
Servo myservo2;

#define LEFT 8
#define RIGHT 8
#define pause 1000


void stopmotors(int stoptime);
void turn_right(int angle);
void turn_left(int angle);
void GoToBall(int distance);
void determineTurn(BallPosition target);
void driveTest();
void setupMotors(int motor1, int motor2);


void driveTest()
{
    Serial.println("Turning Right");
    turn_right(45);
    stopmotors(pause);
    Serial.println("Turning Left");
    turn_left(45);
    stopmotors(pause);
    Serial.println("Driving to Ball");
    GoToBall(20);
    stopmotors(pause);
}
void setupMotors(int motor1, int motor2)
{
	myservo1.attach(motor1);  // attaches the servo pin# the servo object
	myservo2.attach(motor2); // servo to other pin#
}
void stopmotors(int stoptime){
    myservo1.writeMicroseconds(1500);           
    myservo2.writeMicroseconds(1500);
    delay(stoptime);
  }
  
void turn_right(int angle){
    int RightTurn = 1550; 
    myservo1.writeMicroseconds(RightTurn);           
    myservo2.writeMicroseconds(RightTurn);
    int turn_time=RIGHT*fabs(angle);
    delay(turn_time);
  } 
void turn_left(int angle){
    int LeftTurn= 1450;
    myservo1.writeMicroseconds(LeftTurn);           
    myservo2.writeMicroseconds(LeftTurn);
    int turn_time=LEFT*fabs(angle);
    delay(turn_time);
  }
void GoToBall(int distance){
    myservo1.writeMicroseconds(1600);           
    myservo2.writeMicroseconds(1400);
    int turn_time=1*fabs(distance);
    //delay(turn_time);
  }
  
void determineTurn(BallPosition target)
{
  //Serial.print("Angle: ");
  //Serial.println(target.angleTo);
  Serial.print("Distance: ");
  Serial.println(target.distanceTo);
  
	  //while (target.angleTo != 0)
   //{
  
   if (target.angleTo > 5) {
    Serial.println("turning right");
    stopmotors(pause);
    turn_right(target.angleTo);   
    stopmotors(pause);
   }

   else if (target.angleTo < -5) {
    Serial.println("turning left");
    stopmotors(pause);
    turn_left(target.angleTo);
    stopmotors(pause);
   }
   
   else if (target.angleTo <= 5 && target.angleTo >= -5) {
    Serial.println("Going to ball");
    GoToBall(target.distanceTo);
    //stopmotors(2000);
   }
  // }

  
}


  
 
  
  #endif
