/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

OI::OI() 
{
    CurrDriveMode = DriveMode::Manual;
    
}


//==============================================================================
//Drivebase
//==============================================================================
    
float OI::fMoveForward()
{
    return -Xbox1.GetY(frc::XboxController::kLeftHand);
}

float OI::fStrafe()
{
    return Xbox1.GetX(frc::XboxController::kLeftHand);
}


float OI::fRotate()
{
    return Xbox1.GetX(frc::XboxController::kRightHand);
}


//==============================================================================
