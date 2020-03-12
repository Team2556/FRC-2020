/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"

class Debug {
 public:
  Debug(std::string name);

  void PutString(std::string key, std::string value);
  void PutNumber(std::string key, float value);
  void PutBoolean(std::string key, bool value);


  std::shared_ptr<NetworkTable> table;
};
