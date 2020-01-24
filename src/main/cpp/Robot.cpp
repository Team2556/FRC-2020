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
Auto              * AutoControl;
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
  TeleopMain  = new TeleopControl(this, WestDrive, CtrlPanel, pFeeder);
  AutoControl = new Auto(this, WestDrive);
}


void Robot::RobotPeriodic() 
{

}


void Robot::AutonomousInit() 
{
  MotorControl_L1.GetEncoder().SetPositionConversionFactor(1/9.6281914);
  MotorControl_L1.GetEncoder().SetPosition(0);
}

void Robot::AutonomousPeriodic() 
{
  frc::SmartDashboard::PutNumber("Encoder Pos", MotorControl_L1.GetEncoder().GetPosition());
  AutoControl->AutoMain();
}

void Robot::TeleopInit() 
{
  pShooter->rampspeed = 0;
  //MotorControl_L1.GetEncoder().SetPositionConversionFactor(1/9.6281914);
  //MotorControl_L1.GetEncoder().SetPosition(0);
  pShooter->BallsShot = 0;

}

void Robot::TeleopPeriodic() 
{
  //WestCoastDrive.ArcadeDrive(DriverCMD.fMoveForward(), DriverCMD.fRotate());
  //RobotDrive.DriveCartesian(DriverCMD.fStrafe(), DriverCMD.fMoveForward(), DriverCMD.fRotate(), 0.0);
  //pShooter->ShooterMain();
  //WestDrive->Drive();
  //pShooter->TestShoot();
  TeleopMain->TeleopMain();
  //frc::SmartDashboard::PutNumber("Encoder Pos", MotorControl_L1.GetEncoder().GetPosition());

}

void Robot::TestPeriodic()
{
  
}


#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
