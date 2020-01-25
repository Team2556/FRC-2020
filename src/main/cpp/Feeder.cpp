/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Feeder.h"

Feeder::Feeder(Robot * pRobot) 
{
    this->pRobot = pRobot;
}

void Feeder::IntakeMain()
{

    if (pRobot->DriverCMD.IntakeOut())
    {
        pRobot->Intake_Solenoid.Set(frc::DoubleSolenoid::Value::kForward);
    }
    else
    {
        pRobot->Intake_Solenoid.Set(frc::DoubleSolenoid::Value::kReverse);
    }

    if(pRobot->DriverCMD.RunIntake())
    {
        pRobot->Intake_Motor.Set(-.5);
    }
    else if (pRobot->DriverCMD.ReverseIntake())
    {
        pRobot->Intake_Motor.Set(.75);
    }
    else
    {
        pRobot->Intake_Motor.Set(0);
    }
    
}