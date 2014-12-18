//Navigation.h
/* Written by Katie Gandomi, Alexander O'Brien, Yu-sen Wu, Shao Zhou */

void startTurnOpening(){ 
	//error angle calculation for compensation
	float error = asin((endDist - initDist) / initDistanceTraveled()); 
	float errTicks = DEG_TICKS * ToDeg(error);
	//if the initial reading is farther than threshold then disregard, knows at opening
	if(initDist > FAR_THRESH)
		errTicks = 0;
	//does appropriate error compensation for number of turn ticks
	turnTicks = trackingLeft? -ENCODER_TARGET : ENCODER_TARGET;
	turnTicks += trackingLeft? errTicks : -errTicks;
}

void startTurn(){
	//takes the final reading before the turn
	getFinalDist();
	//error angle calculation for compensation
	float error = asin((finalDist - initDist) / distanceTraveled());
	float errTicks = DEG_TICKS * ToDeg(error);
	if(initDist > FAR_THRESH)
		errTicks = 0;

	turnTicks = trackingLeft? ENCODER_TARGET : -ENCODER_TARGET;
	turnTicks += trackingLeft? -errTicks : errTicks;
	//resets the accumulationError compensation
	accumError = 0;
}

bool completeTurn(){

	int leftPos = leftEnc.read(), rightPos = rightEnc.read();
	//continues to turn until both encoders reach target number of turn ticks depending on compensation
	//provides a small band <10 so that both the encoder can activate the condition
	if(abs(leftPos - turnTicks) < 10 && abs(rightPos + turnTicks) < 10){
		//resets and stops loop
		isOpening = false;
		encDiff = 0;
		return true;
	}

	float speed = turnTicks > 0? 1.5 : -1.5;
	//P control for the turns 
	int leftSpeed = speed * (abs(turnTicks) - abs(leftPos));
	int rightSpeed = -speed * (abs(turnTicks) - abs(rightPos));

	drive (leftSpeed, rightSpeed);
	return false;
}

bool driveBackwards(){
	//takes the current encoder readings and continues to drive backwords with P
	//control until the encoder difference is -80 ticks
	int encError = leftEnc.read() - rightEnc.read();
	if(getEncAvg() - initBackUpEncAverage < -80)
		//exit once condition has been met	
		return true;

	drive(-50 - K*encError, -50 + K*encError);
	return false;
}

bool driveStraight(){
	//condition to turn at the near object
	//when a flame is found
	if(isFlameFound && getSideDist() < 50)
		return false;
	//uses the difference between the front two sensors to error compensate
	int sonarError = cm[LF] - cm[RF]; 
	if(abs(sonarError) > 10)
		sonarError = 0;
	sonarError *= 2;
	
	//uses the changes in the side range sensors to compensate errors
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
	// drive straight with triple P controls(from 3 different sources)
	drive(50 - K * totalError - sonarError, 50 + K * totalError + sonarError);
	return true;
}
