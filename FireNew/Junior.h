#include <Servo.h>
#include <Encoder.h>
#include <NewPing.h>

#define lFrontI 6 //left front 
#define lFrontO 5 
#define lBackI 22 //left back 
#define lBackO 23 
#define rFrontI 28//right front 
#define rFrontO 29 
#define rBackI 26 //right back
#define rBackO 27
#define mFrontI 24//middle front
#define mFrontO 25
#define startButton 37

#define LB 0
#define LF 1
#define MF 2 // middle front sensor
#define RF 3
#define RB 4

#define leftMPin 11
#define rightMPin 10
#define panPin 7 
#define tiltPin 8
#define gasPin 
#define K -.5 //constant for controlling left and rigth motors to go at the same speed

Servo leftM, rightM, pan, tilt, gas;

Encoder rightEnc(2, 3);
Encoder leftEnc(18, 19);

double angle = 0; 
boolean trackingLeft;
float initHeading;  
float targetHeading;

typedef enum State {
  FORWARD,
  TURN,
};

State robotState = FORWARD;
boolean goForward = false;
long inTime;

void startTurn(boolean turnLeft);



