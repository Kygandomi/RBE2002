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

#define FAR_THRESH 50
#define FRONT_THRESH 20
#define NEAR_THRESH 10

Servo leftM, rightM, pan, tilt, gas;

Encoder rightEnc(2, A0);
Encoder leftEnc(18, 19);

typedef enum State {
	FORWARD_TIMED,
	FORWARD,
	TURN,
	FLAME
};

State robotState = FORWARD;

boolean trackingLeft;
float targetHeading;
float heading;
long inTime;

void startTurn(boolean turnLeft);
void zeroEncoders();

void goTo(State s){
	switch(s){
		case FORWARD_TIMED:
			zeroEncoders();
			inTime = millis();
			robotState = FORWARD_TIMED;
			break;
		case FORWARD:
			zeroEncoders();
			robotState = FORWARD;
			break;
		case TURN:
			robotState = TURN;
			break;
		case FLAME:
			robotState = FLAME;
			break;
		default:
			break;
	}
}
