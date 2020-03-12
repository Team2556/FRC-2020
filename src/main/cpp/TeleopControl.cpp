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
    AutomationState = AutomationStateEnum::Manual;
    pShooter->SetTurretHome();
    pRobot->Nav.SetCommandYawToCurrent();
    //MotorControl_L1.GetEncoder().SetPositionConversionFactor(1/9.6281914);
    //MotorControl_L1.GetEncoder().SetPosition(0);   
      pRobot->Shooter_Motor_1.SetSelectedSensorPosition(0);    

  
  pShooter->BallsShot = 0;
    
}


void TeleopControl::TeleopMain()
{
  pRobot->DriverCMD.UpdateOI();

  bool BreakAuto = false;
  switch (AutomationState)
  {
  case AutomationStateEnum::BallPickup:
    frc::SmartDashboard::PutString("Teleop State", "Ball Pickup");
    BreakAuto = autoBallPickup(false);
    break;
  case AutomationStateEnum::Shoot:
    frc::SmartDashboard::PutString("Teleop State", "Shoot");
    BreakAuto = autoShoot();
    break;
  case AutomationStateEnum::Manual:
    frc::SmartDashboard::PutString("Teleop State", "Manual");
    ManualMain();
    break;
  case AutomationStateEnum::CPRotate:
    frc::SmartDashboard::PutString("Teleop State", "CP Rotate");
    BreakAuto = CtrlPanelObj->RotationControl(false);
    break;
  default:
    frc::SmartDashboard::PutString("Teleop State", "Error");
    break;
  }
  if(BreakAuto || pRobot->DriverCMD.BreakAuto())
  {
    AutomationState = AutomationStateEnum::Manual;
    iState = 20;
  }
  if(false)//pRobot->DriverCMD.bTestButton(2))
  {
    AutomationState = AutomationStateEnum::BallPickup;
    autoBallPickup(true);
  }
  if(pRobot->DriverCMD.CPRotate())
  {
    AutomationState = AutomationStateEnum::CPRotate;
    CtrlPanelObj->RotationControl(true);
  }
  if(pRobot->DriverCMD.bTestButton(8))
  {
    frc::SmartDashboard::PutBoolean("Shoot start", true);
    iBallsToShoot = frc::SmartDashboard::GetNumber("Balls To Shoot", 0);
    AutomationState = AutomationStateEnum::Shoot;
  }
  else
  {
    frc::SmartDashboard::PutBoolean("Shoot start", false);
  }
  if(pRobot->DriverCMD.CPRotate())
  {
    AutomationState = AutomationStateEnum::CPRotate;
  }
  if(pRobot->DriverCMD.CPToColor())
  {
    AutomationState = AutomationStateEnum::CPToColor;
  }

 

  
  pShooter->ShooterDebug.PutNumber("Hood Angle", pRobot->Hood_Motor.GetSelectedSensorPosition());
  pShooter->ShooterDebug.PutNumber("Target Power", pRobot->DriverCMD.speedMult);
  frc::SmartDashboard::PutNumber("Distance", pRobot->ShooterDistance.distance);
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
  WestDrive->ManualDrive(false);
  WestDrive->ManualTransmission();
  pFeeder->IntakeMain();
  CtrlPanelObj->DetermineColor();
  pShooter->ShooterManual();
  CtrlPanelObj->ManualRotate(pRobot->DriverCMD.CPManualRotate());
  pClimber->ClimbManual();
  CtrlPanelObj->ServoUp();
}

bool TeleopControl::autoBallPickup(bool reset)
{
  static int prevX = 0;
  if(reset)
  {
    if(pRobot->PixyTable->GetBoolean("Ball Tracked", false) == false)
    {
      return true;
    }
    else
    {
      prevX = pRobot->PixyTable->GetNumber("X", 2556);
      return false;
    }
  
  }
  else
  {
    bool ended;// (currX - 160)*-.005
    int currX = (pRobot->PixyTable->GetNumber("X", 2556));
    float fRotate = (currX - 160)*-.0065 - pRobot->DriverCMD.sign(currX-160) * .17;
    float MaxRotate = .5;

    if(fRotate > MaxRotate)
    {
      fRotate = MaxRotate;
    }
    else if(fRotate < -MaxRotate)
    {
      fRotate = -MaxRotate;
    }
    WestDrive->AutoDrive(pRobot->DriverCMD.fMoveForward(), fRotate, false);

    pFeeder->RunIntake(-.75);
    pFeeder->BottomFeeder(.5);
    ended = (pRobot->PixyTable->GetNumber("Time Since", 100) > 2) || fabs(currX - prevX) > 40;
    prevX = currX;
    return ended;
  }

}

bool TeleopControl::autoShoot(bool intake)
{
  static int iCounter = 0;
  float velocity_error;
  frc::SmartDashboard::PutNumber("Shoot State", iState);
  pShooter->CountBalls();
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
      else if(iCounter > 5) //TODO make this a variable
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
      velocity_error = pShooter->SpinUpDistance(-1, false);
      pShooter->AutoHood();
      pShooter->ShooterDebug.PutNumber("Velocity Error", velocity_error);

      
      if(fabs(pShooter->fYawPIDValue) < .05 && fabs(velocity_error) < 700 )
      {
        iCounter++;
      }
      else
      {
        iCounter = 0;
      }
      //wait until turret is stable for 2 iterations (40 milliseconds) before moving on 
      if(iCounter > 2)
      {
        iState = 40;
        iCounter = 0;
      }
      break;

    case 40:
      // open gate
      pShooter->ShooterGate(true);
      iState = 50;
      pShooter->Aim();
      pShooter->SpinUpDistance();
      pShooter->AutoHood();
      break;
    
    //Case 50/60 
    //turn on and off the feeder in short increments to fire balls sequentually
    case 50:
      pFeeder->TopFeeder(-.7);
      pFeeder->BottomFeeder(.8);
      pFeeder->RunIntake(intake);
      iCounter++;
      pShooter->Aim();
      velocity_error = pShooter->SpinUpDistance();
      pShooter->AutoHood();
      // if(iBallsToShoot - pShooter->BallsShot <= 0)
      // {
      //   iCounter = 0;
      //   iState = 100;
      // }
      if(pRobot->DriverCMD.EndShoot())
      {
        iCounter = 0;
        iState = 100;
      }
      if(fabs(velocity_error) > 700)
      {
        iState = 30;
        pFeeder->RunIntake(0);
        pFeeder->BottomFeeder(.4);
        pFeeder->TopFeeder(-.35);
      }
      break;

    case 60:
      pFeeder->TopFeeder(.5);
      pFeeder->BottomFeeder(-.5);
      pFeeder->RunIntake(intake);
      iCounter++;
      pShooter->Aim();
      pShooter->SpinUp();

  
      if(iCounter > 1)
      {
        iCounter = 0;
        iState = 50;
      }

      if (pRobot->DriverCMD.EndShoot())
      {
        iCounter = 0;
        iState = 100;
      }
      break;

    default:
    case 100:
      pShooter->ShooterGate(false);
      pShooter->StopShoot();
      pFeeder->BottomFeeder(0);
      pFeeder->TopFeeder(0);
      pFeeder->RunIntake(0);
      return true;
      break;
  }
  return false;
}