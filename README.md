# MPU6050 Driver for STM32

This repository contains an object-oriented C++ driver for the MPU6050 sensor, designed to run on STM32 microcontrollers. The driver allows for easy interfacing with the MPU6050 to read accelerometer and gyroscope data, calculate angles, and retrieve temperature readings.

## Features

- **Object-Oriented Design:** Encapsulates MPU6050 functionality in a C++ class, improving modularity and reusability.
- **I2C Communication:** Utilizes HAL I2C functions for communication with the MPU6050.
- **Accelerometer and Gyroscope Data:** Provides functions to read raw accelerometer and gyroscope values.
- **Angle Calculation:** Implements functions to calculate angles based on accelerometer data.
- **Temperature Reading:** Allows retrieval of temperature data from the sensor.

## Project Structure

- `MPU6050.h`: Header file containing the class definition and constants for the MPU6050.
- `MPU6050.cpp`: Implementation file containing the method definitions and logic for communicating with the sensor.

## Getting Started

### Prerequisites

- STM32 microcontroller
- MPU6050 sensor module
- STM32CubeIDE or any other ARM GCC-based development environment
- Basic understanding of I2C communication protocol

### Installation

1. Clone the repository:
    ```bash
    git clone https://github.com/Emrecanbl/MPU6050-STM32-Driver.git
    ```
2. Add the `MPU6050.h` and `MPU6050.cpp` files to your STM32 project.

3. Include the `MPU6050.h` in your main file:
    ```cpp
    #include "MPU6050.h"
    ```

### Usage

1. **Instantiate the MPU6050 Object:**

    ```cpp
  MPU6050 Sensor;
    ```

2. **Initialize the Sensor:**

    ```cpp
  while (Sensor.MPU_Init()!=1){
	 HAL_Delay(100);
  }
    ```

3. **Read Sensor Data:**

    - **Accelerometer:**
        ```cpp
        mpu.Accelerometer_Read();
	  Accelerometer_X = Sensor.Read_Accelerometer_X();
	  Accelerometer_Y = Sensor.Read_Accelerometer_Y();
	  Accelerometer_Z = Sensor.Read_Accelerometer_Z();
        ```

    - **Gyroscope:**
        ```cpp
        mpu.Gyroscope_Read();
	  Gyro_X = Sensor.Read_Gyro_X();
	  Gyro_Y = Sensor.Read_Gyro_Y();
	  Gyro_Z = Sensor.Read_Gyro_Z();
        ```

    - **Temperature:**
        ```cpp
        Temp = Sensor.Temp_Read();
        ```

    - **Angles:**
        ```cpp
	  Angle_X = Sensor.Read_Angle_X();
	  Angle_Y = Sensor.Read_Angle_Y();
	  Angle_Z = Sensor.Read_Angle_Z();
        ```
