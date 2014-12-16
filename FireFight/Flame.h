#ifndef Flame_H
#define Flame_H
#define flameThreshold 800

void checkFlameSensor(){
	if(flameDetectedOnce){
	isFlameFound = analogRead(flameSensor) < flameThreshold;
		if(isFlameFound){
			flameDetectedOnce = false;
			goTo(FORWARD);
		} 
	}
}

int limit(int value){
	if(value > 180)
		return 180;
	else if(value < 0)
		return 0;
	else
		return value;
}

void setTarget(int target){
	int error = analogRead(A11) - target;
	int value = limit(90 - error * 0.2);
	gas.write(value);
}


void putOutFlame(){

	if(millis() - initGasTime < 1500){
		setTarget(770);
	}
	else if(millis() - initGasTime < 4000){
		setTarget(350);
	}
	else {
		goTo(STOP);
	}

}

bool findFlame(){

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
			posY += 8;
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
		posX += 4;
		pan.write(posX);
		return false;
	}
}

void checkFlameFront(){
	pan.write(80);
	if(analogRead(flameSensor) < flameThreshold){
		drive(0,0);
		goTo(FLAME);
	}

	if(millis() - initPanTime > 400){
		setFlameServo();
		startTurn();
	} 

}

void setFlameServo(){
	tilt.write(100);
	if(trackingLeft){
		//if we're tracking left, set sensor to face right
		pan.write(140);
	}

	else{
		//else we're tracking right, set sensor to face left
		pan.write(30);
	}
}
void checkStopFindFlame(){
	drive(0,0);
	int lowestVal = analogRead(A1) + 100;
	int lowestTilt = 40;
	int lowestPan = 65;

	for(float i = 25; i < 135; i+= .003){
		pan.write(i);
		if(analogRead(flameSensor) <= lowestVal){
			lowestPan = i; 
			lowestVal = analogRead(flameSensor);
			if(lowestVal < 800){
				flameExists = true;
			}
		}
	}
	
	if(flameExists){
		goTo(FLAME);
	}
	else{
		startTurn();
	}
}
//pan values for flame sensor
//right 135 
//front 80
//left 30

#endif