/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Auto.h"
#include <frc/WPILib.h>


Auto::Auto(Robot * pRobot, Drivebase * WestDrive, ControlPanel * CtrlPanelObj, Shooter * pShooter, TeleopControl * TeleopMain, Feeder * pFeeder) 
{
    this->pRobot        = pRobot;   
    this->WestDrive     = WestDrive;
    this->CtrlPanelObj  = CtrlPanelObj;
    this->pShooter      = pShooter;
    this->TeleopMain    = TeleopMain;
    this->pFeeder       = pFeeder;
}


void Auto::AutoInit()
{
    pRobot->m_encoder.SetPosition(0);
    pRobot->AutoMode = pRobot->AutoChooser.GetSelected();
    pRobot->Nav.SetCommandYawToCurrent();
    iCounter = 0;
    iState = 0;
}

void Auto::AutoChooser()
{
    if(pRobot->AutoMode == pRobot->Auto1)
    {
        AutoOne();
    }
    else if(pRobot->AutoMode == pRobot->Auto2)
    {
        AutoTwo();
    }
    else if(pRobot->AutoMode == pRobot->Auto3)
    {
        AutoThree();
    }
}

void Auto::AutoPeriodic()
{
    AutoDebug.PutString("Auto Version", pRobot->AutoChooser.GetSelected());
    AutoDebug.PutNumber("Encoder Position", currentPosition);
    AutoChooser();
    AutoDebug.PutNumber("Auto Time", 15 - frc::DriverStation::GetInstance().GetMatchTime());
    AutoDebug.PutNumber("Distance Traveled", pRobot->m_encoder.GetPosition());
    AutoDebug.PutNumber("Distance", pRobot->ShooterDistance.distance); 
    AutoDebug.PutNumber("Shoot Set Percent", pRobot->Shooter_Motor_1.GetMotorOutputPercent());
}

float Auto::CurrentAutoPosition()
{

    return -pRobot->m_encoder.GetPosition();
}

void Auto::AutoOne()
{
    float fForward = 0.0;
    float fRotate = 0.0;
    bool  bGyroEnabled = true;
    AutoDebug.PutNumber("State", iState);
    AutoDebug.PutNumber("Counter", iCounter);
    AutoDebug.PutNumber("Encoder Distance", CurrentAutoPosition());
    switch (iState)
    {
        case 0:
            iState  = 10;
            
            iCounter = 0;
            iShootState = 20;
        break;

        case 10: // shoot preloaded balls
            bStateDone = this->autoShoot(pRobot->ShooterDistance.distance, -750, false);

            if (iShootState == 50)
            {
                iCounter++;
            }
            if(iCounter >= 50)
            {
                iShootState = 100;
            }
            if (bStateDone)
            {
                iState = 20;
                iCounter = 0;
                pShooter->ShooterGate(false);
            }
        break;
        
        case 20:
            fForward = -.75;
            WestDrive->AutoDrive(fForward, 0.0, true);
            WestDrive->AutoTransmission(OI::TransmissionState::Low);
            pFeeder->IntakeExtend(false);
            pFeeder->RunIntake(-1);
            pFeeder->BottomFeeder(.8);
            pFeeder->TopFeeder(-.5);
            pShooter->AimNeo();
            pShooter->SpinUpNEODistance(-1, false);
            pShooter->AutoHood();
            if(fabs(15.5-CurrentAutoPosition())< .1 )
            {
                iState  = 35;
                iCounter = 0;
                iShootState = 20;
            }
        break;

        case 30:
            fForward = -.7;

            if(pRobot->PixyTable->GetBoolean("Ball Tracked", false))
            {
                if(pRobot->PixyTable->GetNumber("Y", 0) >180 )
                {
                    iCounter = 0;
                }
                else
                {
                    iCounter++;
                }

                if(iCounter > 100)
                {
                    bGyroEnabled = false;
                    fRotate = (pRobot->PixyTable->GetNumber("X", 2556) - 160)*-.025;
                }
                
            }
            else
            {
                fRotate = 0.0;
            }
            //shooter
            pShooter->Aim();
            pShooter->SpinUpDistance(850, false);
            pShooter->AutoHood();
            //drive
            WestDrive->AutoDrive(fForward, fRotate, bGyroEnabled);
            WestDrive->AutoTransmission(OI::TransmissionState::Low);
            pFeeder->IntakeExtend(false);
            pFeeder->RunIntake(-1);
            pFeeder->BottomFeeder(.8);
            pFeeder->TopFeeder(-.5);
            if(fabs(15.0-CurrentAutoPosition())< .1 )
            {
                iState  = 40;
                iCounter = 0;
                iShootState = 20;
            }
        break;

        case 35:
            pFeeder->RunIntake(0);
            pFeeder->BottomFeeder(0);
            pFeeder->TopFeeder(0);

            iState = 40;
            iCounter = 0;
        break;
        
        case 37:

        bStateDone = this->autoShoot(pRobot->ShooterDistance.distance, -825);
        pFeeder->RunIntake(-1);
        pFeeder->BottomFeeder(.8);
        pFeeder->TopFeeder(-.5);

        iCounter++;

        
        if(iCounter>1)
        {
            iState = 40;
            iCounter = 0;
            pFeeder->RunIntake(0);
            pFeeder->BottomFeeder(0);
            pFeeder->TopFeeder(0);
        }


        break;

        
        case 40:
            bStateDone = this->autoShoot(pRobot->ShooterDistance.distance + 40, -850, true);

        //     if (iShootState == 50)
        //     {
        //         iCounter++;
        //     }
        //     if(iCounter >= 30)
        //     {
        //         iShootState = 100;
        //     }
        //     if (bStateDone)
        //     {
        //         iState = 100;
        //         iCounter = 0;
        //     }
         break;
        case 100:
        default:
            WestDrive->AutoDrive(0.0, 0.0);
        break;
    }
}

void Auto::AutoTwo()
{

}

void Auto::AutoThree()
{
  
}

bool Auto::autoShoot(float distance, float hoodVal, bool intake)
{
  static int iShootCounter = 0;
  float velocity_error;
  AutoDebug.PutNumber("Shoot State", iShootState);
  pShooter->CountBalls();
  switch (iShootState)
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
        iShootState = 20;
        iShootCounter = 0;
      }
      break;

    case 20:
      //ensure that the limelight has a target before moving onwards
      if(pRobot->MagicVision.HasTarget())
      {
        iShootState = 30;
        iShootCounter = 0;
      }
      //if there is no target, the limelight is given 1 second to aquire it
      else if(iShootCounter > 5) //TODO make this a variable
      {
        return true;
      }
      else
      {
        iShootCounter++;
      }
      break;

    case 30:
      // prepare to shoot
      pShooter->AimNeo();
      velocity_error = pShooter->SpinUpNEODistance(distance, false);
      pRobot->Hood_Motor.Set(ControlMode::Position, hoodVal);
      //pShooter->AutoHood(distance + 20);
      pShooter->ShooterDebug.PutNumber("Velocity Error", velocity_error);

      
      if(fabs(pShooter->fYawPIDValue) < .05 && fabs(velocity_error) < 500 )
      {
        iShootCounter++;
      }
      else
      {
        iShootCounter = 0;
      }
      //wait until turret is stable for 2 iterations (40 milliseconds) before moving on 
      if(iShootCounter > 2)
      {
        iShootState = 40;
        iShootCounter = 0;
      }
      break;

    case 40:
      // open gate
      pShooter->ShooterGate(true);
      iShootState = 50;
      pShooter->AimNeo();
      pShooter->SpinUpNEODistance();
      //pShooter->AutoHood(distance + 20);
      pRobot->Hood_Motor.Set(ControlMode::Position, hoodVal);
      break;
    
    //Case 50/60 
    //turn on and off the feeder in short increments to fire balls sequentually
    case 50:
      pFeeder->TopFeeder(-.7);
      pFeeder->BottomFeeder(.8);
      pFeeder->RunIntake(-intake);
      iShootCounter++;
      pShooter->AimNeo();
      velocity_error = pShooter->SpinUpDistance(distance, false);
      pRobot->Hood_Motor.Set(ControlMode::Position, hoodVal);
      //pShooter->AutoHood(distance + 20);
      
      
      if(fabs(velocity_error) > 400)
      {
        iShootState = 30;
        pFeeder->RunIntake(0);
        pFeeder->BottomFeeder(.4);
        pFeeder->TopFeeder(-.35);
      }
      break;

    case 60:
      pFeeder->TopFeeder(.5);
      pFeeder->BottomFeeder(-.5);
      pFeeder->RunIntake(-intake);
      iShootCounter++;
      pShooter->Aim();
      pShooter->SpinUp();

  
      if(iShootCounter > 1)
      {
        iShootCounter = 0;
        iShootState = 50;
      }

      if (pRobot->DriverCMD.EndShoot())
      {
        iShootCounter = 0;
        iShootState = 100;
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