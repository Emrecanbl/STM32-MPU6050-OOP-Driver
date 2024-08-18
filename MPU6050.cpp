/*
 * MPU6050.cpp
 *
 *  Created on: Aug 18, 2024
 *      Author: Emrec
 */

#include "main.h"
#include "stm32g0xx_hal.h"
#include "MPU6050.h"

extern I2C_HandleTypeDef hi2c1;

MPU6050::MPU6050() {
	// TODO Auto-generated constructor stub
}

MPU6050::~MPU6050() {
	// TODO Auto-generated destructor stub
}

void MPU6050::writeRegister(uint8_t reg, uint8_t* data,uint8_t len){
	HAL_I2C_Mem_Write(&hi2c1, MPU6050_I2C_ADRESS_AD0, reg, 1, data, len, 100);
}
uint8_t MPU6050::readRegister(uint8_t reg, uint8_t* data,uint8_t len){
	HAL_I2C_Mem_Read(&hi2c1, MPU6050_I2C_ADRESS_AD0, reg, 1, data, len, 100);
}
uint8_t MPU6050::checkDeviceID(){
	uint8_t Data;
	readRegister(MPU_REG_WHO_AM_I, &Data,1);
	return Data;
}
void MPU6050::Gyroscope_Read(){
	uint8_t Data[6];
	int16_t RAW_Gyro_XOUT = 0 ;
	int16_t RAW_Gyro_YOUT = 0 ;
	int16_t RAW_Gyro_ZOUT = 0 ;

	readRegister(MPU_REG_GYRO_XOUT_H, Data, 6);

	RAW_Gyro_XOUT = (int16_t)(Data[0]<<8)|(Data[1]);
	RAW_Gyro_YOUT = (int16_t)(Data[2]<<8)|(Data[3]);
	RAW_Gyro_ZOUT = (int16_t)(Data[4]<<8)|(Data[5]);

	GYRO_XOUT = RAW_Gyro_XOUT/16.4-(x_cali); // LSB/°/s
	GYRO_YOUT = RAW_Gyro_YOUT/16.4-(y_cali); //MPU_6050_Gyroscope_Cali outputs
	GYRO_ZOUT = RAW_Gyro_ZOUT/16.4-(z_cali);
}
float MPU6050::Read_Gyro_X(){
	uint8_t Data[2];
	int16_t RAW_Gyro_XOUT = 0 ;

	readRegister(MPU_REG_GYRO_XOUT_H, Data, 2);
	RAW_Gyro_XOUT = (int16_t)(Data[0]<<8)|(Data[1]);
	return GYRO_XOUT = RAW_Gyro_XOUT/16.4-(x_cali); // LSB/°/s  MPU_6050_Gyroscope_Cali outputs
}
float MPU6050::Read_Gyro_Y(){
	uint8_t Data[2];
	int16_t RAW_Gyro_YOUT = 0 ;

	readRegister(MPU_REG_GYRO_YOUT_H, Data, 2);
	RAW_Gyro_YOUT = (int16_t)(Data[0]<<8)|(Data[1]);
	return GYRO_YOUT = RAW_Gyro_YOUT/16.4-(y_cali); // LSB/°/s  MPU_6050_Gyroscope_Cali outputs
}
float MPU6050::Read_Gyro_Z(){
	uint8_t Data[2];
	int16_t RAW_Gyro_ZOUT = 0 ;

	readRegister(MPU_REG_GYRO_XOUT_H, Data, 2);
	RAW_Gyro_ZOUT = (int16_t)(Data[0]<<8)|(Data[1]);
	return GYRO_ZOUT = RAW_Gyro_ZOUT/16.4-(z_cali); // LSB/°/s  MPU_6050_Gyroscope_Cali outputs
}

uint8_t MPU6050::MPU_Init(){
	uint8_t check;
	uint8_t Data;
	float Raw_x_cali;
	float Raw_y_cali;
	float Raw_z_cali;

	if (checkDeviceID() == 0x68)  // Check Sensor
	{
		Data = 0;// Power-Up
		writeRegister(MPU_REG_PWR_MGMT_1,&Data,1);
		Data = 0x07;// 1 kHZ
		writeRegister(MPU_REG_SMPLRT_DIV,&Data,1);
		Data=0;
		Data |= (3 << 3);// 2000 °/s
		writeRegister(MPU_REG_GYRO_CONFIG,&Data,1);
		Data=0;
		Data |= (3 << 3);// 16g
		writeRegister(MPU_REG_ACCEL_CONFIG,&Data,1);

		for(int i =0 ;i<=1000;i++){
			Gyroscope_Read();
			Raw_x_cali=x_cali+GYRO_XOUT;
			Raw_y_cali=y_cali+GYRO_YOUT;
			Raw_z_cali=z_cali+GYRO_ZOUT;
		}
		x_cali =Raw_x_cali/1000;	//-2.6245
		y_cali=Raw_y_cali/1000;		//2.9287  Calibration value Gyro
		z_cali=Raw_z_cali/1000;		//-2.502
		return 1;
	}
	else {
		return 0;
	}
}
int16_t MPU6050::Temp_Read(){
	uint8_t Data[2];
	readRegister(MPU_REG_ACCEL_TEMP_OUT_H,Data, 2);
	int16_t Temp =((Data[0] << 8)|Data[1]);
	Temp = (Temp/340) + 36.5;
	return Temp;
}
void MPU6050::Accelerometer_Read(){
	uint8_t Data[6];
	int16_t RAW_ACCEL_XOUT = 0 ;
	int16_t RAW_ACCEL_YOUT = 0 ;
	int16_t RAW_ACCEL_ZOUT = 0 ;

	readRegister(MPU_REG_ACCEL_XOUT_H, Data, 6);

	RAW_ACCEL_XOUT = (int16_t)(Data[0]<<8)|(Data[1]);
	RAW_ACCEL_YOUT = (int16_t)(Data[2]<<8)|(Data[3]);
	RAW_ACCEL_ZOUT = (int16_t)(Data[4]<<8)|(Data[5]);

	ACCEL_XOUT = RAW_ACCEL_XOUT/2048.0; //LSB Sensitivity
	ACCEL_YOUT = RAW_ACCEL_YOUT/2048.0;
	ACCEL_ZOUT = RAW_ACCEL_ZOUT/2048.0;
}
float MPU6050::Read_Accelerometer_X(){
	uint8_t Data[2];
	int16_t RAW_ACCEL_XOUT = 0 ;

	readRegister(MPU_REG_ACCEL_XOUT_H, Data, 2);
	RAW_ACCEL_XOUT = (int16_t)(Data[0]<<8)|(Data[1]);
	return ACCEL_XOUT = RAW_ACCEL_XOUT/2048.0; //LSB Sensitivity
}
float MPU6050::Read_Accelerometer_Y(){
	uint8_t Data[2];
	int16_t RAW_ACCEL_YOUT = 0 ;

	readRegister(MPU_REG_ACCEL_YOUT_H, Data, 6);
	RAW_ACCEL_YOUT = (int16_t)(Data[0]<<8)|(Data[1]);
	return ACCEL_YOUT = RAW_ACCEL_YOUT/2048.0;
}
float MPU6050::Read_Accelerometer_Z(){
	uint8_t Data[2];
	int16_t RAW_ACCEL_ZOUT = 0 ;
	readRegister(MPU_REG_ACCEL_ZOUT_H, Data, 2);
	RAW_ACCEL_ZOUT = (int16_t)(Data[0]<<8)|(Data[1]);
	return ACCEL_ZOUT = RAW_ACCEL_ZOUT/2048.0;
}
float MPU6050::Read_Angle_X(){
	Accelerometer_Read();
	float x,y,z;
	x = ACCEL_XOUT;
	y = ACCEL_YOUT;
	z = ACCEL_ZOUT;
	float tanx;
	tanx = x/(sqrtf((z)*(z))+(y*y));
	tanx = atanf(tanx);
	Angle_X = tanx*(1/(3.14/180.0));
	return Angle_X;
}
float MPU6050::Read_Angle_Y(){
	Accelerometer_Read();
	float x,y,z;
	x = ACCEL_XOUT;
	y = ACCEL_YOUT;
	z = ACCEL_ZOUT;
	float tany;
	tany = y/(sqrtf((x)*(x))+(z*z));
	tany = atanf(tany);
	Angle_Y	= tany*(1/(3.14/180.0));
	return Angle_Y;
}
float MPU6050::Read_Angle_Z(){
	Accelerometer_Read();
	float x,y,z;
	x = ACCEL_XOUT;
	y = ACCEL_YOUT;
	z = ACCEL_ZOUT;
	float tanz;
	tanz = z/(sqrtf((y)*(y))+(x*x));
	tanz = atanf(tanz);
	Angle_Z = tanz*(1/(3.14/180.0));
	return Angle_Z;
}
