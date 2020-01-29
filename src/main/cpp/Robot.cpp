
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
#include "ControlPanel.h"
#include "Feeder.h"

TeleopControl     * TeleopMain;
Auto              * AutoControl;
Drivebase         * WestDrive;
Shooter           * pShooter;
ControlPanel      * CtrlPanel;
Feeder            * pFeeder;



void Robot::RobotInit() 
{
  WestDrive  = new Drivebase(this);
  pShooter = new Shooter(this);  
  CtrlPanel = new ControlPanel(this);
  pFeeder = new Feeder(this);
  TeleopMain  = new TeleopControl(this, WestDrive, CtrlPanel, pShooter, pFeeder);

  //Ultra.SetAutomaticMode(true);
  
  AutoControl = new Auto(this, WestDrive, CtrlPanel, pShooter);

  Nav.Init(false);

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
  Nav.SetCommandYawToCurrent();
  pShooter->rampspeed = 0;
  //MotorControl_L1.GetEncoder().SetPositionConversionFactor(1/9.6281914);
  //MotorControl_L1.GetEncoder().SetPosition(0);
  pShooter->BallsShot = 0;

}

void Robot::TeleopPeriodic() 
{
  //WestCoastDrive.ArcadeDrive(DriverCMD.fMoveForward(), DriverCMD.fRotate());
  //RobotDrive.DriveCartesian(DriverCMD.fStrafe(), -DriverCMD.fMoveForward(), -DriverCMD.fRotate(), 0.0);
  pShooter->ShooterMain(); 
}

void Robot::TestPeriodic()
{
}

void Robot::DisabledInit()
{

}

void Robot::DisabledPeriodic()
{

}
#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif

