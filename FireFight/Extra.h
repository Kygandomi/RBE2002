void initialReadings(){
	long initTime = millis();
	while(millis() - initTime < 3000){
		pingAll();
		collectIMUData();
	}
}

void checkCliff(){
	if(analogRead(cliffSensor) > 800){
		initBackUpEncAverage = (leftEnc.read() + rightEnc.read())/2;
		goTo(BACKUP);
	}
}

void goTo(State s){
	robotState = s;
	switch(s){
		case FORWARD:
			blockSOV = false;
			setFlameServo();
			getInitDist();
			zeroEncoders();
			break;
		case TURN:
			blockSOV = true;
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
			break;
		case EXPLORE:
			break;
		case FLAME:
			break;
	}
}