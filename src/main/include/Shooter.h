/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "Robot.h"
#include "frc/WPILib.h"

class TurretPIDOutput : public frc::PIDOutput
{
	public:
		TurretPIDOutput(float * pfYawPIDVar) : pfYawPID(pfYawPIDVar) {}

		float       * pfYawPID;

		void PIDWrite(double dOutput) { *pfYawPID = dOutput; }
};


class Shooter : frc::PIDSource
{
 public:
  Shooter(Robot * pRobot);

  void AutoShoot();
  void ShooterMain();
  void Aim();
  void CountBalls();

  void TestShoot();

  Robot * pRobot; 


  float rampspeed;
  int BallsShot;

  //Stuff for pid controller
  TurretPIDOutput     * pPIDOutput;
	frc::PIDController  * pYawPID;
  float fYawPIDValue;
  void    PIDEnable(bool bEnable);
  double  PIDGet();
};

