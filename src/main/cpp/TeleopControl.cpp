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
    frc::SmartDashboard::PutString("Teleop State", "Manual");
    ManualMain();
    break;
  case AutomationStateEnum::CPRotate:
    frc::SmartDashboard::PutString("Teleop State", "CP Rotate");
    BreakAuto = CtrlPanelObj->Rotate(4);
    break;
  case AutomationStateEnum::CPToColor:
    frc::SmartDashboard::PutString("Teleop State", "CP Color");
    BreakAuto = CtrlPanelObj->RotateToColor();
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

  // if(pRobot->DriverCMD.BarRoll())
  // {
    frc::SmartDashboard::PutString("Test", "Works");
        //pClimber->rollClimber(pRobot->Nav.FindRoll());
  // }

    frc::SmartDashboard::PutNumber("Limelight Distance", pRobot->MagicVision.GetDistanceToTarget());

  //pShooter->TestShoot();
  //WestCoastDrive.ArcadeDrive(DriverCMD.fMoveForward(), DriverCMD.fRotate());
  //float fRotate = 0.0;
  //pShooter->TestShoot();
  //pShooter->ShooterMain(); 
  //static bool state = false;
  pRobot->DriverCMD.UpdateOI();
  SmartDashboard::PutNumber("Hood Angle", pRobot->Hood_Motor.GetSelectedSensorPosition());
  // float targetvalue = DriverCMD.fTestSelector(10);
  // SmartDashboard::PutNumber("Target Hood Angle", targetvalue);

  // if(DriverCMD.bTestButton(3))
  // {
  //   state = !state;
  // }

  // frc::SmartDashboard::PutBoolean("Auto Hood", state);
  // if(state)
  // {
  //   Hood_Motor.Set(ControlMode::Position, targetvalue);
    
  // }
  // else
  // {
  //   Hood_Motor.Set(DriverCMD.fManualHoodSpeed());
  // }
  // if(DriverCMD.AutoAim())
	// {
	// 	pShooter->Aim();
	// }
	// else
	// {
	// 	pShooter->AimManual();
	// }
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
  WestDrive->ManualDrive(true);
  WestDrive->ManualTransmission();
  pFeeder->IntakeMain();
  pClimber->ClimbManual();
  CtrlPanelObj->DetermineColor();
  pShooter->ShooterManual();
  CtrlPanelObj->ManualRotate(pRobot->DriverCMD.CPManualRotate());
  pClimber->ClimbManual();
  CtrlPanelObj->ServoUp();
}

bool TeleopControl::autoBallPickup()
{
  WestDrive->AutoDrive(pRobot->DriverCMD.fMoveForward(), (pRobot->PixyTable->GetNumber("X", 2556) - 160)*-.025 + pRobot->DriverCMD.fRotate()*.25, false);
  pFeeder->RunIntake(-.75);
  pFeeder->BottomFeeder(.5);
  return (pRobot->PixyTable->GetNumber("Time Since", 100) > 2);
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