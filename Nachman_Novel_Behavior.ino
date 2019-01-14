// Created Nick Livingston 2017
// Modified Nachman Kaul-Seidman 2019

// PDS version without any use of Servo shields.
// Meant for use with Uno, or with TinyDuino
#include "sensors.h"
#include <Servo.h>


Servo left_servo;
Servo right_servo;  // create servo object to control a servo
// twelve servo objects can be created on most boards


//*************************************************** Function Declarations ***********************************************************//
//Behavior Primitive Functions
void avoid();
void motor_stop();
void BehaveLikeNachman();
void ProportionalCruise(DistanceThreshold);
void drive(float left, float right, float delay_seconds); //Motor Control Function

//*************************************************** Global Constant Declarations ****************************************************//
const int FRONT_BUMP = 15;
const int BACK_BUMP = 14;
const int LEFT_PHOTO = 1;
const int RIGHT_PHOTO = 0;
const int LEFT_IR = 3;//Cannot use ports 4, or 5 because they are dedicated to SDA and SCL, which is used for stack communications.
const int RIGHT_IR = 2;
const int LEFT_MOTOR = 6;
const int RIGHT_MOTOR = 9;
const int SERVO_MID = 90;
const int SERVO_RANGE = 90;


//*************************************************** Function Definitions ****************************************************//
void setup(){
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  left_servo.attach(LEFT_MOTOR);
  right_servo.attach(RIGHT_MOTOR);  // attaches the servo on pin RIGHT_MOTOR to the servo object

  pinMode(FRONT_BUMP, INPUT_PULLUP);
  pinMode(BACK_BUMP, INPUT_PULLUP);
  pinMode(LEFT_PHOTO, INPUT);
  pinMode(RIGHT_PHOTO, INPUT);
  pinMode(LEFT_IR, INPUT);
  pinMode(RIGHT_IR, INPUT);
 
  //digitalWrite(BACK_BUMP, LOW);
}
/******************************************************/
void loop() 
{
BehaveLikeNachman();
}
/******************************************************/
void read_analog(){
  left_photo_value    = 0;
  right_photo_value   = 0;
  left_ir_value       = 0;
  right_ir_value      = 0;
  for(int i = 0; i < 10; i++){
    left_photo_value    += (analogRead(LEFT_PHOTO));
    right_photo_value   += (analogRead(RIGHT_PHOTO));
    left_ir_value       += analogRead(LEFT_IR);
    right_ir_value      += analogRead(RIGHT_IR);
  }
  left_photo_value  /= 10;
  right_photo_value /= 10;
  //right_photo_value -= photo_offset;
  left_ir_value     /= 10;
  right_ir_value    /= 10;
}

/******************************************************/
//int check_avoid_conditions(){
//  
//  Serial.print("check_avoid_conditions().... ");
//  Serial.print(left_ir_value);
//  Serial.print(" : ");
// Serial.println(right_ir_value);
//  if(left_ir_value >= 500 || right_ir_value >= 500){
//    return true;
//  }else{
//   return false;
//  }
//}

/******************************************************/
void BehaveLikeNachman () { //
    int NumberofSweeps = 5; //
    int Increment =-5;      //
    int modifier = 1;       //
    int N = 100;            //
    for(int a = 0; a < Numberofsweeps; a++) {
        for(int i = 0; i < 5; i++){
          ProportionalCruise(N);
          avoid();
        }
        N = N + Increment;
    }
}

/******************************************************/

void ProportionalCruise(DistanceThreshold){
  left_ir_value = analogRead(LEFT_IR);
  right_ir_value = analogRead(RIGHT_IR);
  int center_ir_value = (left_ir_value + right_ir_value) / 2;
  
    while(center_ir_value < DistanceThreshold) {
      float speed = (1/IR Value) * scale;
      drive(speed, speed, 0.2);
      int center_ir_value = (left_ir_value + right_ir_value) / 2;
      
      
    }
}

/******************************************************/

void avoid(){
  if(left_ir_value >= 500){
    drive(0.75, -0.75, 0.20);
  }
  
  else if(right_ir_value >= 500){
    drive(-0.75, 0.5, 0.20);
  }
}

/******************************************************/

void motor_stop(){
  drive(0.0, 0.0, 0.25);
}
/******************************************************/

void drive(float left, float right, float delay_seconds){
  
  int left_speed       = SERVO_MID + (SERVO_RANGE * left);
  int right_speed      = SERVO_MID - (SERVO_RANGE * right);
  delay_seconds *= 1000;
  /*Serial.print(left_speed);
  Serial.print(" : ");
  Serial.println(right_speed);
 */
  left_servo.write(left_speed);
  right_servo.write(right_speed);
  delay(delay_seconds);

}
