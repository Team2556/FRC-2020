/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "Robot.h"
#include "Debug.h"


class Drivebase {
 public:
  Drivebase(Robot * pRobot);
  void RampedDrive(float fForward, float fRotate, bool rampRotate);
  void RampedTankDrive(float fLeft, float fRight);
  void ManualDrive(bool GyroEnabled);
  void AutoDrive(float fForward, float fRotate,  bool GyroEnabled = true);
  bool DriveDistance(float distance, bool reset, bool GyroEnabled = true);

  void ManualTransmission();
  void AutoTransmission(OI::TransmissionState bTransmissionState);

  void test();

  Robot * pRobot;

  
  Debug DrivebaseDebug{"/Subsystems/Drivebase"};

  bool bRotatePrevious = false;
  int stopHoldCounter = 0;

};
