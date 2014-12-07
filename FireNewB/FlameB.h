boolean checkFlameSensor(){
  //checks Flame sensor and returns true if flame is nearby
  if(analogRead(A0) > flame){
  	return true;
  } 
  
  else{
  	robotState = FORWARD; 
  	return false; 
  }
}

void findFlame(){
 //routine for finding flame 
}