void startTurnOpening(){ 
	float error = asin((endDist - initDist) / initDistanceTraveled());
	float errTicks = DEG_TICKS * ToDeg(error);
	if(initDist > FAR_THRESH)
		errTicks = 0;

	turnTicks = trackingLeft? -ENCODER_TARGET : ENCODER_TARGET;
	turnTicks += trackingLeft? errTicks : -errTicks;
}

void startTurn(){
	getFinalDist();

	float error = asin((finalDist - initDist) / distanceTraveled());
	float errTicks = DEG_TICKS * ToDeg(error);
	if(initDist > FAR_THRESH)
		errTicks = 0;

	turnTicks = trackingLeft? ENCODER_TARGET : -ENCODER_TARGET;
	turnTicks += trackingLeft? -errTicks : errTicks;

	accumError = 0;
}

bool completeTurn(){
	int leftPos = leftEnc.read(), rightPos = rightEnc.read();

	if(abs(leftPos - turnTicks) < 10 && abs(rightPos + turnTicks) < 10){
		isOpening = false;
		encDiff = 0;
		return true;
	}

	float speed = turnTicks > 0? 1.5 : -1.5;

	int leftSpeed = speed * (abs(turnTicks) - abs(leftPos));
	int rightSpeed = -speed * (abs(turnTicks) - abs(rightPos));

	drive (leftSpeed, rightSpeed);
	return false;
}

bool driveBackwards(){
	int encError = leftEnc.read() - rightEnc.read();
	if(getEncAvg() - initBackUpEncAverage < -80)
		return true;

	drive(-50 - K*encError, -50 + K*encError);
	return false;
}

bool driveStraight(){
	if(isFlameFound && getSideDist() < 50)
		return false;

	int sonarError = cm[LF] - cm[RF]; 
	if(abs(sonarError) > 10)
		sonarError = 0;
	sonarError *= 2;
	
	if(cm[RB] > prevRB)
		accumError += -30;
	else if(cm[RB] < prevRB)
		accumError += 30;
	if(cm[LB] > prevLB)
		accumError += 30;
	else if(cm[LB] < prevLB)
		accumError += -30;

	int encError = leftEnc.read() - rightEnc.read();
	int totalError = encError + accumError;

	drive(50 - K * totalError - sonarError, 50 + K * totalError + sonarError);
	return true;
}