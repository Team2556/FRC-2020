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
#include "NavGyro.h"
#include "Drivebase.h"
#include "Shooter.h"
#include "ControlPanel.h"
#include "Feeder.h"
#include "Climber.h"


TeleopControl     * TeleopMain;
Auto              * AutoControl;
Drivebase         * WestDrive;
Shooter           * pShooter;
ControlPanel      * CtrlPanel;
Feeder            * pFeeder;
Climber           * pClimber;

void Robot::RobotInit() 
{
  WestDrive  = new Drivebase(this);
  CtrlPanel = new ControlPanel(this);
  pFeeder = new Feeder(this);
  pShooter = new Shooter(this, pFeeder); 
  pClimber = new Climber(this);
  TeleopMain  = new TeleopControl(this, WestDrive, CtrlPanel, pShooter, pFeeder, pClimber);

  //Ultra.SetAutomaticMode(true);
  
  AutoControl = new Auto(this, WestDrive, CtrlPanel, pShooter);

  Nav.Init(false);
  //Shooter_Motor_1.SetInverted(true);
  //Shooter_Motor_2.SetInverted(true);

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
  //float fRotate = 0.0;
  //pShooter->TestShoot();
  //pShooter->ShooterMain(); 
  //TeleopMain->TeleopMain();
  pShooter->ShooterManual();
  WestDrive->ManualDrive(true);
  WestDrive->ManualTransmission();
  CtrlPanel->ManualRotate(DriverCMD.CPManualRotate());
  pFeeder->IntakeMain();
  DriverCMD.UpdateOI();
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
