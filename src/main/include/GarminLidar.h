/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "frc/I2C.h"

class GarminLidar {
 public:
  GarminLidar();

  frc::I2C   Lidar{frc::I2C::Port::kOnboard, 0x62};

  float distance();
  bool Connected();
};
