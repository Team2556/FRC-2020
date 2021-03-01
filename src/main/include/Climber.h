/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "Robot.h"

class Climber {
 public:
  Climber(Robot * pRobot);
  Robot * pRobot;

  void climbUpDown(float i);
  void rollClimber(float angle);
  void ClimbManual();

  Debug   ClimberDebug{"/Subsystems/Climber"};
};
