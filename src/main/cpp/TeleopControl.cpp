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
}


void TeleopControl::TeleopMain()
{
    //pRobot->DriverCMD.UpdateOI();
    //pFeeder->IntakeMain();
    //pRobot->WestCoastDrive.ArcadeDrive(pRobot->DriverCMD.fMoveForward(), pRobot->DriverCMD.fRotate());
    //RobotDrive.DriveCartesian(DriverCMD.fStrafe(), DriverCMD.fMoveForward(), DriverCMD.fRotate(), 0.0);
    //pShooter->ShooterMain();
    //WestDrive->Drive();

    //Robot moves after the start button is pressed
    if(pRobot->DriverCMD.BarRoll())
    {
        pClimber->rollClimber(pRobot->Nav.GetRoll());
    }
    //pShooter->TestShoot();
}

void TeleopControl::TeleopTest()
{
  //WestCoastDrive.ArcadeDrive(DriverCMD.fMoveForward(), DriverCMD.fRotate());
  //RobotDrive.DriveCartesian(DriverCMD.fStrafe(), DriverCMD.fMoveForward(), DriverCMD.fRotate(), 0.0);
}