void zeroEncoders(){
  rightEnc.write(0);
  leftEnc.write(0);
}

void EncoderSetup(){
	pinMode(2, INPUT_PULLUP);
	pinMode(A11, INPUT_PULLUP);
	pinMode(18, INPUT_PULLUP);
	pinMode(19, INPUT_PULLUP);
}

void driveStraight(){
	int error = leftEnc.read() - rightEnc.read();
	drive(60 - K*error, 60 + K*error);
}

double distanceTraveled(){
	int encAverage = (leftEnc.read() + rightEnc.read())/2;
	double toCM = encAverage / 16.4;
	return toCM;
}

void straightForABit(){
	if(distanceTraveled() > 20)
		goTo(nextState);
	else
		driveStraight();
		
}

void startTurnOpening(){
	turnTicks = trackingLeft? -ENCODER_TARGET : ENCODER_TARGET;
	goTo(TURN); then(FORWARD_TIMED);
}

void startTurn(){
	getFinalDist();

	float error = asin((finalDist - initDist)/distanceTraveled());
	float errTicks = 3.36 * ToDeg(error);

	turnTicks = trackingLeft? ENCODER_TARGET : -ENCODER_TARGET;
	turnTicks += trackingLeft? -errTicks : errTicks;
	
	goTo(TURN); then(FORWARD);
}

void completeTurn(){
	int leftPos = leftEnc.read(), rightPos = rightEnc.read();

	if(abs(leftPos - turnTicks) < 10 && abs(rightPos + turnTicks) < 10){
		drive(0, 0);
		goTo(nextState); then(FORWARD);
		return;
	}

	float speed = turnTicks > 0? 1.5 : -1.5;

	int leftSpeed = speed * (abs(turnTicks) - abs(leftPos));
	int rightSpeed = -speed * (abs(turnTicks) - abs(rightPos));

	/*int diffError = abs(leftPos) - abs(rightPos);
	drive(leftSpeed - K * diffError, rightSpeed + K * diffError);*/

	drive (leftSpeed, rightSpeed);
}
