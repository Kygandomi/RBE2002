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

void VectorSetup(){
	initHeading = yaw;

	Timer1.initialize(100000);
	Timer1.attachInterrupt(sov);

	lcd.begin(16, 2);
}

void sov(){
	if(!blockSOV){
		double linDiff = ((leftEnc.read()+rightEnc.read()) / 32.8) - prevLinDis;
		double currentAngDis = initHeading - yaw;

		xDis += linDiff * cos(currentAngDis);
		yDis += linDiff * sin(currentAngDis);

		Serial.print(cos(currentAngDis));
		Serial.print("    ");
		Serial.println(sin(currentAngDis));

		prevLinDis += linDiff;
	}
}