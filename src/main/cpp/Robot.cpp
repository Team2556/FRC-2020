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

void Robot::SwitchCamera()
{
  std::string camera = DriverCMD.GetCamera();
  if (camera != "-1")
  {
    CameraTable->PutString("selected", camera);
  }
}

void Robot::RobotInit() 
{
  Intake_Motor.SetInverted(true);
  WestDrive  = new Drivebase(this);
  CtrlPanel = new ControlPanel(this);
  pFeeder = new Feeder(this);
  pShooter = new Shooter(this, pFeeder); 
  pClimber = new Climber(this);
  TeleopMain  = new TeleopControl(this, WestDrive, CtrlPanel, pShooter, pFeeder, pClimber);

  //Ultra.SetAutomaticMode(true);
  
  AutoControl = new Auto(this, WestDrive, CtrlPanel, pShooter, TeleopMain, pFeeder);

  Nav.Init(false);
  //Shooter_Motor_1.SetInverted(true);
  //Shooter_Motor_2.SetInverted(true);


    AutoChooser.AddOption(Auto1, Auto1);
    AutoChooser.AddOption(Auto2, Auto2);
    AutoChooser.AddOption(Auto3, Auto3);
    frc::SmartDashboard::PutData("Auto Selector", &AutoChooser);

  MotorControl_L1.GetEncoder().SetPositionConversionFactor(1/9.6281914);
  MotorControl_L1.GetEncoder().SetPosition(0);
}


void Robot::RobotPeriodic() 
{ 
  static int icounter = 0;
  icounter++;
  if(!DriverCMD.bTestButton(6) && (icounter%2) == 0)
  {
    ShooterDistance.IterativeDistance();
    ShooterDistance.LidarDebug.PutBoolean("Measuring", true);
  }
  else
  {
    ShooterDistance.LidarDebug.PutBoolean("Measuring", false);
  }
  ShooterDistance.dioReset.Set(!DriverCMD.bTestButton(7));
  ShooterDistance.LidarDebug.PutBoolean("Reseting", ShooterDistance.dioReset.Get());
  Nav.UpdateValues();
  //SwitchCamera();
}


void Robot::AutonomousInit() 
{
  AutoControl->AutoInit();
}

void Robot::AutonomousPeriodic() 
{
  AutoControl->AutoPeriodic();
}

void Robot::TeleopInit() 
{
  TeleopMain->TeleopInit();  
}

void Robot::TeleopPeriodic() 
{
  TeleopMain->TeleopMain();
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
