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
    pYawPID    = new frc::PIDController(0.035, 0, 0, this, pPIDOutput);

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

void Shooter::SetTurretHome()
{
	TurretHome = pRobot->Turret_Motor.GetSelectedSensorPosition();
}

void Shooter::GoTurretHome()
{
	pRobot->Turret_Motor.Set(ControlMode::Position, TurretHome);
}

float DistanceToHoodVal(float distance)
{
	float max = 100;
	float min = 0;
	 
}

void Shooter::AutoHood(float distance)
{
	if(distance > 0 )
	{
		pRobot->Hood_Motor.Set(ControlMode::Position, DistanceToHoodVal(distance));
	}
}

double Shooter::PIDGet()
{
    frc::SmartDashboard::PutNumber("PID Error", pRobot->MagicVision.HorizontalOffset());
	return pRobot->MagicVision.HorizontalOffset();
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

void Shooter::SpinUp()
{
	pRobot->Shooter_Motor_1.Set(1);
	pRobot->Shooter_Motor_2.Follow(pRobot->Shooter_Motor_1);
}

void Shooter::ShooterGate(bool open)
{
	if (open)
	{
		pRobot->Shooter_Solenoid.Set(frc::DoubleSolenoid::Value::kReverse);
	}
	else
	{
		pRobot->Shooter_Solenoid.Set(frc::DoubleSolenoid::Value::kForward);
	}
}


void Shooter::TestShoot()
{	
	frc::SmartDashboard::PutNumber("Encoder Velocity", pRobot->Shooter_Motor_1.GetSelectedSensorVelocity());
	// pRobot->Shooter_Motor_1.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 1);
	// pRobot->Shooter_Motor_2.Follow(pRobot->Shooter_Motor_1);
	// if (pRobot->Shooter_Motor_1.GetSelectedSensorVelocity() <= (-15000))
	// {
	// 	float maxvelocity = -26800;
	// 	static float speed = 0.0;
	// 	if (pRobot->DriverCMD.bTestButton(6))
	// 	{
	// 		speed = pRobot->DriverCMD.fTestValue(5);
	// 	}
	// 	frc::SmartDashboard::PutNumber("Shooter Speed", speed);
	// 	frc::SmartDashboard::PutBoolean("Ramping", false);
	// 	pRobot->Shooter_Motor_1.Set(ctre::phoenix::motorcontrol::ControlMode::Velocity, maxvelocity*.95);
	// 	pRobot->Shooter_Motor_2.Follow(pRobot->Shooter_Motor_1);


		
	// }
	// else 
	// {
		pRobot->Shooter_Motor_1.Set(rampspeed);
		pRobot->Shooter_Motor_2.Follow(pRobot->Shooter_Motor_1);
		rampspeed -= .001;
		frc::SmartDashboard::PutNumber("Ramp Speed", rampspeed);
		frc::SmartDashboard::PutBoolean("Ramping", true);
	// }
	// CountBalls();
	// frc::SmartDashboard::PutNumber("Balls Shot", BallsShot);
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

void Shooter::ShooterManual()
{
	// if(pRobot->DriverCMD.bTestButton(0))
	// {
	// 	Aim();
	// }
	// else
	// {
		AimManual();
	// }
	pFeeder->BottomFeeder(pRobot->DriverCMD.fBottomFeederSpeed());
	pFeeder->TopFeeder(pRobot->DriverCMD.fTopFeederSpeed());
	float speed =  pRobot->DriverCMD.fManualShootSpeed()*30000;
	frc::SmartDashboard::PutNumber("Set Speed", speed);
	// if(fabs(pRobot->DriverCMD.fManualShootSpeed())>.2 )
	// {
	// pRobot->Shooter_Motor_1.Set(ControlMode::Velocity, speed);
	// pRobot->Shooter_Motor_2.Follow(pRobot->Shooter_Motor_1);
	// }
	// else
	// {
	// 	pRobot->Shooter_Motor_1.Set(ControlMode::PercentOutput, 0);
	// 	pRobot->Shooter_Motor_2.Follow(pRobot->Shooter_Motor_1);
	// }
	pRobot->Shooter_Motor_1.Set(ControlMode::PercentOutput, pRobot->DriverCMD.fManualShootSpeed());
	pRobot->Shooter_Motor_2.Follow(pRobot->Shooter_Motor_1);
	pRobot->Hood_Motor.Set(pRobot->DriverCMD.fManualHoodSpeed());
	frc::SmartDashboard::PutNumber("Shoot Speed", pRobot->Shooter_Motor_1.GetSelectedSensorVelocity());
	frc::SmartDashboard::PutNumber("Shoot Set Speed", pRobot->Shooter_Motor_1.GetMotorOutputPercent());
}

void Shooter::AimManual()
{
	float speed = pRobot->DriverCMD.fManualTurretSpeed();
	pRobot->Turret_Motor.Set(ControlMode::PercentOutput, speed);
	ShooterDebug.PutNumber("Manual Turret Speed", speed);
}