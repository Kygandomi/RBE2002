void checkStop(){
	if(cm[LF] < FRONT_THRESH || cm[RF] < FRONT_THRESH || cm[MF] < FRONT_THRESH){
		drive(0, 0);
		if(!flameDetectedOnce){
			goTo(PAN_SENSOR);
		}
		else{
			startTurn();
		}
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
		endDist = trackingLeft? prevLB : prevRB;
		isOpening = true;
	}
}

void checkSafety(){
	if(trackingLeft){
		if(isOpening){
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
		if(isOpening){
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

void setDirection(){
	trackingLeft = (cm[LB] < cm[RB]);
}

void getInitDist(){
	initDist = trackingLeft? cm[LB] : cm[RB];
}

void getFinalDist(){
	finalDist = trackingLeft? cm[LB] : cm[RB];
}

void pingAll(){
	for(int i = 0; i < SONAR_NUM; i++)
		pingingSensors(i);
}
void setCurrPing(){
	currLB = cm[LB];
	currRB = cm[RB];
}
void setPrevPing(){
	prevLB = cm[LB];
	prevRB = cm[RB];
}
