//IMUlib.h
/*
Copyright (c) 2011 Pololu Corporation.
http://www.pololu.com/
*/
void I2C_Init();
void Gyro_Init();
void Read_Gyro();

#define ToRad(x) ((x)*0.01745329252)  // *pi/180
#define ToDeg(x) ((x)*57.2957795131)  // *180/pi

float G_Dt=0.02;    // Integration time (DCM algorithm)  We will run the integration loop at 50Hz if possible

long timer=0;   //general purpuse timer
int AN[3]; //array that stores the gyro and accelerometer data
int AN_OFFSET[3]={0,0,0}; //Array that stores the Offset of the sensors
int gyro_x;
int gyro_y;
int gyro_z;

void IMUSetup()
{
	I2C_Init();
	delay(1000);
	Gyro_Init();

	for(int i=0;i<32;i++){    // We take some readings...
		delay(20);
		Read_Gyro();
		for(int y=0; y<3; y++)   // Cumulate values
			AN_OFFSET[y] += AN[y];
	}

	for(int y=0; y<3; y++)
		AN_OFFSET[y] = AN_OFFSET[y]/32;

	timer=millis();
}

L3G gyro;

void I2C_Init(){
	Wire.begin();
}

void Gyro_Init(){
	gyro.init();
	gyro.writeReg(L3G_CTRL_REG4, 0x20); // 2000 dps full scale
	gyro.writeReg(L3G_CTRL_REG1, 0x0F); // normal power mode, all axes enabled, 100 Hz
}

void Read_Gyro(){
	gyro.read();

	AN[0] = gyro.g.x;
	AN[1] = gyro.g.y;
	AN[2] = gyro.g.z;
	gyro_x = (AN[0] - AN_OFFSET[0]);
	gyro_y = (AN[1] - AN_OFFSET[1]);
	gyro_z = (AN[2] - AN_OFFSET[2]);
}