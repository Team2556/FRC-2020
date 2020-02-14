/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Auto.h"
#include <frc/WPILib.h>


Auto::Auto(Robot * pRobot, Drivebase * WestDrive, ControlPanel * CtrlPanelObj, Shooter * pShooter) 
{
    this->pRobot = pRobot;   
    this->WestDrive = WestDrive;
    this->CtrlPanelObj  = CtrlPanelObj;
    this->pShooter      = pShooter;
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
    return 0;//pRobot->m_encoder.GetPosition();
}

