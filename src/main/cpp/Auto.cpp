/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Auto.h"

#include <frc/WPILib.h>

Auto::Auto(Robot * pRobot, Drivebase  * WestDrive) 
{
    this->pRobot = pRobot;
    this->WestDrive = WestDrive;
}

void Auto::AutoMain()
{
    WestDrive->AutoDrive((10-pRobot->MotorControl_L1.GetEncoder().GetPosition())*.4, 0, OI::TransmissionState::Low);

}