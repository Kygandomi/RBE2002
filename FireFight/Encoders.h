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

double distanceTraveled(){
	int encAverage = (leftEnc.read() + rightEnc.read())/2;
	double toCM = encAverage / 16.4;
	return toCM;
}
double initDistanceTraveled(){
	double toCM = initEncAverage / 16.4;
	return toCM;
}


