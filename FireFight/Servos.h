void ServoSetup(){
	leftM.attach(leftMPin);
	rightM.attach(rightMPin);
	pan.attach(panPin);
	tilt.attach(tiltPin);
	gas.attach(gasPin, 1000, 2000);
}

void drive(int x, int y){
	if(x>100)
		x = 100;
	else if(x<-100)
		x = -100;
	if(y>100)
		y = 100;
	else if(y<-100)
		y = -100;

	if(x>0 && x<MIN_POWER)
		x = MIN_POWER;
	if(x<0 && x>-MIN_POWER)
		x = -MIN_POWER;
	if(y<0 && y>-MIN_POWER)
		y = -MIN_POWER;
	if(y>0 && y<MIN_POWER)
		y = MIN_POWER;


	int a = map(x, -100, 100, 1000, 2000);
	int b = map(y, -100, 100, 2000, 1000);

	leftM.writeMicroseconds(a);
	rightM.writeMicroseconds(b);
}