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
    pRobot->m_encoder.SetPosition(0);
    pRobot->AutoMode = pRobot->AutoChooser.GetSelected();
    pRobot->Nav.SetCommandYawToCurrent();
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
    frc::SmartDashboard::PutString("Auto Version", pRobot->AutoChooser.GetSelected());
    frc::SmartDashboard::PutNumber("Encoder Position", currentPosition);
    AutoChooser();
}

void Auto::AutoOne()
{

}

void Auto::AutoTwo()
{

}

void Auto::AutoThree()
{

}

