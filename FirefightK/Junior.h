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
#define startButton 37

#define RF 0
#define LF 1
#define LB 2
#define RB 3

#define leftMPin 11
#define rightMPin 10
#define K -.5

Servo leftM, rightM;
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

