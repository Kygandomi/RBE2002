void checkStop(){
  if((cm[LF] < 20 && cm[LF] != 0) || (cm[RF] < 20 && cm[RF] != 0)){
    leftM.write(90);
    rightM.write(90);
    //zeroEncoders();
    robotState = TURN;
  }
}

void checkSensors(){
	if(cm[LB] < 20 && cm[LB] != 0){
	    //routine for correcting if LB is close to wall
	    robotState = SENSOR;
	    correctR = true;
	}

	if(cm[RB] < 20 && cm[RB] != 0){
	   //routine for correcting if RB is close to wall
	   robotState = SENSOR; 
	   correctR = false;
	}

	else{
		robotState = FORWARD; 
	}
}