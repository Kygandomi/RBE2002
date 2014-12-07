#define SONAR_NUM     5 // Number or sensors.
#define MAX_DISTANCE  250 // Maximum distance (in cm) to ping.
#define PING_INTERVAL 40 // Milliseconds between sensor pings (29ms is about the min to avoid cross-sensor echo).

unsigned long pingTimer[SONAR_NUM]; // Holds the times when the next ping should happen for each sensor.
unsigned int cm[SONAR_NUM];         // Where the ping distances are stored.
uint8_t currentSensor = 0;          // Keeps track of which sensor is active.

NewPing sonar[SONAR_NUM] = {     // Sensor object array.
	NewPing(lBackI, lBackO, MAX_DISTANCE),
	NewPing(lFrontI, lFrontO, MAX_DISTANCE),
	NewPing(mFrontI, mFrontO, MAX_DISTANCE), //added to accommodate the 5th sensor (front middle)
	NewPing(rFrontI, rFrontO, MAX_DISTANCE), 
	NewPing(rBackI, rBackO, MAX_DISTANCE)
	
};

void echoCheck() { // If ping received, set the sensor distance to array.
	if (sonar[currentSensor].check_timer())
		cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}

void pingingSensors(int x){
	if (millis() >= pingTimer[x]) {         // Is it this sensor's time to ping?
		pingTimer[x] += PING_INTERVAL * SONAR_NUM;  // Set next time this sensor will be pinged.
		/*if (x == 0 && currentSensor == SONAR_NUM - 1)
		 oneSensorCycle(); // Sensor ping cycle complete, do something with the results.*/
		sonar[currentSensor].timer_stop();          // Make sure previous timer is canceled before starting a new ping (insurance).
		currentSensor = x;                          // Sensor being accessed.
		cm[currentSensor] = 0;                      // Make distance zero in case there's no ping echo for this sensor.
		sonar[currentSensor].ping_timer(echoCheck); // Do the ping (processing continues, interrupt will call echoCheck to look for echo).
	}
}

void oneSensorCycle() { // Sensor ping cycle complete, do something with the results.
	for (uint8_t i = 0; i < SONAR_NUM; i++) {
		Serial.print(i);
		Serial.print("=");
		Serial.print(cm[i]);
		Serial.print("cm ");
	}
	Serial.println();
}

void PingSetup(){
	pingTimer[0] = millis() + 75;           // First ping starts at 75ms, gives time for the Arduino to chill before starting.
	for (uint8_t i = 1; i < SONAR_NUM; i++)
		pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;
}

void pingAll(){
	pingingSensors(0);
	pingingSensors(1);
	pingingSensors(2);
	pingingSensors(3);
	pingingSensors(4);
}