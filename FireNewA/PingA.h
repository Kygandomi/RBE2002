void checkStop(){
	if(cm[LF] < FRONT_THRESH || cm[RF] < FRONT_THRESH || cm[MF] < FRONT_THRESH){
		drive(0, 0);
		goTo(PAN_SENSOR);
	}
}
void checkInitDist(){
	if(isFirstOpen){
		if(initDist > FAR_THRESH){
			isFirstDetect = true;
			isFirstOpen = false;
		}
}
}
void checkForOpening(){
	int measurement = trackingLeft? currLB : currRB;
	if(measurement > FAR_THRESH){
		initEncAverage = (leftEnc.read() + rightEnc.read())/2;
		Serial.print("initEncAverage ");
		Serial.println(initEncAverage);
		Serial.print("CALCULATING prevLB ");
		Serial.println(prevLB);
		endDist = trackingLeft? prevLB : prevRB;
		checkOpeningFirst = true;
		//startTurnOpening(trackingLeft);
		//goTo(FORWARD_TIMED); then(EXPLORE);
		Serial.print(" WE USE THIS ONE " );
		Serial.println(endDist);
	}
}

void checkSafety(){
	if(trackingLeft){
		if(checkOpeningFirst){
			if (cm[LB] == prevLB){
				accumError += 0;
			}
			else if(cm[LB] > 16){
				accumError += 10;
			}
			else if(cm[LB] < 14){
				accumError += -10;
			}
		}		
	}
	else {
		if(checkOpeningFirst){
			if(cm[RB] == prevRB){
				accumError += 0;
			}
			else if(cm[RB] > 16){
				accumError += -10;
			}
			else if(cm[RB] < 14){
				accumError += 10;
			}
		}
	}	
}

void dirTracking(){
	trackingLeft = (cm[LB] < cm[RB]);
}

void getInitDist(){
	initDist = trackingLeft? cm[LB] : cm[RB];
}

void getFinalDist(){
	finalDist = trackingLeft? cm[LB] : cm[RB];
}
