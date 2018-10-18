#ifndef _MOTORCONTROL_H
#define _MOTORCONTROL_H
#include <Servo.h>
Servo myservo1;  // create servo object to control a servo
Servo myservo2;

void stopmotors(int stoptime);
void turn_right(int angle);
void turn_left(int angle);
void GoToBall(int distance);
void determineTurn(BallPosition target);
void driveTest();
void setupMotors(int motor1, int motor2);
void testingAngle(BallPosition target);

void driveTest()
{
    Serial.println("Turning Right");
    turn_right(45);
    stopmotors(5000);
    Serial.println("Turning Left");
    turn_left(45);
    stopmotors(5000);
    Serial.println("Driving to Ball");
    GoToBall(20);
    stopmotors(5000);
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
    int RightTurn = 1450; 
    myservo1.writeMicroseconds(RightTurn);           
    myservo2.writeMicroseconds(RightTurn);
    int turn_time=50*angle;
    delay(turn_time);
  } 
void turn_left(int angle){
    int LeftTurn= 1550;
    myservo1.writeMicroseconds(LeftTurn);           
    myservo2.writeMicroseconds(LeftTurn);
    int turn_time=50*angle;
    delay(turn_time);
  }
void GoToBall(int distance){
    myservo1.writeMicroseconds(1300);           
    myservo2.writeMicroseconds(1700);
    int turn_time=100*distance;
    //delay(turn_time);
  }
  
void determineTurn(BallPosition target)
{
  Serial.print("Angle: ");
  Serial.println(target.angleTo);
  Serial.print("Distance: ");
  Serial.println(target.distanceTo);
  
	  //while (target.angleTo != 0)
   //{
  
   if (target.angleTo < 0) {
    Serial.println("turning right");
    turn_right(target.angleTo);    
   }

   else if (target.angleTo > 0) {
    Serial.println("turning left");
    turn_left(target.angleTo);
   }
   
   else /*(target.angleTo = 0)*/ {
    Serial.println("Going to ball");
    GoToBall(target.distanceTo);
   }
  // }
}

void testingAngle(BallPosition target)
{
  int angle = 0;
  if(Serial.available() > 0)
  {
    angle = Serial.parseInt();
    target.angleTo = angle;
  }
}
  
 
  
  #endif
