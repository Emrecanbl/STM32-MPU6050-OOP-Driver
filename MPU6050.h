/*
 * MPU6050.h
 *
 *  Created on: Aug 18, 2024
 *      Author: Emrec
 */

#ifndef SRC_MPU6050_H_
#define SRC_MPU6050_H_

#include <stdint.h>
#include <cmath>
#include "stm32g0xx_hal.h"

class MPU6050 {
public:
	MPU6050();
	void Accelerometer_Read();
	void Angle();
	float Read_Angle_X();
	float Read_Angle_Y();
	float Read_Angle_Z();
	float Read_Accelerometer_X();
	float Read_Accelerometer_Y();
	float Read_Accelerometer_Z();
	float Read_Gyro_X();
	float Read_Gyro_Y();
	float Read_Gyro_Z();
	void Gyroscope_Read();
	uint8_t MPU_Init();
	int16_t Temp_Read();
	virtual ~MPU6050();
private:

    float x_cali = 0;
    float y_cali = 0 ;
    float z_cali = 0;
	float GYRO_XOUT;
	float GYRO_YOUT;
	float GYRO_ZOUT;
	float Angle_X;
	float Angle_Y;
	float Angle_Z;
	float ACCEL_XOUT;
	float ACCEL_YOUT;
	float ACCEL_ZOUT;
    void writeRegister(uint8_t reg, uint8_t* data,uint8_t len);
    uint8_t readRegister(uint8_t reg, uint8_t* data,uint8_t len);
    uint8_t checkDeviceID();
protected:
    static constexpr uint8_t MPU6050_I2C_ADRESS_AD0 = 0x68 << 1;
    static constexpr uint8_t MPU6050_I2C_ADRESS_AD1 = 0x69 << 1;

    static constexpr uint8_t MPU_REG_SELF_TEST_X = 13;
    static constexpr uint8_t MPU_REG_SELF_TEST_Y = 14;
    static constexpr uint8_t MPU_REG_SELF_TEST_Z = 15;
    static constexpr uint8_t MPU_REG_SELF_TEST_A = 16;
    static constexpr uint8_t MPU_REG_SMPLRT_DIV = 25;
    static constexpr uint8_t MPU_REG_CONFIG = 26;
    static constexpr uint8_t MPU_REG_GYRO_CONFIG = 27;
    static constexpr uint8_t MPU_REG_ACCEL_CONFIG = 28;
    static constexpr uint8_t MPU_REG_ACCEL_XOUT_H = 59;
    static constexpr uint8_t MPU_REG_ACCEL_XOUT_L = 60;
    static constexpr uint8_t MPU_REG_ACCEL_YOUT_H = 61;
    static constexpr uint8_t MPU_REG_ACCEL_YOUT_L = 62;
    static constexpr uint8_t MPU_REG_ACCEL_ZOUT_H = 63;
    static constexpr uint8_t MPU_REG_ACCEL_ZOUT_L = 64;
    static constexpr uint8_t MPU_REG_ACCEL_TEMP_OUT_H = 65;
    static constexpr uint8_t MPU_REG_ACCEL_TEMP_OUT_L = 66;
    static constexpr uint8_t MPU_REG_GYRO_XOUT_H = 67;
    static constexpr uint8_t MPU_REG_GYRO_XOUT_L = 68;
    static constexpr uint8_t MPU_REG_GYRO_YOUT_H = 69;
    static constexpr uint8_t MPU_REG_GYRO_YOUT_L = 70;
    static constexpr uint8_t MPU_REG_GYRO_ZOUT_H = 71;
    static constexpr uint8_t MPU_REG_GYRO_ZOUT_L = 72;
    static constexpr uint8_t MPU_REG_USER_CTRL = 106;
    static constexpr uint8_t MPU_REG_PWR_MGMT_1 = 107;
    static constexpr uint8_t MPU_REG_PWR_MGMT_2 = 108;
    static constexpr uint8_t MPU_REG_FIFO_COUNTH = 114;
    static constexpr uint8_t MPU_REG_FIFO_COUNTL = 115;
    static constexpr uint8_t MPU_REG_FIFO_R_W = 116;
    static constexpr uint8_t MPU_REG_WHO_AM_I = 117;

};

#endif /* SRC_MPU6050_H_ */
