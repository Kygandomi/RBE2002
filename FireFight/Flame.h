/* Written by Katie Gandomi, Alexander O'Brien, Yu-sen Wu, Shao Zhou */

bool checkFlameSensor(){
	//return true if there is a flame, false otherwise
	//should be called when the robot is in FORWARD state
	if(flameDetectedOnce){
		isFlameFound = analogRead(flameSensor) < FLAME_THRESH;
		if(isFlameFound){
			flameDetectedOnce = false;
			setLed(FLASH);
			return true;
		} 
	}
	return false;
}

int limit(int value){ 
	//limit proportional control values to the range 0-180 to prevent overdriving
	if(value > 180)
		return 180;
	else if(value < 0)
		return 0;
	else
		return value;
}

void setTarget(int target){
	//p control for the air actuator
	int error = analogRead(A11) - target;
	int value = limit(90 - error * 0.2);
	gas.write(value);
}

bool putOutFlame(){ 
	//put out the fire by releasing a stream of air for 1 second
	//return true at the end of the 1s period
	if(millis() - initGasTime < 1000)
		setTarget(770); // potentiometer value to turn on the air
	else if(millis() - initGasTime < 2000)
		setTarget(350); // potentiometer value to turn off the air
	else
		return true;
	return false;
}

bool findFlame(){ 
	//scan by traversing in a matris-lie pattern for the flame 

	// values to write to the pan servo (which moves in X direction)
	// and tilt servo (which moves in Y direction)
	const int minX = 30;
	const int minY = 60;
	const int maxX = 120;
	const int maxY = 130;

	static int finalX;
	static int finalY;
	static int bestReading = 1023;

	static unsigned long lastCallTime;
	static int posX = minX;
	static int posY = minY;
	//scan each cell for 70 ms
	if ((millis() - lastCallTime) > 70){
		lastCallTime = millis();
		if (posX >= maxX){
			posX = minX;
			delay(100); //give the pan servo enough time to go back to the starting position
			//increment servo PWM value to move from cell to cell
			posY += 6;
		}

		int tempReading = (analogRead(A1));
		// memorize the location of the flame
		if (tempReading < bestReading){
			bestReading = tempReading;
			finalX = posX;
			finalY = posY;
		}

		if(posY >= maxY){ //when the scanning procedure is complete
			posY = maxY;
			pan.write(finalX);
			tilt.write(finalY+5); //offset for the nozzle
			delay(1000); //ensure enough travel time
			return true;
		}
		// increment servo PWM values to move from cell to cell
		tilt.write(posY);
		posX += 3;
		pan.write(posX);
		return false;
	}
}

void setFlameServo(){ //switch direction based on which wall is being followed
	tilt.write(90);
	pan.write(trackingLeft? 140 : 30);
}

bool checkStopFindFlame(){
	//called if there is an obstacle in front of the robot
	// return true if there is a flame, false otherwise
	drive(0,0);
	int lowestVal = analogRead(A1) + 100;
	int lowestTilt = 40;
	int lowestPan = 65;
	// slowly iterate the loop so that servo have sufficient time to move from position to position
	for(float i = 25; i < 135; i+= .003){
		pan.write(i);
		if(analogRead(flameSensor) <= lowestVal){
			lowestPan = i; 
			lowestVal = analogRead(flameSensor);
			if(lowestVal < FLAME_THRESH)
				flameExists = true;
		}
	}
	return flameExists;
}