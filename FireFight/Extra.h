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
			setLed(GREEN);
			break;
		case PAN_SENSOR:
			initPanTime = millis();
			break;
		case EXPLORE:
			break;
		case FLAME:
			setLed(FLASH);
			break;
	}
}

void setLed(Color newState){
	ledState = newState;
	switch(ledState){
		case OFF:
			ledValues.b = 0; ledValues.r = 0; ledValues.g = 0;
			break;
		case PURPLE:
			ledValues.b = 30; ledValues.r = 30; ledValues.g = 0;
			break;
		case GREEN:
			ledValues.b = 0; ledValues.r = 0; ledValues.g = 40;
			break;
		case FLASH:
			ledValues.b = 0; ledValues.r = 50; ledValues.g = 0;
	}
	if(ledState != FLASH){
		for(uint8_t i = 0; i < LEDNUM; i++){
			LED.set_crgb_at(i, ledValues);
		}
		LED.sync();
	}
}

void updateLed(){
	if(ledState == FLASH) if(millis() - ledTimer > 50){
		cRGB nullValues;
		nullValues.b = 0; nullValues.r = 0; nullValues.g = 0;
		for(uint8_t i = 0; i < LEDNUM; i++){
			LED.set_crgb_at(i, i%2==ledPhase? ledValues : nullValues);
		}
		LED.sync();
		ledPhase = !ledPhase;
		ledTimer = millis();
	}
}