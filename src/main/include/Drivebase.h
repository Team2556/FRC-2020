/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "Robot.h"

class Drivebase {
 public:
  Drivebase(Robot * pRobot);
  void Drive();
  void ManualDrive(float fForward, float fRotate);
  void AutomaticDrive(float fForward, float fRotate);
  void AutoDrive(float fForward, float fRotate, OI::TransmissionState bTransmissionState);

  Robot * pRobot;

  


};
