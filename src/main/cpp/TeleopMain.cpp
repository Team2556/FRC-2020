/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "TeleopMain.h"



TeleopControl::TeleopControl(Robot * pRobot, Drivebase * WestDrive, ControlPanel * CtrlPanelObj, Feeder * pFeeder) 
    {
        this->pRobot = pRobot;   
        this->WestCoast = WestDrive;
        this->CtrlPanelObj  = CtrlPanelObj;
        this->pFeeder = pFeeder;
    }

void TeleopControl::TeleopMain() 
{
    //CtrlPanelObj->ColorTest();
    //CtrlPanelObj->ManualRotate(pRobot->DriverCMD.CPRotate());
    pRobot->DriverCMD.UpdateOI();
    WestCoast->Drive();
    pFeeder->IntakeMain();
    
}