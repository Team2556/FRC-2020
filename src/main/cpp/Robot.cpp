/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() 
{
  
}


void Robot::RobotPeriodic() 
  {

  }


//Auto Init
void Robot::AutonomousInit() 
  {

  }
//Auto Periodic
void Robot::AutonomousPeriodic() 
  {
 
  }

void Robot::TeleopInit() 
  {

  }

void Robot::TeleopPeriodic() 
  {

  }

void Robot::TestPeriodic() 
  {

  }

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
