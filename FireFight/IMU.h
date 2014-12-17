void collectIMUData(){
	// if((millis() - timer) > 19){
	// 	counter++;
	// 	G_Dt = abs(millis() - timer)/1000.0;
	// 	timer=millis();

	// 	Read_Gyro();
	// 	Read_Accel();

	// 	if (counter > 5){
	// 		counter=0;
	// 		Read_Compass();
	// 		Compass_Heading();
	// 	}

	// 	Matrix_update(); 
	// 	Normalize();
	// 	Drift_correction();
	// 	Euler_angles();

	// 	heading = ToDeg(yaw);
	// }
	int interval = millis() - timer;
	if(interval > 19) // Main loop runs at 50Hz
	{
		counter++;
		G_Dt = interval / 1000.0; // Real time of loop run. We use this on the DCM algorithm (gyro integration time)
		timer = millis();

		Read_Gyro(); // This read gyro data
		Read_Accel(); // Read I2C accelerometer

		if(robotState == TURN)
			heading += gyro_z * G_Dt * 0.07;

		//Serial.println(heading);
	}
}

void VectorSetup(){
	//lcd.begin(16, 2);
}
/*
void sumOfVectors(){
	int linDiff = ((leftEnc.read()+rightEnc.read()) / 33); // - prevLinDis;
	float currentAngDis = ToRad(heading); //initHeading - yaw;

	xDis += linDiff * cos(currentAngDis);
	yDis += linDiff * sin(currentAngDis);
}
*/