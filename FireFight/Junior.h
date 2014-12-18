//Junior.h
/* Written by Katie Gandomi, Alexander O'Brien, Yu-sen Wu, Shao Zhou */

/* PINS */
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
#define cliffSensor A5
#define LEDPIN A10
#define LEDNUM 6
#define leftMPin 10
#define rightMPin 11
#define panPin 9 
#define tiltPin 8
#define gasPin 7

/* SONAR COUNTER */
#define LB 0
#define LF 1
#define MF 2
#define RF 3
#define RB 4

/* MISCELLANEOUS TARGETS */
#define MIN_POWER 20
#define K 0.5
#define TICKS_CM 16.4
#define DEG_TICKS 3.36

#define FAR_THRESH 30
#define FRONT_THRESH 13
#define NEAR_THRESH 10

#define ENCODER_TARGET 305
#define FLAME_THRESH 800

/* OBJECTS */
Servo leftM, rightM, pan, tilt, gas;
Encoder rightEnc(2, A0);
Encoder leftEnc(18, 19);
LiquidCrystal lcd(40,41,42,43,44,45);
WS2812 LED(LEDNUM);

/* STATE ENUMERATION */
typedef enum State {
	FORWARD,
	TURN,
	FLAME,
	PUT_OUT_FLAME,
	PAN_SENSOR,
	STOP,
	BACKUP
};
State robotState;

/* LIGHT */
long ledTimer;
bool ledPhase;
typedef enum{
	OFF, PURPLE, GREEN, FLASH
} Color;
Color ledState;
cRGB ledValues;

bool checkCliff();
void setLed(Color);
void updateLed();

/* PING */
bool trackingLeft;
bool isOpening = false;
bool isFirstDetect = false;
float initDist;
float finalDist;
float endDist;

int getSideDist();
bool checkStop();
void checkForOpening();
void initialReadings();
void setDirection();
void getInitDist();
void getFinalDist();
void pingAll();

/* IMU */
float heading;
int xDis;
int yDis;

void collectIMUData();
void VectorSetup();
void sumOfVectors();

/* ENCODERS */
float initEncAverage; 
int encDiff;
int encDetect;
int turnTicks;
int accumError;
int initBackUpEncAverage;

void zeroEncoders();
void EncoderSetup();
int getEncAvg();
double distanceTraveled();
double initDistanceTraveled();

/* FLAME */
bool isFlameFound;
bool flameDetectedOnce = true;
bool flameExists;
int highestReading; 
int highestEncAverage;
unsigned long initPanTime;
unsigned long initGasTime;
int flameStatus[3] = {0, 180, 180}; 

bool checkFlameSensor();
int limit(int);
void setTarget(int);
bool putOutFlame();
bool findFlame();
void setFlameServo();
bool checkStopFindFlame();

/* SERVOS */
void ServoSetup();
void drive(int, int);

/* NAVIGATION */
void startTurnOpening();
void startTurn();
bool completeTurn();
bool driveBackwards();
bool driveStraight();

/* STATE CHANGE */
void goTo(State s){
	if(robotState == FORWARD)
		sumOfVectors();
	robotState = s;
	switch(s){
		case FORWARD:
			setFlameServo();
			getInitDist();
			zeroEncoders();
			break;
		case TURN:
			zeroEncoders();
			break;
		case PUT_OUT_FLAME:
			initGasTime = millis();
			break;
		case STOP:
			setLed(GREEN);
			break;
		case PAN_SENSOR:
			drive(0, 0);
			initPanTime = millis();
			break;
	}
}