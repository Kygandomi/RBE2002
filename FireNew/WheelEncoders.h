void zeroEncoders(){
  rightEnc.write(0);
  leftEnc.write(0);
}

void driveStraight(){
	int error = (leftEnc.read() - rightEnc.read());
	int leftVal = 140 + K*error;
	int rightVal = 40 + K*error;
	leftM.write(leftVal);
	rightM.write(rightVal);

  	checkStop();
  	//checkForOpening();
  	//checkSafety(); 
}

void straightForABit(){
	if(millis()-inTime < 1000){
		leftM.write(170);
		rightM.write(10);
	}

	else{
		goForward = false;
		robotState = TURN; 
	}
}

void drive(){
	leftM.write(30);
	rightM.write(145);
}
