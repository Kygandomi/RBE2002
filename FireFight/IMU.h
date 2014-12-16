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

void sov(){
	if(!blockSOV){
		float linDiff = (((leftEnc.read()+rightEnc.read()) * 6.0) / 200.0) - prevLinDis;
		int currentAngDis = initHeading - yaw;

		xDis += linDiff * sin(currentAngDis);																																																																																																																																																																																																																																																																																																																																																																												
		yDis += linDiff * cos(currentAngDis);

		prevLinDis += linDiff;
	}
}

void VectorSetup(){
	lcd.begin(16, 2);
	initHeading = yaw;

	Timer1.initialize(100);
	Timer1.attachInterrupt(sov);
}