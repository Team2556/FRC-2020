/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "TeleopControl.h"



TeleopControl::TeleopControl(Robot * pRobot, Drivebase * WestDrive, ControlPanel * CtrlPanelObj, Shooter * pShooter) 
    {
        this->pRobot = pRobot;   
        this->WestCoast = WestCoast;
        this->CtrlPanelObj  = CtrlPanelObj;
        this->pShooter      = pShooter;
    }

void TeleopControl::TeleopInit()
{
    pShooter->rampspeed = 0;
}


void TeleopControl::TeleopTest()
{
    pRobot->WestCoastDrive.ArcadeDrive(pRobot->DriverCMD.fMoveForward(), pRobot->DriverCMD.fRotate());
  //RobotDrive.DriveCartesian(DriverCMD.fStrafe(), DriverCMD.fMoveForward(), DriverCMD.fRotate(), 0.0);
  //pShooter->ShooterMain();
  //WestDrive->Drive();
  //pShooter->TestShoot();
}