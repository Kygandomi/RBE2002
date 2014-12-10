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

void straightForABit(){
	Serial.println("GOING STRAIGHT FOR A BIT");
	if(millis()-inTime < 1000)
		driveStraight();
	else
		goTo(FORWARD);
}

void startTurn(boolean turnLeft){
	expectedHeading += 90;
	zeroEncoders();
	turnTicks = turnLeft? -ENCODER_TARGET : ENCODER_TARGET;
}

boolean isDoneTurning(){
	int leftPos = leftEnc.read(), rightPos = rightEnc.read();

	if(abs(leftPos - turnTicks) < 10 && abs(rightPos + turnTicks) < 10){
		drive(0, 0);
		return true;
	}

	Serial.print(abs(leftPos - turnTicks));
	Serial.print("   ");
	Serial.println(abs(rightPos + turnTicks));

	float speed = turnTicks > 0? 1.5 : -1.5;

	int leftSpeed = speed * (abs(turnTicks) - abs(leftPos));
	int rightSpeed = -speed * (abs(turnTicks) - abs(rightPos));

	/*int diffError = abs(leftPos) - abs(rightPos);
	drive(leftSpeed - K * diffError, rightSpeed + K * diffError);*/

	drive (leftSpeed, rightSpeed);

	return false;
}
