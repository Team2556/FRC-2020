/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Shooter.h"

Shooter::Shooter(Robot * pRobot) 
{
    this->pRobot = pRobot;

    pPIDOutput = new TurretPIDOutput(&fYawPIDValue);
    pYawPID    = new frc::PIDController(0.025, 0, .004, this, pPIDOutput);

    PIDEnable(true);
}


void Shooter::AutoShoot()
{

}

bool Shooter::ShooterMain()
{
    Aim();
	frc::SmartDashboard::PutNumber("Robot Distance", RobotDistance());
	return false;
}

float Shooter::LimelightDistance()
{
	return pRobot->MagicVision.Height();
}

float Shooter::RobotDistance()
{
	return -2*LimelightDistance() + 60;
}


void Shooter::Aim()
{
	if(pRobot->MagicVision.HasTarget())
	{
		float value = fYawPIDValue;
		pRobot->Turret_Motor.Set(value);
		frc::SmartDashboard::PutNumber("PID Output",value);
		frc::SmartDashboard::PutBoolean("Has Target", true);
	}
	else
	{
		//return to forward
		frc::SmartDashboard::PutBoolean("Has Target", false);
		frc::SmartDashboard::PutNumber("PID Output",.5*pRobot->DriverCMD.fTestValue(6));
		pRobot->Turret_Motor.Set(.5*pRobot->DriverCMD.fTestValue(6));
	}
	
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
	frc::SmartDashboard::PutNumber("Encoder pos", pRobot->Shooter_Motor_1.GetSelectedSensorPosition());
	// if (pRobot->Shooter_Motor_1.GetSelectedSensorVelocity() <= (-15000))
	// {
		float maxvelocity = -2000;
		static float speed = 0.0;
		if (pRobot->DriverCMD.bTestButton(6))
		{
			speed = pRobot->DriverCMD.fTestValue(5);
		}
		frc::SmartDashboard::PutNumber("Shooter Speed", speed);
		frc::SmartDashboard::PutBoolean("Ramping", false);
		pRobot->Shooter_Motor_1.Set(ControlMode::PercentOutput, 1);
		pRobot->Shooter_Motor_2.Follow(pRobot->Shooter_Motor_1);


		
	// }
	// else 
	// {
	// 	pRobot->Shooter_Motor_1.Set(rampspeed);
	// 	pRobot->Shooter_Motor_2.Follow(pRobot->Shooter_Motor_1);
	// 	rampspeed -= .001;
	// 	frc::SmartDashboard::PutNumber("Ramp Speed", rampspeed);
	// 	frc::SmartDashboard::PutBoolean("Ramping", true);
	// }
}

bool comp(int a, int b) 
{ 
    return (a < b); 
} 


void Shooter::CountBalls()
{
	static float currents[3] = {0, 0, 0};
	static float highestseen = 0.0;
	float spike_current = 20;
	currents[0] = currents[1];
	currents[1] = currents[2];
	currents[2] = pRobot->PDP.GetCurrent(0);

	if (currents[2] > highestseen)
	{
		frc::SmartDashboard::PutNumber("MaxCurrent", currents[2]);
		highestseen = currents[2];
	}
	frc::SmartDashboard::PutNumber("CurrentCurrent", currents[2]);

	float maxcurrent = currents[0];
	if (currents[1] > maxcurrent)
	{
		maxcurrent = currents[1];
	}
	if (currents[2] > maxcurrent)
	{
		maxcurrent = currents[2];
	}
	if ((currents[1] - currents[0]) > 0.0 && (currents[1] - currents[2]) > 0.0 && maxcurrent > spike_current)
	{
		BallsShot++;
	}
}