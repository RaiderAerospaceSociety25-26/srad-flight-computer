// Sensor configuration (ranges, I2C speeds, calibration toggles)
// NOTE: Scaffold only — current values come from app_config.h and device modules
#pragma once

// Future home for:
// - I2C clock config per device
// - Default IMU ranges and LPF
// - Sea level pressure default for altitude
// Default sea level pressure for altitude calculations (hPa)
#ifndef SEALEVELPRESSURE_HPA
#define SEALEVELPRESSURE_HPA (1012.0)
#endif

// IMU1 (USFSMAX) fixed rotation between sensor axes and rocket body frame
// Define both a 3x3 rotation matrix (sensor -> body) and quaternion (body -> sensor)
#ifndef IMU1_R00
#define IMU1_R00 0.0f
#define IMU1_R01 1.0f
#define IMU1_R02 0.0f
#define IMU1_R10 -1.0f
#define IMU1_R11 0.0f
#define IMU1_R12 0.0f
#define IMU1_R20 0.0f
#define IMU1_R21 0.0f
#define IMU1_R22 1.0f
#endif

#ifndef IMU1_Q_B2S_W
#define IMU1_Q_B2S_W 0.70710678f
#define IMU1_Q_B2S_X 0.0f
#define IMU1_Q_B2S_Y 0.0f
#define IMU1_Q_B2S_Z 0.70710678f
#endif

// IMU2 (MPU6050) orientation mapping to rocket body frame
// Define a 3x3 rotation matrix R such that: v_body = R * v_sensor
// Default matches flight orientation (sensor long edge horizontal, short edge down)
#ifndef IMU2_R00
#define IMU2_R00 0.0f
#define IMU2_R01 1.0f
#define IMU2_R02 0.0f
#define IMU2_R10 -1.0f
#define IMU2_R11 0.0f
#define IMU2_R12 0.0f
#define IMU2_R20 0.0f
#define IMU2_R21 0.0f
#define IMU2_R22 1.0f
#endif
