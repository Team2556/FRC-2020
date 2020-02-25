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
    //pRobot->m_encoder.SetPosition(0);
}

void Auto::AutoPeriodic()
{
    //WestDrive->AutoDrive((10-pRobot->MotorControl_L1.GetEncoder().GetPosition())*.4, 0);
    frc::SmartDashboard::PutNumber("Encoder Position", CurrentAutoPosition());
}



float Auto::CurrentAutoPosition()
{
    return -pRobot->m_encoder.GetPosition();
}

void Auto::Auto1()
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
            iState  = 30;
            iCounter = 0;
            TeleopMain->iState = 20;
        break;

        case 10: // shoot preloaded balls
            bStateDone = TeleopMain->autoShoot();

            if (TeleopMain->iState == 50)
            {
                iCounter++;
            }
            if(iCounter >= 125)
            {
                TeleopMain->iState = 100;
            }
            if (bStateDone)
            {
                iState = 20;
                iCounter = 0;
            }
        break;
        
        case 20:
            fForward = -.7;
            WestDrive->AutoDrive(fForward, 0.0);
            WestDrive->AutoTransmission(OI::TransmissionState::Low);
            pFeeder->IntakeExtend(false);
            pFeeder->RunIntake(-.5);
            pFeeder->BottomFeeder(.5);
            pFeeder->TopFeeder(-.5);
            if(fabs(15-CurrentAutoPosition())< .1 )
            {
                iState  = 100;
            }
        break;

        case 30:
            fForward = -.6;

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

            WestDrive->AutoDrive(fForward, fRotate, bGyroEnabled);
            WestDrive->AutoTransmission(OI::TransmissionState::Low);
            pFeeder->IntakeExtend(false);
            pFeeder->RunIntake(-.5);
            pFeeder->BottomFeeder(.5);
            pFeeder->TopFeeder(-.5);
            if(fabs(15-CurrentAutoPosition())< .1 )
            {
                iState  = 100;
            }
        break;

        case 100:
        default:
            WestDrive->AutoDrive(0.0, 0.0);
        break;
    }
}