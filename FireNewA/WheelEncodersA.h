void zeroEncoders(){
  rightEnc.write(0);
  leftEnc.write(0);
}

void EncoderSetup(){
	pinMode(2, INPUT_PULLUP);
	pinMode(A0, INPUT_PULLUP);
	pinMode(18, INPUT_PULLUP);
	pinMode(19, INPUT_PULLUP);
}

double distanceTraveled(){
	int encAverage = (leftEnc.read() + rightEnc.read())/2;
	double toCM = encAverage / 16.4;
	return toCM;
}
double initDistanceTraveled(){
	double toCM = initEncAverage / 16.4;
	return toCM;
}

void startTurnOpening(){ 
	Serial.println(" startTurnOpening... ");
	float error = asin((endDist - initDist) / initDistanceTraveled());
	float errTicks = 3.36 * ToDeg(error);
	if(initDist > FAR_THRESH){
		errTicks = 0;
	}
	Serial.print(" isFirstDetect ");
	Serial.println(isFirstDetect);
	Serial.print(" final dist ");
	Serial.println(endDist);
	Serial.print(" init dist ");
	Serial.println(initDist);
	Serial.print(" error angle ");
	Serial.println(error);
	Serial.print(" initEncAverage ");
	Serial.println(initEncAverage);
	Serial.print("errTicks ");
	Serial.println(errTicks);


	turnTicks = trackingLeft? -ENCODER_TARGET : ENCODER_TARGET;
	turnTicks += trackingLeft? errTicks : -errTicks;

	goTo(TURN);
}

void startTurn(){
		getFinalDist();


	float error = asin((finalDist - initDist) / distanceTraveled());
	float errTicks = 3.36 * ToDeg(error);
	if(initDist > FAR_THRESH){
		errTicks = 0;
	}

	Serial.print("errTicks ");
	Serial.println(errTicks);

	turnTicks = trackingLeft? ENCODER_TARGET : -ENCODER_TARGET;
	turnTicks += trackingLeft? -errTicks : errTicks;

	Serial.print("turnTicks ");
	Serial.println(turnTicks);
	
	goTo(TURN); 
}

void completeTurn(){
	int leftPos = leftEnc.read(), rightPos = rightEnc.read();

	if(abs(leftPos - turnTicks) < 10 && abs(rightPos + turnTicks) < 10){
		drive(0, 0);
		checkOpeningFirst = false;
		encDiff = 0;
		isFirstOpen = true;
		accumError = 0;
		goTo(FORWARD);
		return;
	}

	float speed = turnTicks > 0? 1.5 : -1.5;

	int leftSpeed = speed * (abs(turnTicks) - abs(leftPos));
	int rightSpeed = -speed * (abs(turnTicks) - abs(rightPos));

	/*int diffError = abs(leftPos) - abs(rightPos);
	drive(leftSpeed - K * diffError, rightSpeed + K * diffError);*/

	drive (leftSpeed, rightSpeed);
}
void checkCliff(){
	if(analogRead(cliffSensor) > 800){
		goTo(BACKUP);
	}
}
void driveBackwards(){
	int leftEncTick = leftEnc.read();
		int rightEncTick = rightEnc.read();
		int Eerror = leftEncTick - rightEncTick;
		int currentEncAverage = (leftEnc.read() + rightEnc.read())/2;
		if(currentEncAverage < 0){
			drive(0, 0);
			goTo(REROUTE);
		}

	drive(-50 - K*Eerror, -50 + K*Eerror);
}
void driveStraight(){
	if(isFlameFound){
		if(trackingLeft){
			if(cm[RB] < 35){
				startTurn();
			}
		}
		else{
			if(cm[LB] < 35){
				startTurn();
			}
		}
	}
	int Rerror = (cm[LF] - cm[RF])-2; 
		if(Rerror > 10 || Rerror < -10){
			Rerror = 0;
		}
		int leftEncTick = leftEnc.read();
		int rightEncTick = rightEnc.read();
		int Kp = 2;
	if(trackingLeft){
		if(!checkOpeningFirst){
			if (cm[LB] == prevLB){
				accumError += 0;
			}
			else if(cm[LB] > prevLB){
				accumError += 15;
			}
			else if(cm[LB] < prevLB){
				accumError += -15;
			}
		}
		else{
			if(cm[RB] == prevRB){
				accumError += 0;
			}
			else if(cm[RB] > prevRB){
				accumError += -15;
			}
			else if(cm[RB] < prevRB){
				accumError += 15;
			}
		}
	}
	else {
		if(!checkOpeningFirst){
			if(cm[RB] == prevRB){
				accumError += 0;
			}
			else if(cm[RB] > prevRB){
				accumError += -15;
			}
			else if(cm[RB] < prevRB){
				accumError += 15;
			}
		}
		else{
			if (cm[LB] == prevLB){
				accumError += 0;
			}
			else if(cm[LB] > prevLB){
				accumError += 15;
			}
			else if(cm[LB] < prevLB){
				accumError += -15;
			}
		}
	}
	int Eerror = leftEncTick - rightEncTick;
	int totError = Eerror + accumError;

	Serial.print(" RError  ");
	Serial.println(Rerror);
	Serial.print("totError  ");
	Serial.println(totError);
	drive(80 - K*totError - Kp*Rerror, 80 + K*totError + Kp*Rerror);
}