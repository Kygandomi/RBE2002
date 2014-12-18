/* Written by Katie Gandomi, Alexander O'Brien, Yu-sen Wu, Shao Zhou */

bool checkFlameSensor(){
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

int limit(int value){ //limit servo values to the range 0-180
	if(value > 180)
		return 180;
	else if(value < 0)
		return 0;
	else
		return value;
}

void setTarget(int target){ //p control for the air actuator
	int error = analogRead(A11) - target;
	int value = limit(90 - error * 0.2);
	gas.write(value);
}

bool putOutFlame(){ //put out the fire for 1 second
	if(millis() - initGasTime < 1000)
		setTarget(770);
	else if(millis() - initGasTime < 2000)
		setTarget(350);
	else
		return true;
	return false;
}

bool findFlame(){ //scan for the flame
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

	if ((millis() - lastCallTime) > 70){
		lastCallTime = millis();
		if (posX >= maxX){
			posX = minX;
			delay(100);
			posY += 6;
		}

		int tempReading = (analogRead(A1));

		if (tempReading < bestReading){
			bestReading = tempReading;
			finalX = posX;
			finalY = posY;
		}

		if(posY >= maxY){
			posY = maxY;
			pan.write(finalX);
			tilt.write(finalY+5);
			delay(1000);
			return true;
		}

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
	drive(0,0);
	int lowestVal = analogRead(A1) + 100;
	int lowestTilt = 40;
	int lowestPan = 65;

	for(float i = 25; i < 135; i+= .003){
		pan.write(i);
		if(analogRead(flameSensor) <= lowestVal){
			lowestPan = i; 
			lowestVal = analogRead(flameSensor);
			if(lowestVal < 800)
				flameExists = true;
		}
	}
	
	return flameExists;
}