/* CONSTANT DEFINITIONS */

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

#define LB 0
#define LF 1
#define MF 2 // middle front sensor
#define RF 3
#define RB 4

#define MIN_POWER 20
#define K 0.5

#define FAR_THRESH 30
#define FRONT_THRESH 13
#define NEAR_THRESH 10

#define ENCODER_TARGET 310
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
	REROUTE,
	EXPLORE,
	FLAME,
	PUT_OUT_FLAME,
	PAN_SENSOR,
	STOP,
	BACKUP
};
State robotState;

/* EXTRA */
long ledTimer;
bool ledPhase;
typedef enum{
	OFF, PURPLE, GREEN, FLASH
} Color;
Color ledState;
cRGB ledValues;

void initialReadings();
void checkCliff();
void goTo(State s);
void setLed(Color newState);
void updateLed();

/* PING */
bool trackingLeft;
bool isOpening = false;
bool isFirstDetect = false;
bool isFirstOpen = true;
float initDist;
float finalDist;
float endDist;

void checkStop();
void checkInitDist();
void checkForOpening();
void checkSafety();
void setDirection();
void getInitDist();
void getFinalDist();
void pingAll();
void setCurrPing();
void setPrevPing();

/* IMU */
float heading =0;
int xDis;
int yDis;

void collectIMUData();
void sov();
void VectorSetup();

/* ENCODERS */
float initEncAverage; 
int encDiff;
int encDetect;
int turnTicks;
int accumError = 0;
int initBackUpEncAverage;

void zeroEncoders();
void EncoderSetup();
double distanceTraveled();
double initDistanceTraveled();

/* FLAME */
bool isFlameFound = false;
bool flameDetectedOnce = true;
bool flameExists = false;
int highestReading; 
int highestEncAverage;
unsigned long initPanTime;
unsigned long initGasTime;
int flameStatus[3] = {0, 180, 180}; 

void checkFlameSensor();
int limit(int value);
void setTarget(int target);
void putOutFlame();
bool findFlame();
void checkFlameFront();
void setFlameServo();
void checkStopFindFlame();

/* SERVOS */
void ServoSetup();
void drive(int x, int y);

/* NAVIGATION */
void startTurnOpening();
void startTurn();
void completeTurn();
void driveBackwards();
void driveStraight();