int getSideDist(){
	return trackingLeft? cm[LB] : cm[RB];
}

bool checkStop(){
	if(cm[LF] < FRONT_THRESH || cm[RF] < FRONT_THRESH || cm[MF] < FRONT_THRESH){
		if(!flameDetectedOnce)
			goTo(PAN_SENSOR);
		else
			return true;
	}
	return false;
}

void checkForOpening(){
	int measurement = getSideDist();
	if(measurement > FAR_THRESH){
		initEncAverage = getEncAvg();
		endDist = trackingLeft? prevLB : prevRB;
		isOpening = true;
	}
}

void initialReadings(){
	long initTime = millis();
	while(millis() - initTime < 3000)
		pingAll();
}

void setDirection(){
	trackingLeft = (cm[LB] < cm[RB]);
}

void getInitDist(){
	initDist = getSideDist();
	if(initDist > FAR_THRESH)
		isFirstDetect = true;
}

void getFinalDist(){
	finalDist = getSideDist();
}

void pingAll(){
	prevLB = cm[LB];
	prevRB = cm[RB];
	for(int i = 0; i < SONAR_NUM; i++)
		pingingSensors(i);
}
