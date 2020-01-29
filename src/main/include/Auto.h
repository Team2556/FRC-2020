/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "Robot.h"
#include "ControlPanel.h"
#include "Drivebase.h"
#include "Shooter.h"
#include "Feeder.h"

class Auto {
 public:
  Auto(Robot * pRobot, Drivebase * WestDrive, ControlPanel * CtrlPanelObj, Shooter * pShooter);

   Robot           * pRobot;
   Drivebase       * WestDrive;
   ControlPanel    * CtrlPanelObj;
   Shooter           * pShooter;

  float currentPosition = pRobot->m_encoder.GetPosition();

  void AutoInit();
  void AutoPeriodic();
  float CurrentAutoPosition();

};
