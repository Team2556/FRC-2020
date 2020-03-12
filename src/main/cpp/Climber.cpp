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
//Roll to a balanced point automatically once the robot climbs
//=================================================================================================
void Climber::rollClimber(float angle) 
{
    frc::SmartDashboard::PutNumber("Roll Value", angle);

    //Set motors to power after it is manipulated
    float power = 0;

    //Balance to plus/minus this angle
    const float balancePrecision = 5;

    //sets angle to range from -180 to 180 degrees
    if(angle > 180)
    {
        angle -= 360;
    }

    //If shield generator is balanced dont frickin move
    if(abs(angle) <= balancePrecision)
    {
        //pRobot->RollingMotor.Set(ControlMode::PercentOutput, power);
        return;
    }

    if(angle < 0)
    {
        //when the angle is -15 degrees, power is -1, when at balancePrecision degrees power is 0
        power = (balancePrecision - 15)/(15 + balancePrecision) * (angle + balancePrecision)/(balancePrecision - angle);
    }
    else
    {
        //when the angle is 15 degrees, power is 1, when at balancePrecision degrees power is 0
        power = (balancePrecision + 15)/(15 - balancePrecision) * (angle - balancePrecision)/(balancePrecision + angle);
    }

    frc::SmartDashboard::PutNumber("Balance Precision", balancePrecision);
    //makes the robot roll at slower speeds as you approach balanced, ranges from 0 to 1 power
    //pRobot->RollingMotor.Set(ControlMode::PercentOutput, power);
    frc::SmartDashboard::PutNumber("Climber Strafe Power", power);
}


void Climber::ClimbManual()
{
    //pistions
    if(pRobot->Intake_Solenoid.Get() == frc::DoubleSolenoid::Value::kForward)
    {
        ClimberDebug.PutBoolean("Intake Out", true);
        if(pRobot->DriverCMD.climbUp)
        {
            pRobot->Climb_Solenoid.Set(frc::DoubleSolenoid::Value::kForward);
        }
        else
        {
            pRobot->Climb_Solenoid.Set(frc::DoubleSolenoid::kReverse);
        }
    
    }
    else
    {
        ClimberDebug.PutBoolean("Intake Out", false);
    }


    if(true)//pRobot->Climb_Solenoid.Get() == frc::DoubleSolenoid::Value::kForward && pRobot->Intake_Solenoid.Get() == frc::DoubleSolenoid::Value::kForward)
    {
        ClimberDebug.PutBoolean("Climb Enabled", true);
        frc::SmartDashboard::PutNumber("Climb Speed", pRobot->DriverCMD.fClimbSpeed());
        pRobot->WinchMotor.Set(ControlMode::PercentOutput, pRobot->DriverCMD.fClimbSpeed());
    }
    else
    {
        pRobot->WinchMotor.Set(ControlMode::PercentOutput, 0);
        ClimberDebug.PutBoolean("Climb Enabled", false);
    }
}