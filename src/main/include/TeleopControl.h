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
#include "Shooter.h"
#include "Feeder.h"
#include "Climber.h"

class TeleopControl {
 public:
  TeleopControl(Robot * pRobot, Drivebase * WestDrive, ControlPanel * CtrlPanelObj, Shooter * pShooter, Feeder * pFeeder, Climber * pClimber);

   Robot           * pRobot;
   Drivebase       * WestDrive;
   ControlPanel    * CtrlPanelObj;
   Shooter         * pShooter;
   Feeder          * pFeeder;
   Climber         * pClimber;
  
  void TeleopInit();
  void TeleopMain();
  void TeleopTest();

  void TeleopDrive();

  void ManualMain();
  bool autoBallPickup();
  bool autoShoot();

  bool bAllowManualDrive;

  enum AutomationStateEnum{Manual, BallPickup, Shoot};

  int iState = 0;

  AutomationStateEnum AutomationState;     

};
