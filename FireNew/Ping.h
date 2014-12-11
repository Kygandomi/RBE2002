void checkStop(){
	if(cm[LF] < FRONT_THRESH || cm[RF] < FRONT_THRESH || cm[MF] < FRONT_THRESH){
		drive(0, 0);
		goTo(REROUTE);
	}
}

void checkForOpening(){
	int measurement = trackingLeft? cm[LB] : cm[RB];
	if(measurement > FAR_THRESH && measurement < MAX_DISTANCE){
		//startTurnOpening(trackingLeft);
		goTo(FORWARD_TIMED); then(EXPLORE);
	}
}

void checkSafety(){
	int measurement = trackingLeft? cm[LB] : cm[RB];
	if(measurement < NEAR_THRESH)
		goTo(REROUTE);
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
