bool driveBackwards(){
	int error = (leftEnc.read() - rightEnc.read()) * K;
	drive(-50 - error, -50 + error);

	return (distanceTraveled() < -10);
}

void moveFarther(){
	if(trackingLeft)
		leftEnc.write(leftEnc.read() - 1);
	else
		rightEnc.write(rightEnc.read() - 1);
}

void moveCloser(){
	if(!trackingLeft)
		leftEnc.write(leftEnc.read() - 1);
	else
		rightEnc.write(rightEnc.read() - 1);
}

void driveStraight(){
	int dist = getSideDist();
	if(dist < FAR_THRESH){
		if(dist > initDist)
			moveCloser();
		else if(dist < initDist)
			moveFarther();
	}
	int error = (leftEnc.read() - rightEnc.read()) * K;
	drive(50 - error, 50 + error);
}

void startTurn(){
	turnTicks = trackingLeft? ENCODER_TARGET : -ENCODER_TARGET;
}

void startTurnOpening(){
	turnTicks = trackingLeft? -ENCODER_TARGET : ENCODER_TARGET;
}

bool completeTurn(){
	int leftPos = leftEnc.read(), rightPos = rightEnc.read();

	if(abs(leftPos - turnTicks) < 10 && abs(rightPos + turnTicks) < 10)
		return true;

	float speed = turnTicks > 0? 1.5 : -1.5;

	int leftSpeed = speed * (abs(turnTicks) - abs(leftPos));
	int rightSpeed = -speed * (abs(turnTicks) - abs(rightPos));

	/*int diffError = abs(leftPos) - abs(rightPos);
	drive(leftSpeed - K * diffError, rightSpeed + K * diffError);*/

	drive (leftSpeed, rightSpeed);
	return false;
}