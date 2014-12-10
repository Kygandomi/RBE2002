void zeroEncoders(){
  rightEnc.write(0);
  leftEnc.write(0);
}

void EncoderSetup(){
	pinMode(2, INPUT_PULLUP);
	pinMode(A11, INPUT_PULLUP);
	pinMode(18, INPUT_PULLUP);
	pinMode(19, INPUT_PULLUP);

	zeroEncoders();
}

int limit(int value){
	if(value > 180)
		return 180;
	else if(value < 0)
		return 0;
	else
		return value;
}

void driveStraight(){
	int error = (leftEnc.read() - rightEnc.read());
	int leftVal = limit(140 + K*error);
	int rightVal = limit(40 + K*error);
	leftM.write(leftVal);
	rightM.write(rightVal);
}

void straightForABit(){
	Serial.println("GOING STRAIGHT FOR A BIT");
	if(millis()-inTime < 1000)
		driveStraight();
	else
		goTo(FORWARD);
}
