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
	if((millis() - driveTimer) > 20 && dist < FAR_THRESH){
		if(dist > initDist)
			moveCloser();
		else if(dist < initDist)
			moveFarther();
		driveTimer = millis();
	}
	int error = (leftEnc.read() - rightEnc.read()) * K;
	drive(50 - error, 50 + error);
}

int wrap(int angle){
	if(angle > 180)
		return angle - 360;
	else if(angle < -180)
		return angle + 360;
	return angle;
}

void startTurn(){
	targetHeading = heading;
	targetHeading += trackingLeft? 90 : -90;
	targetHeading = wrap(targetHeading);
}

void startTurnOpening(){
	targetHeading = heading;
	targetHeading += trackingLeft? -90 : 90;
	targetHeading = wrap(targetHeading);
}

bool completeTurn(){
	int diff = abs(wrap(targetHeading - heading));
	if(diff < 10)
		return true;

	int speed = (targetHeading - heading) > 0? 4 : -4;

	drive(speed * diff, -speed * diff);
	return false;
}