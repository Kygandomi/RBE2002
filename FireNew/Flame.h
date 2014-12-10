boolean checkFlameSensor(){
  //checks Flame sensor and returns true if flame is nearby
	if(analogRead(A0) < 900)
  		return true;
  	return false; 
}

void findFlame(){
 //routine for finding flame

}

//pan values for flame sensor
//right 135 
//front 80
//left 30