
/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include "ControlPanel.h"
#include "Feeder.h"
#include "TeleopMain.h"
#include "Auto.h"

#include <iostream>



#include "Drivebase.h"
#include "Shooter.h"
#include "Feeder.h"

TeleopControl     * TeleopMain;
Drivebase         * WestDrive;
Shooter           * pShooter;
Feeder            * pFeeder;
ControlPanel      * CtrlPanel;


void Robot::RobotInit() 
{
  WestDrive  = new Drivebase(this);
  pFeeder = new Feeder(this);
  pShooter = new Shooter(this, pFeeder);
  CtrlPanel = new ControlPanel(this);
  TeleopMain  = new TeleopControl(this, WestDrive, CtrlPanel);
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
  pShooter->rampspeed = 0;
}

void Robot::TeleopPeriodic() 
{
  WestCoastDrive.ArcadeDrive(DriverCMD.fMoveForward(), DriverCMD.fRotate());
  //RobotDrive.DriveCartesian(DriverCMD.fStrafe(), DriverCMD.fMoveForward(), DriverCMD.fRotate(), 0.0);
  //pShooter->ShooterMain();
  //WestDrive->Drive();
  //pShooter->TestShoot();
  //TeleopMain->TeleopMain();
}

void Robot::TestPeriodic()
{
  
}


#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif

