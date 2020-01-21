/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

OI::OI() 
    {
        
    }

//==============================================================================

float OI::CPManualRotate()
{
    if(Xbox2.GetBButton())
    {
        return 1.0;
    }
    else
    {
        return 0;
    }
}

float OI::CPRotate()
{
    if(Xbox2.GetBumper(frc::XboxController::kLeftHand))
    {
        return 1.0;
    }
    else
    {
        return 0;
    }
}

float OI::CPToColor()
{
    if(Xbox2.GetBumper(frc::XboxController::kRightHand))
    {
        return 1.0;
    }
    else
    {
        return 0;
    }
}