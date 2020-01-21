/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "TeleopMain.h"



TeleopControl::TeleopControl(Robot * pRobot, Drivebase * WestDrive, ControlPanel * CtrlPanelObj) 
    {
        this->pRobot = pRobot;   
        this->WestCoast = WestCoast;
        this->CtrlPanelObj  = CtrlPanelObj;
    }

void TeleopControl::TeleopMain() 
{
    //=======================================================================================================
    //Control Panel
    //=======================================================================================================
    CtrlPanelObj->ColorTest();
    //Rotates control panel when B is pressed on Xbox2
    CtrlPanelObj->ManualRotate(pRobot->DriverCMD.CPRotate());
    if(pRobot->DriverCMD.CPRotate())
    {
        //Rotates the control panel argument times when left bumper is pressed on Xbox2
        CtrlPanelObj->Rotate(3);
    }
    if(pRobot->DriverCMD.CPToColor())
    {
        //Rotates the control panel to game data value ('R', 'G', 'B', or 'Y') when right bumper is pressed on Xbox2
        CtrlPanelObj->RotateToColor();
    }
    //=======================================================================================================


    pRobot->DriverCMD.UpdateOI();
    WestCoast->Drive();
}