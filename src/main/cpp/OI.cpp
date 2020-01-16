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

float OI::CPRotate()
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
