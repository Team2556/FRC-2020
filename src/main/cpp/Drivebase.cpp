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