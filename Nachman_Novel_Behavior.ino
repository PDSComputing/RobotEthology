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
void avoid();             //takes IR readings and turn 90º to avoid obstacles
void motor_stop();        //stops motors
void BehaveLikeNachman(); //"explores" space by -------
void ProportionalCruise(DistanceThreshold); // drives towards obstacle, where speed is proportional to distance
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
void loop()   // the robot behaves like Nachman
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
void BehaveLikeNachman () { // Does whatever a Nachman can
    const int NumberofSweeps = 5; // Sets how many times the robot goes around the enclosure
    const int Increment =-5;      // Sets the increment by which each "loop path" is shorter than the last (must be set after Empirical Testing)
    const int modifier = 1;       // Scales the speed derived from IR value to motor (must be set after testing)
    int DistanceThreshold = 100;  // Sets the minimum distance which consitutes being "close" to an object (set after testing)
    for(int a = 0; a < Numberofsweeps; a++) { // Does Numbemberofsweeps many "sweeps" or "loops" around the enclosure
        for(int i = 0; i < 3; i++){           // for each sweep, it make 4 turns
          ProportionalCruise(DistanceThreshold); // Robot approaches obstacle with its speed proportional to its distance from obstacle
          avoid();                               // after ProportionalCruise terminates, Robot turns to side and restarts loop
        }
        DistanceThreshold = DistanceThreshold + Increment;  // Set the distance threshold lower each loop, so that the robot's
                                                            // "loop path" gets tighter until it has covered the entire enclosure
    }   
}

/******************************************************/

void ProportionalCruise(DistanceThreshold){     // drives the robot to approach an obstacle,  DistanceThreshold  representss  distance considered "close

  left_ir_value = analogRead(LEFT_IR);          // Reads IR sensor on left and right sides
  right_ir_value = analogRead(RIGHT_IR);        
  int center_ir_value = (left_ir_value + right_ir_value) / 2; // assumes that average between them represents a "middle" IR reading
  
    while(center_ir_value < DistanceThreshold) {  // while robot is not close to an obstacle
      float speed = (1/IR Value) * scale;         // speed is proportional to distance (and therefore inversly poportional to IR reading)
      drive(speed, speed, 0.2);                   // drive motors at appropriate speed
      left_ir_value = analogRead(LEFT_IR);        // takes IR readings in order to inform condition of While Loop
      right_ir_value = analogRead(RIGHT_IR);  
      int center_ir_value = (left_ir_value + right_ir_value) / 2;
      
      
    }
}

/******************************************************/

void avoid(){                                       // avoids nearby obstacles
  if(left_ir_value >= 500){                         // if object is close to left side
    drive(0.75, -0.75, 0.20);                       // turn right
  }
    
  else if(right_ir_value >= 500){                   // if object is close to right side
    drive(-0.75, 0.5, 0.20);                        // turn left
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
