/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "Robot.h"

class ControlPanel {
 public:
  ControlPanel(Robot * pRobot);
  Robot * pRobot;
  static constexpr auto i2cPort = frc::I2C::Port::kMXP;
  rev::ColorSensorV3    ColorSensor{i2cPort};
  
  int rotations = 0;

  void ColorTest();
  bool Rotate(int spinNum);
  char DetermineColor();
  void ManualRotate(int i);
  char GetColorNeeded();
  bool RotateToColor(char givenColor = 'R');
  bool ServoUp();
  bool ServoDown();
};
