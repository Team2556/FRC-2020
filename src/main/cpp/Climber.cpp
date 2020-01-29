/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Climber.h"

Climber::Climber(Robot * pRobot) 
{
    this->pRobot = pRobot;
}

void Climber::climbUpDown(float i)
{
    pRobot->ClimbingMotor.Set(ControlMode::PercentOutput, i);
}

//=================================================================================================
//Roll automatically once the robot climbs
//=================================================================================================
void Climber::rollClimber(float angle) 
{
    //sets angle to range from -180 to 180 degrees
    if(angle > 180)
    {
        angle -= 360;
    }

    //If shield generator is balanced dont frickin move
    if(abs(angle) < 5)
    {
        return;
    }

    //makes the robot roll at slower speeds as you approach balanced, ranges from 4/12 to 7/12 power
    //pRobot->RollingMotor.Set(ControlMode::PercentOutput, angle/(angle + 10));

    frc::SmartDashboard::PutNumber("Roll Value", angle);
}