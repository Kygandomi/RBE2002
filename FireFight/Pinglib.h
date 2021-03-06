//Pinglib.h
/* This example code was taken from the NewPing library examples */

#define SONAR_NUM     5 // Number of sensors.
#define MAX_DISTANCE  300 // Maximum distance (in cm) to ping.
#define PING_INTERVAL 50 // Milliseconds between sensor pings (29ms is about the min to avoid cross-sensor echo).

unsigned long pingTimer[SONAR_NUM]; // Holds the times when the next ping should happen for each sensor.
unsigned int cm[SONAR_NUM];         // Where the ping distances are stored.   
uint8_t currentSensor = 0;          // Keeps track of which sensor is active.
float prevLB = 6;
float prevRB = 6;

NewPing sonar[SONAR_NUM] = { // Sensor object array.
	NewPing(lBackI, lBackO, MAX_DISTANCE),
	NewPing(lFrontI, lFrontO, MAX_DISTANCE),
	NewPing(mFrontI, mFrontO, MAX_DISTANCE), //added to accommodate the 5th sensor (front middle)
	NewPing(rFrontI, rFrontO, MAX_DISTANCE), 
	NewPing(rBackI, rBackO, MAX_DISTANCE)
	
};

void echoCheck(){ // If ping received, set the sensor distance to array.
	if (sonar[currentSensor].check_timer())
		cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}

void pingingSensors(int x){
	if (millis() >= pingTimer[x]) {         // Is it this sensor's time to ping?
		pingTimer[x] += PING_INTERVAL * SONAR_NUM;  // Set next time this sensor will be pinged.
		sonar[currentSensor].timer_stop();          // Make sure previous timer is canceled before starting a new ping (insurance).
		currentSensor = x;                          // Sensor being accessed.
		cm[currentSensor] = MAX_DISTANCE;                      // Make distance zero in case there's no ping echo for this sensor.
		sonar[currentSensor].ping_timer(echoCheck); // Do the ping (processing continues, interrupt will call echoCheck to look for echo).
	}
}

void PingSetup(){
	pingTimer[0] = millis() + 75;           // First ping starts at 75ms, gives time for the Arduino to chill before starting.
	for (uint8_t i = 1; i < SONAR_NUM; i++)
		pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;
}