/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Shooter.h"

Shooter::Shooter(Robot * pRobot, Feeder * pFeeder) 
{
    this->pRobot = pRobot;
    this->pFeeder = pFeeder;

    pPIDOutput = new TurretPIDOutput(&fYawPIDValue);
    pYawPID    = new frc::PIDController(0.025, 0, .004, this, pPIDOutput);

    PIDEnable(true);
}


void Shooter::AutoShoot()
{

}

void Shooter::ShooterMain()
{
    Aim();
}

void Shooter::Aim()
{
	float value = fYawPIDValue;
    pRobot->Turret_Motor.Set(value);
    frc::SmartDashboard::PutNumber("PID Output",value);
}

double Shooter::PIDGet()
{
    frc::SmartDashboard::PutNumber("PID Error", pRobot->MagicVision.HorizontalOffset());
	return -pRobot->MagicVision.HorizontalOffset();
}

void Shooter::PIDEnable(bool bEnable)
{
	if (bEnable)
	{
	//        this->bPIDEnabled = true;
		pYawPID->Enable();
	}
	else
	{
	//        this->bPIDEnabled = false;
	pYawPID->Reset();
	pYawPID->Disable(); // PROBABLY DON'T NEED
	}
}


void Shooter::TestShoot()
{	
	frc::SmartDashboard::PutNumber("Encoder Velocity", pRobot->Shooter_Motor_1.GetSelectedSensorVelocity());
	if (pRobot->Shooter_Motor_1.GetSelectedSensorVelocity() <= (-15000))
	{
		float maxvelocity = -24600;
		static float speed = 0.0;
		if (pRobot->DriverCMD.bTestButton(6))
		{
			speed = pRobot->DriverCMD.fTestValue(5);
		}
		frc::SmartDashboard::PutNumber("Shooter Speed", speed);
		frc::SmartDashboard::PutBoolean("Ramping", false);
		pRobot->Shooter_Motor_1.Set(ctre::phoenix::motorcontrol::ControlMode::Velocity, maxvelocity*.8);
		pRobot->Shooter_Motor_2.Follow(pRobot->Shooter_Motor_1);


		
	}
	else 
	{
		pRobot->Shooter_Motor_1.Set(rampspeed);
		pRobot->Shooter_Motor_2.Follow(pRobot->Shooter_Motor_1);
		rampspeed -= .001;
		frc::SmartDashboard::PutNumber("Ramp Speed", rampspeed);
		frc::SmartDashboard::PutBoolean("Ramping", true);
	}
}