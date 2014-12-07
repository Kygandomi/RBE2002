void checkStop(){
  if((cm[LF] < 20 && cm[LF] != 0) || (cm[RF] < 20 && cm[RF] != 0) || (cm[MF] < 20 && cm[MF] < 0)){
  	//pan FlameSensor to face forward
	//if flame reading
	//go to flame case
	
    leftM.write(90);
    rightM.write(90);

    startTurn(!trackingLeft);
    robotState = TURN;
  }
}

void checkForOpening(){
	if(cm[LB] - prevLB > 20 ){
		startTurn(trackingLeft);
		goForward = true;
		robotState = TURN;
	}

	else if(cm[RB] - prevRB > 20){
		startTurn(trackingLeft);
		goForward = true;
		robotState = TURN;
	}
}

void checkSafety(){
	if((cm[LB] < 20 && cm[LB] != 0)||(cm[RB] < 20 && cm[RB] != 0)){
	    goForward = true;
	    startTurn(!trackingLeft);
	    robotState = TURN;
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