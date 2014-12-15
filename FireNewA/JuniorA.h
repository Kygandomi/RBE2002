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
#define flameSensor A1
#define startButton 37
#define cliffSensor A5

#define LB 0
#define LF 1
#define MF 2 // middle front sensor
#define RF 3
#define RB 4

#define leftMPin 10
#define rightMPin 11
#define panPin 9 
#define tiltPin 8
#define gasPin 7
#define K 0.5

#define MIN_POWER 20

#define FAR_THRESH 30
#define FRONT_THRESH 13
#define NEAR_THRESH 10

#define ENCODER_TARGET 310

Servo leftM, rightM, pan, tilt, gas;
Encoder rightEnc(2, A0);
Encoder leftEnc(18, 19);

typedef enum State {
	FORWARD,
	TURN,
	REROUTE,
	EXPLORE,
	FLAME,
	PUT_OUT_FLAME,
	PAN_SENSOR,
	STOP,
	BACKUP
};
State nextState, robotState;

boolean trackingLeft;
boolean checkOpeningFirst = false;
boolean isFirstDetect = false;
boolean isFirstOpen = true;

boolean isFlameFound = false;
boolean flameDetectedOnce = true;
boolean flameExists = false;
float heading;

float initDist;
float finalDist;
float endDist;
float initEncAverage; 
int encDiff;
int encDetect;
int turnTicks;
int accumError = 0;

int highestReading; 
int highestEncAverage;
unsigned long initPanTime;
unsigned long initGasTime;
int flameStatus[3] = {0, 180, 180}; 

void startTurn(boolean turnLeft);
void startTurnOpening(boolean turnLeft);
void zeroEncoders();
void pingAll();
void collectIMUData();
void getInitDist();
void getFinalDist();
void setPrevPing();
void checkInitDist();
void setFlameServo();
int getEncAverage();

void ServoSetup(){
	leftM.attach(leftMPin);
	rightM.attach(rightMPin);
	pan.attach(panPin);
	tilt.attach(tiltPin);
	gas.attach(gasPin, 1000, 2000);
}

void drive(int x, int y){
	x = (x>100)?100:(x<-100)?-100:x;
	y = (y>100)?100:(y<-100)?-100:y;

	if(x>0 && x<MIN_POWER)
		x = MIN_POWER;
	if(x<0 && x>-MIN_POWER)
		x = -MIN_POWER;
	if(y<0 && y>-MIN_POWER)
		y = -MIN_POWER;
	if(y>0 && y<MIN_POWER)
		y = MIN_POWER;


	int a = map(x, -100, 100, 1000, 2000);
	int b = map(y, -100, 100, 2000, 1000);

	leftM.writeMicroseconds(a);
	rightM.writeMicroseconds(b);
}

void initialReadings(){
	long initTime = millis();
	while(millis() - initTime < 3000){
		pingAll();
		collectIMUData();
	}
}

void goTo(State s){
	robotState = s;
	switch(s){
		case FORWARD:
			flameDetectedOnce = true;
			setFlameServo();
			getInitDist();
			zeroEncoders();
			break;
		case TURN:
			zeroEncoders();
			break;
		case BACKUP:
			break;
		case PUT_OUT_FLAME:
			initGasTime = millis();
			break;		
		case REROUTE:
			break;
		case STOP:
			break;
		case PAN_SENSOR:
			initPanTime = millis();
			Serial.print("initPanTime: ");
			Serial.println(initPanTime);
			break;
		case EXPLORE:
			break;
		case FLAME:
			break;
	}
}

void then(State s){
	nextState = s;
}
