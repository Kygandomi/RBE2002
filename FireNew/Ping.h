void checkStop(){
	if(cm[LF] < FRONT_THRESH || cm[RF] < FRONT_THRESH || cm[MF] < FRONT_THRESH){

		leftM.write(90);
		rightM.write(90);
		startTurn(!trackingLeft);
		goTo(TURN);
	}
}

void checkForOpening(){
	if(trackingLeft){
		if(cm[LB] > FAR_THRESH){
			startTurn(trackingLeft);
			goTo(TURN);
		}
	}
	else{
		if(cm[RB] > FAR_THRESH){
			startTurn(trackingLeft);
			goTo(TURN);
		}
	}
}

void checkSafety(){
	if(trackingLeft){
		if(cm[LB] < NEAR_THRESH){
			startTurn(!trackingLeft);
			goTo(TURN);
		}
	}
	else{
		if(cm[RB] < NEAR_THRESH){
			startTurn(!trackingLeft);
			goTo(TURN);
		}
	}
}

void dirTracking(){
	if(cm[LB] < cm[RB]){
		trackingLeft = true;
	}	
	else if(cm[RB] < cm[LB]){
		trackingLeft = false; 
	}
}

void getInitDist(){
	
					
}