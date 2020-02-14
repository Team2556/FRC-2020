/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "TeleopControl.h"



TeleopControl::TeleopControl(Robot * pRobot, Drivebase * WestDrive, ControlPanel * CtrlPanelObj, Shooter * pShooter, Feeder * pFeeder) 
    {
        this->pRobot = pRobot;   
        this->WestDrive = WestDrive;
        this->CtrlPanelObj  = CtrlPanelObj;
        this->pShooter      = pShooter;
        this->pFeeder   = pFeeder;
    }

void TeleopControl::TeleopInit()
{
    pShooter->rampspeed = 0;
    AutomationState = AutomationStateEnum::Manual;
    pShooter->SetTurretHome();
}


void TeleopControl::TeleopMain()
{
  bool BreakAuto = false;
  switch (AutomationState)
  {
  case AutomationStateEnum::BallPickup:
    frc::SmartDashboard::PutString("Teleop State", "Ball Pickup");
    BreakAuto = autoBallPickup();
    break;
  case AutomationStateEnum::Shoot:
    frc::SmartDashboard::PutString("Teleop State", "Shoot");
    BreakAuto = autoShoot();
    break;
  case AutomationStateEnum::Manual:
  default:
    frc::SmartDashboard::PutString("Teleop State", "Manual");
    ManualMain();
    break;
  }
  if(BreakAuto || pRobot->DriverCMD.BreakAuto())
  {
    AutomationState = AutomationStateEnum::Manual;
    iState = 0;
  }
  if(pRobot->DriverCMD.bTestButton(2))
  {
    AutomationState = AutomationStateEnum::BallPickup;
  }
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

void TeleopControl::ManualMain()
{
  WestDrive->ManualDrive(true);
  WestDrive->ManualTransmission();
  pFeeder->IntakeMain();
}

bool TeleopControl::autoBallPickup()
{
  WestDrive->AutoDrive(pRobot->DriverCMD.fMoveForward(), (pRobot->PixyTable->GetNumber("X", 2556) - 160)*-.005 + pRobot->DriverCMD.fRotate()*.25);
  pFeeder->RunIntake(-.75);
  return (pRobot->PixyTable->GetNumber("Time Since", 100) > 1);
}

bool TeleopControl::autoShoot()
{
  static int iCounter = 0;
  switch (iState)
  {
    case 10:
      //This state rotates the robot towards the target
      pRobot->Nav.SetCommandYaw(0);
      WestDrive->AutoDrive(0, 0);
      pShooter->ShooterDebug.PutNumber("Turret Position", pRobot->Turret_Motor.GetSelectedSensorPosition());
      pShooter->ShooterDebug.PutNumber("Turret Home", pShooter->TurretHome);
      //pShooter->GoTurretHome();
      if (fabs(pRobot->Nav.GetYawError()) < 10 && fabs(pShooter->TurretHome - pRobot->Turret_Motor.GetSelectedSensorPosition()) < 100)
      {
        iState = 20;
        iCounter = 0;
      }
      break;

    case 20:
      //ensure that the limelight has a target before moving onwards
      if(pRobot->MagicVision.HasTarget())
      {
        iState = 30;
        iCounter = 0;
      }
      //if there is no target, the limelight is given 1 second to aquire it
      else if(iCounter > 5) //TODO make this a constant
      {
        return true;
      }
      else
      {
        iCounter++;
      }
      break;

    case 30:
      // prepare to shoot
      pShooter->Aim();
      pShooter->SpinUp();

      if(fabs(pShooter->fYawPIDValue) < .05)
      {
        iCounter++;
      }
      else
      {
        iCounter = 0;
      }
      if(iCounter > 5)
      {
        iState = 40;
        iCounter = 0;
      }
      break;

    case 40:
      pShooter->ShooterGate(true);
      iState = 50;
      pShooter->Aim();
      pShooter->SpinUp();
      break;
    
    case 50:
      pFeeder->TopFeeder(.25);
      iCounter++;
      pShooter->Aim();
      pShooter->SpinUp();
      if(iCounter > 2)
      {
        iCounter = 0;
        iState = 60;
      }
      break;
    case 60:
      pFeeder->TopFeeder(0);
      iCounter++;
      pShooter->Aim();
      pShooter->SpinUp();

      if (pRobot->DriverCMD.EndShoot())
      {
        pShooter->ShooterGate(false);
        return true;
      }
      if(iCounter > 3)
      {
        iCounter = 0;
        iState = 50;
      }
      break;

    default:
      return true;
      break;
  }
  return true;
}