void startTurnOpening(){ 
	float error = asin((endDist - initDist) / initDistanceTraveled());
	float errTicks = 3.36 * ToDeg(error);
	if(initDist > FAR_THRESH){
		errTicks = 0;
	}

	turnTicks = trackingLeft? -ENCODER_TARGET : ENCODER_TARGET;
	turnTicks += trackingLeft? errTicks : -errTicks;

	goTo(TURN);
}

void startTurn(){
	getFinalDist();

	float error = asin((finalDist - initDist) / distanceTraveled());
	float errTicks = 3.36 * ToDeg(error);
	if(initDist > FAR_THRESH){
		errTicks = 0;
	}

	turnTicks = trackingLeft? ENCODER_TARGET : -ENCODER_TARGET;
	turnTicks += trackingLeft? -errTicks : errTicks;
	
	goTo(TURN); 
	accumError = 0;
}

void completeTurn(){
	int leftPos = leftEnc.read(), rightPos = rightEnc.read();

	if(abs(leftPos - turnTicks) < 10 && abs(rightPos + turnTicks) < 10){
		drive(0, 0);
		isOpening = false;
		encDiff = 0;
		isFirstOpen = true;
		goTo(FORWARD);
		return;
	}

	float speed = turnTicks > 0? 1.5 : -1.5;

	int leftSpeed = speed * (abs(turnTicks) - abs(leftPos));
	int rightSpeed = -speed * (abs(turnTicks) - abs(rightPos));

	/*int diffError = abs(leftPos) - abs(rightPos);
	drive(leftSpeed - K * diffError, rightSpeed + K * diffError);*/

	drive (leftSpeed, rightSpeed);
}

void driveBackwards(){
	int leftEncTick = leftEnc.read();
		int rightEncTick = rightEnc.read();
		int Eerror = leftEncTick - rightEncTick;
		int currentEncAverage = (leftEnc.read() + rightEnc.read())/2;
		if(currentEncAverage - initBackUpEncAverage < -80){
			drive(0, 0);
			goTo(REROUTE);
		}

	drive(-50 - K*Eerror, -50 + K*Eerror);
}

void driveStraight(){
	if(isFlameFound){
		if(trackingLeft){
			if(cm[RB] < 50){
				startTurn();
			}
		}
		else{
			if(cm[LB] < 50){
				startTurn();
			}
		}
	}
	int Rerror = cm[LF] - cm[RF]; 
		if(Rerror > 10 || Rerror < -10){
			Rerror = 0;
		}
		int leftEncTick = leftEnc.read();
		int rightEncTick = rightEnc.read();
		 int Kp = 2;
	
	if(trackingLeft){
			if (cm[LB] == prevLB  || cm[LB] > FAR_THRESH || prevLB > FAR_THRESH){
				accumError += 0;
			}
			else if(cm[LB] > prevLB){
				accumError += 20;
			}
			else if(cm[LB] < prevLB){
				accumError += -20;
			}
	}
	else {
			if(cm[RB] == prevRB || cm[RB] > FAR_THRESH || prevRB > FAR_THRESH){
				accumError += 0;
			}
			else if(cm[RB] > prevRB){
				accumError += -20;
			}
			else if(cm[RB] < prevRB){
				accumError += 20;
			}
	}

	int Eerror = leftEncTick - rightEncTick;
	int totError = Eerror + accumError;

	drive(70 - K*totError - Kp*Rerror, 70 + K*totError + Kp*Rerror);
}