#include <Servo.h>
#include <Encoder.h>
#include <NewPing.h>

#define lFrontI 24 //left front 
#define lFrontO 25 
#define lBackI 22 //left back 
#define lBackO 23 
#define rFrontI 28//right front 
#define rFrontO 29 
#define rBackI 26 //right back
#define rBackO 27
#define mFrontI //middle front
#define mFrontO

#define startButton 37

#define LB 0
#define LF 1
#define MF 2 // middle front sensor
#define RF 3
#define RB 4

#define leftMPin 11
#define rightMPin 10
#define panPin S7 
#define tiltPin S8
#define gasPin
#define K -.5 //constant for controlling left and rigth motors to go at the same speed

Servo leftM, rightM, pan, tilt, gas;

Encoder rightEnc(18, 19);
Encoder leftEnc(2, 20);

typedef enum State {
  ALIGN,
  FORWARD,
  SENSOR,
  FLAME,
  TURN,
  STOP
};

State robotState = ALIGN;

double angle = 0; 
boolean turnRight = true;
boolean flame = false;
boolean correctR = false; 