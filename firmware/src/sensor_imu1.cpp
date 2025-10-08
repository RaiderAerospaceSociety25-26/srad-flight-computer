//* ===== IMU1 Sensor Task (USFSMAX) =====
// Brief: Polls USFSMAX (I2C) for quaternion, accel, and internal baro.
// Refs: docs/sensors/usfsmax.md, docs/signals.md
// USFSMAX Task Implementation & API
//* ===== Includes =====
#include <Arduino.h>
#include <Wire.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

#include "pins.h"
#include "app_config.h"
#include "config/sensors_config.h"
#include "logging.h"
#include "bus.h"
#include "sensor_imu1.h"
#include "rtos_mutex.h"
#include <USFSMAX.h>
//* ====================

//* ===== External Globals =====
extern float qt[2][4];
extern int16_t accADC[2][3];
extern float g_per_count;
extern float heading[2];
extern float angle[2][2];
extern int32_t baroADC[2];
//* ============================

//* ===== Module Globals =====
static I2Cdev s_i2c(&Wire);
static USFSMAX s_imu1(&s_i2c, 0);

// Data handlers
static SemaphoreHandle_t s_imu1Data_mutex = nullptr; // protect local snapshot `s_latest`
static imu1_reading_t s_latest = {0};

static constexpr float kImu1Rot[9] = {IMU1_R00, IMU1_R01, IMU1_R02,
                                      IMU1_R10, IMU1_R11, IMU1_R12,
                                      IMU1_R20, IMU1_R21, IMU1_R22};
static constexpr float kImu1QuatB2S[4] = {IMU1_Q_B2S_W, IMU1_Q_B2S_X,
                                         IMU1_Q_B2S_Y, IMU1_Q_B2S_Z};
static inline void quatMultiply(const float a[4], const float b[4], float out[4])
{
  out[0] = a[0] * b[0] - a[1] * b[1] - a[2] * b[2] - a[3] * b[3];
  out[1] = a[0] * b[1] + a[1] * b[0] + a[2] * b[3] - a[3] * b[2];
  out[2] = a[0] * b[2] - a[1] * b[3] + a[2] * b[0] + a[3] * b[1];
  out[3] = a[0] * b[3] + a[1] * b[2] - a[2] * b[1] + a[3] * b[0];
}
//* ==========================

//* ===== Task: IMU1 (USFSMAX) =====
static void task_sensor_imu1(void *param)
{
  // Enter protected setup for IMU1
  ENTER_CRITICAL(g_setup_mutex);

  // Ensure data mutex exists
  if (!s_imu1Data_mutex)
    s_imu1Data_mutex = xSemaphoreCreateMutex();

  WITH_MUTEX(g_i2c_mutex)
  {
    Wire.setClock(100000); // 100kHz for configuration
  }

  // Probe USFSMAX presence by reading a known register (FIRMWARE_ID)
  bool imu_present = false;
  uint8_t fw = 0xFF;
  for (int tries = 0; tries < 3 && !imu_present; ++tries)
  {
    WITH_MUTEX(g_i2c_mutex)
    {
      fw = s_i2c.readByte(MAX32660_SLV_ADDR, FIRMWARE_ID);
    }
    // On NACK, Wire.read() returns -1 which becomes 0xFF; 0x00 is also unlikely for a valid FW ID
    if (fw != 0xFF && fw != 0x00)
      imu_present = true;
    else
      vTaskDelay(pdMS_TO_TICKS(10));
  }

  if (!imu_present)
  {
    LOGLN("IMU1 (USFSMAX) not found (check wiring)");
    vTaskDelete(nullptr);
    return;
  }

  // Initialize USFSMAX via library routine
  s_imu1.init_USFSMAX();

  WITH_MUTEX(g_i2c_mutex)
  {
    Wire.setClock(I2C_CLOCK);
  }

  LOGLN("IMU1 (USFSMAX) initialized (library)");
  DEBUGLN("===== ^ IMU1 (USFSMAX) setup complete ^ =====\n");
  EXIT_CRITICAL(g_setup_mutex);

  TickType_t last = xTaskGetTickCount();

  //* ===== Main Task Loop =====
  static float last_pressure_pa = NAN;
  static float last_altitude_m = NAN;
  for (;;)
  {
    // Read event status `evt` to determine which sensors have new data
    uint8_t evt = 0;
    s_i2c.readBytes(MAX32660_SLV_ADDR, COMBO_DRDY_STAT, 1, &evt);

    // Uses status bits to call appropriate combo read functions
    // Bits: 0=ACC, 1=GYRO, 2=MAG, 3=BARO, 4=QUAT/EULER
    //? Note: ACC is always read as part of GYRO or MAG reads, so only request it alone if no other sensor is indicated
    uint8_t call_sensors = evt & 0x0F;
    switch (call_sensors)
    {
    case 0x01:
    case 0x02:
    case 0x03:
      s_imu1.GyroAccel_getADC();
      break;
    case 0x07:
    case 0x0B:
    case 0x0F:
      s_imu1.GyroAccelMagBaro_getADC();
      break;
    case 0x0C:
      s_imu1.MagBaro_getADC();
      break;
    case 0x04:
      s_imu1.MAG_getADC();
      break;
    case 0x08:
      s_imu1.BARO_getADC();
      break;
    default:
      // No combined sensor flags; still attempt to read accel to keep it fresh
      s_imu1.ACC_getADC();
      break;
    }

    // Check for new Quaternion/Euler data
    if (evt & 0x10)
    {
      s_imu1.getQUAT();
      s_imu1.getEULER();
    }

    //* ===== Snapshot Build =====
    imu1_reading_t r;
    r.quat[0] = qt[0][0];
    r.quat[1] = qt[0][1];
    r.quat[2] = qt[0][2];
    r.quat[3] = qt[0][3];
    r.accel_g[0] = accADC[0][0] * g_per_count;
    r.accel_g[1] = accADC[0][1] * g_per_count;
    r.accel_g[2] = accADC[0][2] * g_per_count;
    // Rotate accelerometer into rocket body frame
    {
      const float ax = r.accel_g[0];
      const float ay = r.accel_g[1];
      const float az = r.accel_g[2];
      r.accel_g[0] = kImu1Rot[0] * ax + kImu1Rot[1] * ay + kImu1Rot[2] * az;
      r.accel_g[1] = kImu1Rot[3] * ax + kImu1Rot[4] * ay + kImu1Rot[5] * az;
      r.accel_g[2] = kImu1Rot[6] * ax + kImu1Rot[7] * ay + kImu1Rot[8] * az;
    }
    // Compose orientation with static body->sensor offset
    {
      const float q_sensor[4] = {r.quat[0], r.quat[1], r.quat[2], r.quat[3]};
      float q_out[4];
      quatMultiply(q_sensor, kImu1QuatB2S, q_out);
      r.quat[0] = q_out[0];
      r.quat[1] = q_out[1];
      r.quat[2] = q_out[2];
      r.quat[3] = q_out[3];
    }
    // Internal baro sample: update only when a new BARO event was indicated
    if (evt & 0x08)
    {
      // LPS22HB output: 4096 LSB/hPa => 100/4096 Pa per count
      last_pressure_pa = ((float)baroADC[0]) * (100.0f / 4096.0f);
      last_altitude_m = 44330.0f * (1.0f - pow((last_pressure_pa / 100.0f) / SEALEVELPRESSURE_HPA, 0.1903f));
    }
    r.pressure_pa = last_pressure_pa;
    r.altitude_m = last_altitude_m;
    r.valid = true;
    WITH_MUTEX(s_imu1Data_mutex)
    {
      s_latest = r;
    }
    vTaskDelayUntil(&last, pdMS_TO_TICKS(USFS_PERIOD_MS));
  }
  //* ==========================
}
//* ================================

//* ===== Public API =====
void imu1StartTask()
{
  xTaskCreatePinnedToCore(task_sensor_imu1, "usfsmax", 4096, nullptr, TASK_PRIO_BMP390, nullptr, APP_CPU_NUM);
}

bool imu1Get(imu1_reading_t &out)
{
  bool v;
  if (s_imu1Data_mutex)
    xSemaphoreTake(s_imu1Data_mutex, portMAX_DELAY);
  out = s_latest;
  v = s_latest.valid;
  if (s_imu1Data_mutex)
    xSemaphoreGive(s_imu1Data_mutex);
  return v;
}
