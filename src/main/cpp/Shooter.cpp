/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Shooter.h"
#include "math.h"

Shooter::Shooter(Robot * pRobot, Feeder * pFeeder) 
{
    this->pRobot = pRobot;
	this->pFeeder = pFeeder;

    pPIDOutput = new TurretPIDOutput(&fYawPIDValue);
    pYawPID    = new frc::PIDController(0.0285, .000, .002, .06, this, pPIDOutput);

    PIDEnable(true);
}


void Shooter::AutoShoot()
{
	//Turret Aiming
	Aim();
	
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
	// if(pRobot->MagicVision.HasTarget())
	// {
		float value = fYawPIDValue;
		pRobot->Turret_Motor.Set(value);
		frc::SmartDashboard::PutNumber("PID Output",value);
		frc::SmartDashboard::PutBoolean("Has Target", true);
	// }
	// else
	// {
	// 	//return to forward
	// 	frc::SmartDashboard::PutBoolean("Has Target", false);
	// 	frc::SmartDashboard::PutNumber("PID Output",.5*pRobot->DriverCMD.fTestValue(6));
	// 	pRobot->Turret_Motor.Set(.5*pRobot->DriverCMD.fTestValue(6));
	// }
	
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
	float target = .0012158 * (pow(distance, 2.0)) + -1.58349*distance -163.159;
	
	return target;
}
float DistanceToHoodVal2(float distance)
{
	float target = (90027/distance) -827.694;
	
	return target;
}

void Shooter::AutoHood(float distance)
{
	if(distance < 0 )
	{
		distance = pRobot->ShooterDistance.distance;
	}
	float target = DistanceToHoodVal2(distance);
	ShooterDebug.PutNumber("Hood Target", target);
	if (true)
	{
		pRobot->Hood_Motor.Set(ControlMode::Position, target);
	}
	else
	{
		pRobot->Hood_Motor.Set(ControlMode::PercentOutput, 0);
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
	float speed =  -pRobot->DriverCMD.speedMult *33700;//max 33700 encoder 4930 rpm
	frc::SmartDashboard::PutNumber("Set Speed", speed);
	pRobot->Shooter_Motor_1.Set(ControlMode::Velocity, speed);
	pRobot->Shooter_Motor_2.Follow(pRobot->Shooter_Motor_1);
	frc::SmartDashboard::PutNumber("Shoot Speed", pRobot->Shooter_Motor_1.GetSelectedSensorVelocity());
	frc::SmartDashboard::PutNumber("Shoot Set Percent", pRobot->Shooter_Motor_1.GetMotorOutputPercent());
}

float Shooter::SpinUpDistance(float distance, bool manual)
{
	if (distance<0)
	{
		distance = pRobot->ShooterDistance.distance;
	}
	float power = -(((.3/(16*30.48))*(distance-(8*30.48)))+.6);
	if(power<-.85)
	{
		power = -.85;
	}
	frc::SmartDashboard::PutNumber("Shooter Power", power);

	float speed =  power*33700;//max 33700 encoder 4930 rpm
	frc::SmartDashboard::PutNumber("Set Speed", speed);
	
	if((!manual) || fabs(pRobot->DriverCMD.fManualShootSpeed())>.2 )
	{
		pRobot->Shooter_Motor_1.Set(ControlMode::Velocity, speed);
		pRobot->Shooter_Motor_2.Follow(pRobot->Shooter_Motor_1);
	}
	else
	{
		pRobot->Shooter_Motor_1.Set(ControlMode::PercentOutput, 0);
		pRobot->Shooter_Motor_2.Follow(pRobot->Shooter_Motor_1);
	}

	ShooterDebug.PutNumber("Velocity", pRobot->Shooter_Motor_1.GetSelectedSensorVelocity());
	frc::SmartDashboard::PutNumber("Shoot Speed", pRobot->Shooter_Motor_1.GetSelectedSensorVelocity());
	return pRobot->Shooter_Motor_1.GetSelectedSensorVelocity() - speed;
	
}

void Shooter::StopShoot()
{
	pRobot->Shooter_Motor_1.Set(ControlMode::PercentOutput, 0);
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


void CountBallsOld()
{
	static float currents[3] = {0, 0, 0};
	static float highestseen = 0.0;
	float spike_current = 20;
	currents[0] = currents[1];
	currents[1] = currents[2];
	currents[2] = 0.0;//pRobot->PDP.GetCurrent(0);

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
		//BallsShot++;
	}
}

void CountBallsOld2()
{
	// static float Velocities[5] = {0, 0, 0, 0, 0};
	// Velocities[0] = Velocities[1];
	// Velocities[1] = Velocities[2];
	// Velocities[2] = Velocities[3];
	// Velocities[3] = Velocities[4];
	// Velocities[4] = -pRobot->Shooter_Motor_1.GetSelectedSensorVelocity();

	// float velDif = Velocities[2] - Velocities[0];
	// if( (Velocities[2]-Velocities[0]) > 0 && (Velocities[4]-Velocities[2]) > 0.0 && velDif > 50)
	// // && (Velocities[2]-Velocities[4]) > 0.0 
	// //(Velocities[2]-Velocities[0]) > 0.0 &&
	// {
	// 	BallsShot++;
	// }
	// ShooterDebug.PutNumber("velDif", velDif);
	// ShooterDebug.PutNumber("Balls Shot", BallsShot);
}


void Shooter::CountBalls()
{

}


void Shooter::ShooterManual()
{
	CountBalls();
	SpinUpDistance();
	if(pRobot->DriverCMD.AutoAim())
	{
		Aim();
	}
	else
	{
		AimManual();
	}
	pFeeder->BottomFeeder(pRobot->DriverCMD.fBottomFeederSpeed());
	pFeeder->TopFeeder(pRobot->DriverCMD.fTopFeederSpeed());
	// float rawspeed = pRobot->DriverCMD.fManualShootSpeed();
	// float speed =  rawspeed*33700;//max 33700 encoder 4930 rpm
	// frc::SmartDashboard::PutNumber("Set Speed", speed);
	// if(fabs(rawspeed)>.2 )
	// {
	// 	pRobot->Shooter_Motor_1.Set(ControlMode::Velocity, speed);
	// 	pRobot->Shooter_Motor_2.Follow(pRobot->Shooter_Motor_1);
	// }
	// else
	// {
	// 	pRobot->Shooter_Motor_1.Set(ControlMode::PercentOutput, 0);
	// 	pRobot->Shooter_Motor_2.Follow(pRobot->Shooter_Motor_1);
	// }
	// pRobot->Shooter_Motor_1.Set(ControlMode::PercentOutput, pRobot->DriverCMD.fManualShootSpeed());
	// pRobot->Shooter_Motor_2.Follow(pRobot->Shooter_Motor_1);
	if(pRobot->DriverCMD.bTestButton(2))
	{
		AutoHood();
	}
	else
	{
		pRobot->Hood_Motor.Set(pRobot->DriverCMD.fManualHoodSpeed());
	}
	frc::SmartDashboard::PutNumber("Shoot Speed", pRobot->Shooter_Motor_1.GetSelectedSensorVelocity());
	frc::SmartDashboard::PutNumber("Shoot Set Percent", pRobot->Shooter_Motor_1.GetMotorOutputPercent());
	frc::SmartDashboard::PutNumber("Velocity Error", pRobot->Shooter_Motor_1.GetClosedLoopError());
	ShooterGate(pRobot->DriverCMD.bShooterOpen());
	if(pRobot->DriverCMD.bLimeLightOff)
	{
		pRobot->MagicVision.SetValue("ledMode", 1);
	}
	else
	{
		pRobot->MagicVision.SetValue("ledMode", 3);
	}
	
}

void Shooter::AimManual()
{
	float speed = pRobot->DriverCMD.fManualTurretSpeed();
	pRobot->Turret_Motor.Set(ControlMode::PercentOutput, speed);
	ShooterDebug.PutNumber("Manual Turret Speed", speed);
}