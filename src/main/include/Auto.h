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
#include "TeleopControl.h"
#include "Debug.h"

class Auto {
 public:
  Auto(Robot * pRobot, Drivebase * WestDrive, ControlPanel * CtrlPanelObj, Shooter * pShooter, TeleopControl * TeleopMain, Feeder * pFeeder);

   Robot            * pRobot;
   Drivebase        * WestDrive;
   ControlPanel     * CtrlPanelObj;
   Shooter          * pShooter;
   TeleopControl    * TeleopMain;
   Feeder * pFeeder;

  float currentPosition = 0;//pRobot->m_encoder.GetPosition();

  void AutoInit();
  void AutoPeriodic();
  float CurrentAutoPosition();
  bool autoShoot(float distance, bool intake = false);

  void Auto1(); // far right side of field (from our perspective,) in line with our trench 3 ball

  int iState = 0; //track state in the state machine
  int iShootState = 0;
  int iCounter = 0; // counter used in various actions that neet timing
  bool bStateDone = false; // used in some states if the return from an active function signals the end of a state 

  Debug   AutoDebug{"Auto"};
};
