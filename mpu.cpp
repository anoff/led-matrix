#include "mpu.h"

namespace mpu {
  int setup(int mpu_addr) {
    int res;
    Wire.begin();
    Wire.beginTransmission(mpu_addr);
    res = Wire.write(0x6B); // PWR_MGMT_1
    if (res != 0) return res;
    Wire.write(0); // wake up MPU-6050
    res = Wire.endTransmission(true);
    return res;
  }
  int16_t read(int mpu_addr, mpu_acceleration *data) {
    int res;
    int16_t accelerometer_x, accelerometer_y, accelerometer_z;
    Wire.beginTransmission(mpu_addr);
    res = Wire.write(0x3B); // start reading the a_x register (2 bytes per reg)
    if (res != 0) return res;
    res = Wire.endTransmission(false); // do not release I2C bus
    Wire.requestFrom(mpu_addr, 7*2, true); // request data
    
    accelerometer_x = Wire.read()<<8 | Wire.read(); // 0x3B (ACCEL_XOUT_H), 0x3C (ACCEL_XOUT_L)
    data->a_y = Wire.read()<<8 | Wire.read(); // 0x3D (ACCEL_YOUT_H), 0x3E (ACCEL_YOUT_L)
    data->a_z = Wire.read()<<8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H), 0x40 (ACCEL_ZOUT_L)
    
    return accelerometer_x;
  }
}
