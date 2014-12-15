int getSideDist(){
	return trackingLeft? leftCM : rightCM;
}

bool checkStop(){
	return (cm[LF] < FRONT_THRESH || cm[RF] < FRONT_THRESH || cm[MF] < FRONT_THRESH);
}

int checkForOpening(){
	if(getSideDist() == MAX_DISTANCE)
		return 0;
	if(getSideDist() > FAR_THRESH)
		return 1;
	else{
		goFarther = false;
		return -1;
	}
}

bool checkSafety(){
	return true;	
}

void setDirection(){
	trackingLeft = (leftCM < rightCM);
}

void getInitDist(){
	initDist = getSideDist();
	if(initDist > FAR_THRESH)
		goFarther = true;
}

void pingAll(){
	leftCM = cm[LB];
	rightCM = cm[RB];
	for(int i = 0; i < SONAR_NUM; i++)
		pingingSensors(i);
}
