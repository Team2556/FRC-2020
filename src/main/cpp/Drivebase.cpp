/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivebase.h"

Drivebase::Drivebase(Robot * pRobot) 
{
    this->pRobot = pRobot;

    
}


void Drivebase::Drive()
{
    //if(pRobot->DriverCMD.CurrDriveMode == OI::DriveMode::Manual)
    //{
        frc::SmartDashboard::PutNumber("Forward", pRobot->DriverCMD.fMoveForward());
        frc::SmartDashboard::PutNumber("Rotate", pRobot->DriverCMD.fRotate());
        pRobot->WestCoastDrive.ArcadeDrive(pRobot->DriverCMD.fMoveForward(), pRobot->DriverCMD.fRotate());
        if(pRobot->DriverCMD.DriveGear == OI::TransmissionState::Low)
        {
            pRobot->Transmission.Set(frc::DoubleSolenoid::Value::kForward);
            frc::SmartDashboard::PutString("Gear", "Low");
        }
        else if(pRobot->DriverCMD.DriveGear == OI::TransmissionState::High)
        {
            pRobot->Transmission.Set(frc::DoubleSolenoid::Value::kReverse);
            frc::SmartDashboard::PutString("Gear", "High");
        }
    //}
}

void Drivebase::AutoDrive(float fForward, float fRotate, OI::TransmissionState bTransmissionState)
{

    //if(pRobot->DriverCMD.CurrDriveMode == OI::DriveMode::Manual)
    //{

        pRobot->WestCoastDrive.ArcadeDrive(fForward, fRotate);
        if(bTransmissionState == OI::TransmissionState::Low)
        {
            pRobot->Transmission.Set(frc::DoubleSolenoid::Value::kForward);
            frc::SmartDashboard::PutString("Gear", "Low");
        }
        else if(bTransmissionState == OI::TransmissionState::High)
        {
            pRobot->Transmission.Set(frc::DoubleSolenoid::Value::kReverse);
            frc::SmartDashboard::PutString("Gear", "High");
        }
    //}
}

void Drivebase::GyroDrive(float fForward, float fRotate) {
    bool			bAllowRotate = false;

    // Get joystick inputs
    fForward = pRobot->DriverCMD.fMoveForward();
    fRotate = pRobot->DriverCMD.fRotate();


    // if(pRobot->DriverCMD.bManualRotate())
    // {
    //     bAllowRotate = true;
    // }

    if(fabs(pRobot->Nav.GetYawError())<10)
    {
    	pRobot->Nav.bPresetTurning = false;
    }
    else if(pRobot->Nav.bPresetTurning == true)
    {
        bAllowRotate = false;
    }



    if(bAllowRotate == true)
    {
        bRotatePrevious = true;
    }

    if((bAllowRotate == false) && (bRotatePrevious == true) && (stopHoldCounter < 5))
    {
        stopHoldCounter++;
    }
    else if((bAllowRotate == false) && (bRotatePrevious == true) && (stopHoldCounter >= 5))
    {
        stopHoldCounter = 0;
        bRotatePrevious = false;
    }


    if (bRotatePrevious)
	{
        fRotate = pRobot->DriverCMD.fRotate();

        if (fRotate >  0.0) fRotate -= 0.05;
        if (fRotate <  0.0) fRotate += 0.05;
        if (fRotate >  0.8) fRotate  =  0.8;
        if (fRotate < -0.8) fRotate  = -0.8;

        pRobot->Nav.SetCommandYawToCurrent();
        frc::SmartDashboard::PutBoolean("Gryo Enabled", false);
	}
    else
    {
        // Calculate a rotation rate from robot angle error
    	fRotate = pRobot->Nav.GetRotate();
        frc::SmartDashboard::PutBoolean("Gryo Enabled", true);
    }


} // end GyroDrive