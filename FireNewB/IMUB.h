void collectIMUData(){
	if((millis() - timer) > 19){
		counter++;
		G_Dt = abs(millis() - timer)/1000.0;
		timer=millis();
		Read_Gyro();
		Read_Accel();

		if (counter > 5){
			counter=0;
			Read_Compass();
			Compass_Heading();
		}

		Matrix_update(); 
		Normalize();
		Drift_correction();
		Euler_angles();

		printdata();
	}
}

void alignWithWall(){
 //right now sets the state to Forward
 robotState = FORWARD;  
}

void turnRobot(boolean turnRight){
 //IMU 
 //Check sides to determine which way to turn
}

void correct(boolean x){

}