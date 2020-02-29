/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "TeleopControl.h"



TeleopControl::TeleopControl(Robot * pRobot, Drivebase * WestDrive, ControlPanel * CtrlPanelObj, Shooter * pShooter, Feeder * pFeeder, Climber * pClimber) 
    {
        this->pRobot = pRobot;   
        this->WestDrive = WestDrive;
        this->CtrlPanelObj  = CtrlPanelObj;
        this->pShooter      = pShooter;
        this->pFeeder   = pFeeder;
        this->pClimber      = pClimber;
    }

void TeleopControl::TeleopInit()
{
    pShooter->rampspeed = 0;
}


void TeleopControl::TeleopMain()
{
    //pRobot->DriverCMD.UpdateOI();
    //pFeeder->IntakeMain();
    //pRobot->WestCoastDrive.ArcadeDrive(pRobot->DriverCMD.fMoveForward(), pRobot->DriverCMD.fRotate());
  //RobotDrive.DriveCartesian(DriverCMD.fStrafe(), DriverCMD.fMoveForward(), DriverCMD.fRotate(), 0.0);
  if (!pShooter->ShooterMain())
  {
    //only drive if we arent actively shooting
    TeleopDrive();
  }

  if(pRobot->DriverCMD.CPManualRotate() == 1) {
    CtrlPanelObj->ManualRotate(1);
  }
  // if(pRobot->DriverCMD.BarRoll())
  // {
    frc::SmartDashboard::PutString("Test", "Works");
        //pClimber->rollClimber(pRobot->Nav.FindRoll());
  // }

    frc::SmartDashboard::PutNumber("Limelight Distance", pRobot->MagicVision.GetDistanceToTarget());

  //pShooter->TestShoot();
}

void TeleopControl::TeleopDrive()
{
  static bool ResetDistance = false;
  if(pRobot->DriverCMD.bTestButton(7))
  {
    bAllowManualDrive = false;
    ResetDistance = true;
  }

  if(bAllowManualDrive)
  {
    WestDrive->ManualDrive(true);
    WestDrive->ManualTransmission();
  }
  else
  {
    bAllowManualDrive = WestDrive->DriveDistance(10, ResetDistance);
    ResetDistance = false;
  }
  
  frc::SmartDashboard::PutBoolean("Manual Drive", bAllowManualDrive);
}

