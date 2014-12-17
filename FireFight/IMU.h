/* Written by Katie Gandomi, Alexander O'Brien, Yu-sen Wu, Shao Zhou */

void collectIMUData(){
	int interval = millis() - timer;
	if(interval > 19){ // Main loop runs at 50Hz
		G_Dt = interval / 1000.0; // Real time of loop run. We use this on the DCM algorithm (gyro integration time)
		timer = millis();

		Read_Gyro(); // This read gyro data
		Read_Accel(); // Read I2C accelerometer

		if(robotState == TURN) //only count gyro data when turning (very little drift!)
			heading += gyro_z * G_Dt * 0.07;
	}
}

void VectorSetup(){
	//set up the lcd and set all variables to 0
	lcd.begin(16, 2);
	lcd.setCursor(0, 0);
	xDis = 0;
	yDis = 0;
	heading = 0;
}

void sumOfVectors(){
	//get current displacement
	int linDiff = getEncAvg() / TICKS_CM;
	float currentAngDis = ToRad(heading);

	//get vector components
	xDis += linDiff * cos(currentAngDis);
	yDis += linDiff * sin(currentAngDis);
}