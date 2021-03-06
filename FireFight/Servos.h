//Servos.h
/* Written by Katie Gandomi, Alexander O'Brien, Yu-sen Wu, Shao Zhou */

void ServoSetup(){
	leftM.attach(leftMPin);
	rightM.attach(rightMPin);
	pan.attach(panPin, 1000, 2000);
	tilt.attach(tiltPin, 1000, 2000);
	gas.attach(gasPin, 1000, 2000);
}

//this enables us to tell the motors to drive in an intuitive way
//as a percentage rather than degree from 90
//also mapped so positive is forward for both motors!
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

	leftM.writeMicroseconds(map(x, -100, 100, 1000, 2000));
	rightM.writeMicroseconds(map(y, -100, 100, 2000, 1000));
}