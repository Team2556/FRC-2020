
/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include "TeleopControl.h"
#include "Auto.h"

#include <iostream>

#include "Drivebase.h"
#include "Shooter.h"
#include "Feeder.h"
#include "ControlPanel.h"
#include "Feeder.h"

TeleopControl     * pTeleop;
Drivebase         * WestDrive;
Shooter           * pShooter;
Feeder            * pFeeder;
ControlPanel      * CtrlPanel;
Auto              * AutoCtrl;


void Robot::RobotInit() 
{
  WestDrive  = new Drivebase(this);
  pFeeder = new Feeder(this);
  pShooter = new Shooter(this, pFeeder);
  CtrlPanel = new ControlPanel(this);
  pTeleop  = new TeleopControl(this, WestDrive, CtrlPanel, pShooter);
  AutoCtrl = new Auto(this, WestDrive, CtrlPanel, pShooter);
}


void Robot::RobotPeriodic() 
{

}


void Robot::AutonomousInit() 
{
  
}

void Robot::AutonomousPeriodic() 
{

}

void Robot::TeleopInit() 
{
  AutoCtrl->AutoInit();
  //pTeleop->TeleopInit();
}

void Robot::TeleopPeriodic() 
{
  AutoCtrl->AutoPeriodic();
  //pTeleop->TeleopMain();
}

void Robot::TestPeriodic()
{
  
}


#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif

