void zeroEncoders(){
  rightEnc.write(0);
  leftEnc.write(0);
}

void driveStraight(){
	int error = (leftEnc.read() - rightEnc.read());
	int leftVal = 40 + K*error;
	int rightVal = 140 + K*error;
	leftM.write(leftVal);
	rightM.write(rightVal);
	
    robotState = FLAME;	
}

void turnRobot(){
 //IMU 
 //Check sides to determine which way to turn
}

void drive(){
	leftM.write(30);
	rightM.write(145);
}
