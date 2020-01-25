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
        this->WestCoast = WestCoast;
        this->CtrlPanelObj  = CtrlPanelObj;
        this->pShooter      = pShooter;
    }

void Auto::AutoInit()
{
   // currentPosition = 0;
}

void Auto::AutoPeriodic()
{
    frc::SmartDashboard::PutNumber("ProcessVariable", currentPosition);
}
