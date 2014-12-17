void zeroEncoders(){
	rightEnc.write(0);
	leftEnc.write(0);
}

void EncoderSetup(){
	pinMode(2, INPUT_PULLUP);
	pinMode(A0, INPUT_PULLUP);
	pinMode(18, INPUT_PULLUP);
	pinMode(19, INPUT_PULLUP);
}

int getEncAvg(){
	return (leftEnc.read() + rightEnc.read()) / 2;
}

double distanceTraveled(){
	int encAverage = getEncAvg();
	double toCM = encAverage / TICKS_CM;
	return toCM;
}

double initDistanceTraveled(){
	double toCM = initEncAverage / TICKS_CM;
	return toCM;
}
