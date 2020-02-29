/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "frc/WPILib.h"
#include "frc/smartdashboard/Smartdashboard.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"
#include <iostream>



class Limelight {
 public:
  Limelight();

  double Skew();
  double Area();
  double VerticalOffset();
  double HorizontalOffset();
  void SetValue(std::string Key, int Value);
  double Width();
  double Height();
  double Angle();
  double Ratio();
  bool HasTarget();
  void TopRow();
  void GetDrive(float * fForward, float *fStrafe, float * fRotate, bool * bFOD);
  double NewRatio();
  float GetDistanceToTarget();


  double results[4][2] = {{1,2}, {3,4}, {1,2}, {3,4}};
  std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
};