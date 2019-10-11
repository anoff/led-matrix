#ifndef MPU_H
  #define MPU_H
  #include <Wire.h>
#endif

namespace mpu {
  struct mpu_acceleration {
    int16_t a_x;
    int16_t a_y;
    int16_t a_z;
  };
  int setup(int mpu_addr);
  int read(int mpu_addr, mpu_acceleration *data);
}