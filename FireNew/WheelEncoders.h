#include <math.h>
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
	if(leftEnc.read() > 750 && rightEnc.read() > 750)
		goTo(FORWARD);
	else
		driveStraight();
		
}

void startTurnOpening(boolean turnLeft){
	zeroEncoders();
	if(turnLeft){
		turnTicks = -320;	
	}
	else {
		turnTicks = 320;
	}
}



void startTurn(boolean turnLeft){
	if(trackingLeft){
		finalDist = cm[LB];
		isFirstCheck = true;
	}

	else{
		finalDist = cm[RB];
		isFirstCheck = true; 
	}

	// Serial.print("initDist ");
	// Serial.println(initDist);
	// Serial.print("finalDist ");
	// Serial.println(finalDist);

	int encAverage = (leftEnc.read() + rightEnc.read())/2;
	double toCM = encAverage / 16.4; 

	float error = asin((finalDist - initDist)/toCM);
	float errAngle = (180/ 3.14)*error;
	float errTicks = 3.36 * errAngle; 

	zeroEncoders();

	if(turnLeft){
		turnTicks = -320 + errTicks;	
	}
	else {
		turnTicks = 320 - errTicks;
	}

	Serial.print("errorAngle ");
	Serial.println(errAngle);
	Serial.print(" turnTicks ");
	Serial.println(turnTicks);
}

boolean isDoneTurning(){
	int leftPos = leftEnc.read(), rightPos = rightEnc.read();

	if(abs(leftPos - turnTicks) < 10 && abs(rightPos + turnTicks) < 10){
		drive(0, 0);
		zeroEncoders();
		return true;
	}

	//Serial.print(abs(leftPos - turnTicks));
	//Serial.print("   ");
	//Serial.println(abs(rightPos + turnTicks));

	float speed = turnTicks > 0? 1.5 : -1.5;

	int leftSpeed = speed * (abs(turnTicks) - abs(leftPos));
	int rightSpeed = -speed * (abs(turnTicks) - abs(rightPos));

	/*int diffError = abs(leftPos) - abs(rightPos);
	drive(leftSpeed - K * diffError, rightSpeed + K * diffError);*/

	drive (leftSpeed, rightSpeed);

	return false;
}
