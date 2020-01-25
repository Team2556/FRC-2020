/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
<<<<<<< HEAD
#include "Robot.h"
#include "ControlPanel.h"
=======
>>>>>>> 73a6c05fe6aaf99cdf24b646ced8ddffe09b6e10
#include "Drivebase.h"
#include "Robot.h"

class Auto {
 public:
<<<<<<< HEAD
  Auto(Robot * pRobot, Drivebase * WestDrive, ControlPanel * CtrlPanelObj, Shooter * pShooter);

   Robot           * pRobot;
   Drivebase       * WestCoast;
   ControlPanel    * CtrlPanelObj;
   Shooter           * pShooter;


  float currentPosition = pRobot->m_encoder.GetPosition();

  void AutoInit();
  void AutoPeriodic();
=======
  Auto(Robot * pRobot, Drivebase  * WestDrive);
  void AutoMain();
>>>>>>> 73a6c05fe6aaf99cdf24b646ced8ddffe09b6e10
  
  Drivebase       * WestDrive;
  Robot           * pRobot;


};
