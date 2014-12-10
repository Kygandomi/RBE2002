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
	}
}

void alignWithWall(){
 //right now sets the state to Forward
 //should use IMU to align robot with a particular axis
 robotState = FORWARD;  
}

void startTurn(boolean turnLeft){
	if(turnLeft){
		leftM.write(150);
		rightM.write(150);
		targetHeading = yaw - 90;
	}

	else{
		leftM.write(50);
		rightM.write(50);
		targetHeading = yaw + 90;
	}
}

boolean isDoneTurning(){
	if(abs(yaw - targetHeading) > 5){
		return false;
	}
	else{
		if(goForward){
			inTime = millis();
		}
	 return true;
	}
}

void sumOfVectors(){
	//obtain angualr and linear displacement
	float ang_displacement = yaw - prev_yaw;
	float displacement = (leftEnc.read()+rightEnc.read())/2;
	//calculation for displacement
	// x_ and y_displacement are decleared in Junior.h
	x_displacement += displacement * cos(ang_displacement);
	y_displacement += displacement * sin(ang_displacement);
	//reset the sensors
	zeroEncoders();
	prev_yaw = yaw;
}

