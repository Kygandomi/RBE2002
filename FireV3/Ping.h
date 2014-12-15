int getSideDist(){
	return trackingLeft? cm[LB] : cm[RB];
}

bool checkStop(){
	return (cm[LF] < FRONT_THRESH || cm[RF] < FRONT_THRESH || cm[MF] < FRONT_THRESH);
}

bool checkForOpening(){
	if(getSideDist() > FAR_THRESH && getSideDist() < MAX_DISTANCE)
		return true;
	else{
		goFarther = false;
		return false;
	}
}

bool checkSafety(){
	return true;	
}

void setDirection(){
	trackingLeft = (cm[LB] < cm[RB]);
}

void getInitDist(){
	initDist = getSideDist();
	if(initDist > FAR_THRESH)
		goFarther = true;
}
