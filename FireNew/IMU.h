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

		heading = ToDeg(yaw);
	}
}

void startTurn(boolean turnLeft){
	Serial.println("Start turn");
	if(turnLeft){
		leftM.write(150);
		rightM.write(150);
		targetHeading = heading - 90;
	}

	else{
		leftM.write(50);
		rightM.write(50);
		targetHeading = heading + 90;
	}
}

boolean isDoneTurning(){
	int error = abs(heading - targetHeading);
	Serial.println(error);
	if(error < 5)
		return true;
	return false;
}
