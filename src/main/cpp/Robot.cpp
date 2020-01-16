/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"




#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

#include "Drivebase.h"
#include "Shooter.h"
#include "Feeder.h"

Drivebase         * WestDrive;
Shooter           * pShooter;
Feeder            * pFeeder;


void Robot::RobotInit() 
{
  WestDrive  = new Drivebase(this);
  pFeeder = new Feeder();
  pShooter = new Shooter(this, pFeeder);
}


void Robot::RobotPeriodic() 
{

}


void Robot::AutonomousInit() 
{
  
}

void Robot::AutonomousPeriodic() 
{

}

void Robot::TeleopInit() 
{

}

void Robot::TeleopPeriodic() 
{
  //WestCoastDrive.ArcadeDrive(DriverCMD.fMoveForward(), DriverCMD.fRotate());
  RobotDrive.DriveCartesian(DriverCMD.fStrafe(), DriverCMD.fMoveForward(), DriverCMD.fRotate(), 0.0);
  pShooter->ShooterMain();
}

void Robot::TestPeriodic()
{
  
}


#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
