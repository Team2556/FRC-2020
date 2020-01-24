/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "Robot.h"
#include "Drivebase.h"
#include "ControlPanel.h"
#include "Feeder.h"

class TeleopControl {
 public:
  TeleopControl(Robot * pRobot, Drivebase * WestDrive, ControlPanel * CtrlPanelObj, Feeder * pFeeder);

   Robot           * pRobot;
   Drivebase       * WestCoast;
   ControlPanel    * CtrlPanelObj;
   Feeder * pFeeder;
  
  void TeleopMain();

};
