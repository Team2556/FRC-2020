/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "Robot.h"

class Feeder {
 public:
  Feeder(Robot * pRobot);

  Robot * pRobot;

  void IntakeMain();
  void RunIntake(float speed);
  void BottomFeeder(float speed);
  void TopFeeder(float speed);
  void IntakeExtend(bool extended);

  Debug   FeederDebug{"/Subsystems/Feeder"};
};
