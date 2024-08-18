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
    MPU6050 mpu;
    ```

2. **Initialize the Sensor:**

    ```cpp
    if (mpu.initialize() == 0) {
        // Handle initialization failure
    }
    ```

3. **Read Sensor Data:**

    - **Accelerometer:**
        ```cpp
        mpu.readAccelerometer();
        float accelX = mpu.getAccelerometerX();
        float accelY = mpu.getAccelerometerY();
        float accelZ = mpu.getAccelerometerZ();
        ```

    - **Gyroscope:**
        ```cpp
        mpu.readGyroscope();
        float gyroX = mpu.getGyroX();
        float gyroY = mpu.getGyroY();
        float gyroZ = mpu.getGyroZ();
        ```

    - **Temperature:**
        ```cpp
        int16_t temperature = mpu.readTemperature();
        ```

    - **Angles:**
        ```cpp
        mpu.calculateAngles();
        float angleX = mpu.getAngleX();
        float angleY = mpu.getAngleY();
        float angleZ = mpu.getAngleZ();
        ```

### Example

Here's a simple example to initialize the MPU6050, read accelerometer data, and calculate angles:

```cpp
#include "MPU6050.h"

int main(void) {
    MPU6050 mpu;

    if (mpu.initialize() == 0) {
        // Handle error
        return -1;
    }

    while (1) {
        mpu.readAccelerometer();
        mpu.calculateAngles();

        float angleX = mpu.getAngleX();
        float angleY = mpu.getAngleY();
        float angleZ = mpu.getAngleZ();

        // Use the calculated angles
    }
}
