//Ping.h
/* Written by Katie Gandomi, Alexander O'Brien, Yu-sen Wu, Shao Zhou */

int getSideDist(){
	return trackingLeft? cm[LB] : cm[RB]; //return distance to side wall
}

bool checkStop(){
	if(cm[LF] < FRONT_THRESH || cm[RF] < FRONT_THRESH || cm[MF] < FRONT_THRESH){ //look out for obstacles in front
		if(!flameDetectedOnce)
			goTo(PAN_SENSOR); //must be candle base
		else
			return true;
	}
	return false;
}

void checkForOpening(){
	if(getSideDist() > FAR_THRESH){ //must be something to explore
		initEncAverage = getEncAvg();
		endDist = trackingLeft? prevLB : prevRB;
		isOpening = true;
	}
	else{ //nothing to explore
		isOpening = false;
		encDiff = 0;
		isFirstDetect = false;
	}
}

void initialReadings(){
	long initTime = millis();
	while(millis() - initTime < 3000) //read for 3 sec
		pingAll();
}

void setDirection(){
	trackingLeft = (cm[LB] < cm[RB]); //which side is closer?
}

void getInitDist(){
	initDist = getSideDist(); //set the initial distance
	if(initDist > FAR_THRESH)
		isFirstDetect = true;
}

void getFinalDist(){
	finalDist = getSideDist(); //set final distance
}

void pingAll(){
	prevLB = cm[LB];
	prevRB = cm[RB];
	for(int i = 0; i < SONAR_NUM; i++) //update all distance values
		pingingSensors(i);
}
