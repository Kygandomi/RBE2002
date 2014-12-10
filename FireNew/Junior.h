#include <Servo.h>
#include <Encoder.h>
#include <NewPing.h>

#define lFrontI 12 //left front 
#define lFrontO 13 
#define lBackI 28 //left back 
#define lBackO 29 
#define mFrontI 24//middle front
#define mFrontO 25
#define rBackI 26 //right back
#define rBackO 27
#define rFrontI 22//right front 
#define rFrontO 23 
#define startButton 37

#define LB 0
#define LF 1
#define MF 2 // middle front sensor
#define RF 3
#define RB 4

#define leftMPin 10
#define rightMPin 11
#define panPin 8 
#define tiltPin 9
#define gasPin 7
#define K -0.5 //constant for controlling left and rigth motors to go at the same speed

float x_displacement = 0;
float y_displacement = 0;

Servo leftM, rightM, pan, tilt, gas;

Encoder rightEnc(2, A11);
Encoder leftEnc(18, 19);

double angle = 0; 
boolean trackingLeft;
float initHeading;  
float targetHeading;

typedef enum State {
  FORWARD,
  TURN,
  FLAME
};

State robotState = FORWARD;
boolean goForward = false;
long inTime;

void startTurn(boolean turnLeft);



