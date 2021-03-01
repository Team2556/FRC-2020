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



void Drivebase::ManualDrive(bool GyroEnabled)
{
    float fForward = pRobot->DriverCMD.fMoveForward();
    float fRotate = pRobot->DriverCMD.fRotate();
    bool  bQuickTurn = pRobot->DriverCMD.bQuickTurn();
    DrivebaseDebug.PutNumber("Forward", fForward);
    DrivebaseDebug.PutNumber("Rotate", fRotate);

    if(GyroEnabled)
    {
        bool bAllowRotate = false;

        if(pRobot->DriverCMD.bManualRotate())
        {
            bAllowRotate = true;
        }


        if(bAllowRotate == true)
        {
            bRotatePrevious = true;
        }

        if((bAllowRotate == false) && (bRotatePrevious == true) && (stopHoldCounter < 20))
        {
            stopHoldCounter++;
        }
        else if((bAllowRotate == false) && (bRotatePrevious == true) && (stopHoldCounter >= 20))
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
            DrivebaseDebug.PutBoolean("Gryo Enabled", false);
            bQuickTurn = pRobot->DriverCMD.bQuickTurn();
        }
        else
        {
            // Calculate a rotation rate from robot angle error
            fRotate = pRobot->Nav.GetRotate();
            DrivebaseDebug.PutBoolean("Gryo Enabled", true);
            bQuickTurn = true;
        }
    }

    //#define TANK_DRIVE
    #ifndef TANK_DRIVE
    if (pRobot->DriverCMD.flipDrive)
    {
        fForward = -fForward;
    }
    DrivebaseDebug.PutBoolean("Quick Turn", bQuickTurn);
    
    RampedDrive(fForward, fRotate, bRotatePrevious);

    
    //pRobot->WestCoastDrive.CurvatureDrive(fForward, fRotate, bQuickTurn);

    #else
    fForward = pRobot->DriverCMD.fTankLeft();
    fRotate = pRobot->DriverCMD.fTankRight();
    if (pRobot->DriverCMD.flipDrive)
    {
        fForward = -fForward;
        fRotate = -fRotate;
    }
    pRobot->WestCoastDrive.TankDrive(fForward, fRotate);
    #endif
}

void Drivebase::RampedDrive(float fForward, float fRotate, bool rampRotate)
{
    static float prevForward = fForward;
    static float prevRotate = fRotate;
    float trueForward;
    float trueRotate;

    float maxForwardRamp = .025;//frc::SmartDashboard::GetNumber("Max Forward Ramp", 0.02);//.05; //.02 on Banshee
    float maxRotateRamp = .015; //frc::SmartDashboard::GetNumber("Max Rotate Ramp", 0.02);//.05; //.02 on Banshee
    frc::SmartDashboard::PutNumber("Max Forward Ramp", maxForwardRamp);
    frc::SmartDashboard::PutNumber("Max Rotate Ramp", maxRotateRamp);
    DrivebaseDebug.PutNumber("Max Forward Ramp", maxForwardRamp);
    DrivebaseDebug.PutNumber("Max Rotate Ramp", maxRotateRamp);

    if(fabs(prevForward - fForward) < maxForwardRamp)
    {
        trueForward = fForward;
    }
    else
    {
        trueForward = prevForward +  pRobot->DriverCMD.sign((prevForward - fForward))*(-1)*(maxForwardRamp);
    }
    //ramp rotate
    if(rampRotate)
    {
        if(fabs(prevRotate - fRotate) < maxRotateRamp)
        {
            trueRotate = fRotate;
        }
        else
        {
            trueRotate = prevRotate + pRobot->DriverCMD.sign((prevRotate - fRotate))*(-1)*(maxRotateRamp);
        }
    }
    else
    {
        trueRotate = fRotate;
    }

    pRobot->WestCoastDrive.CurvatureDrive(trueForward, trueRotate, pRobot->DriverCMD.bQuickTurn());

    prevForward = trueForward;
    prevRotate = trueRotate;
}

void Drivebase::AutoDrive(float fForward, float fRotate,  bool GyroEnabled)
{

    if(GyroEnabled)
    {
        bool bAllowRotate = false;

        if(fabs(fRotate) > .1)
        {
            bAllowRotate = true;
        }


        if(bAllowRotate == true)
        {
            bRotatePrevious = true;
        }

        if((bAllowRotate == false) && (bRotatePrevious == true) && (stopHoldCounter < 20))
        {
            stopHoldCounter++;
        }
        else if((bAllowRotate == false) && (bRotatePrevious == true) && (stopHoldCounter >= 20))
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

            pRobot->Nav.SetCommandYawToCurrent();
            DrivebaseDebug.PutBoolean("Gryo Enabled", false);
        }
        else
        {
            // Calculate a rotation rate from robot angle error
            fRotate = pRobot->Nav.GetRotate();
            DrivebaseDebug.PutBoolean("Gryo Enabled", true);
        }
    }
    if (pRobot->DriverCMD.flipDrive)
    {
        fForward = -fForward;
    }
        
    
    else
    {
        pRobot->Nav.SetCommandYawToCurrent();
    }


    #ifndef TANK_DRIVE
    pRobot->WestCoastDrive.ArcadeDrive(fForward, fRotate);

    #else
    fForward = pRobot->DriverCMD.fTankLeft();
    fRotate = pRobot->DriverCMD.fTankRight();
    if (pRobot->DriverCMD.flipDrive)
    {
        fForward = -fForward;
        fRotate = -fRotate;
    }
    pRobot->WestCoastDrive.TankDrive(fForward, fRotate);
    #endif
}

void Drivebase::ManualTransmission()
{
    if(pRobot->DriverCMD.DriveGear == OI::TransmissionState::Low)
    {
        pRobot->Transmission.Set(frc::DoubleSolenoid::Value::kForward);
        DrivebaseDebug.PutString("Gear", "Low");
    }
    else if(pRobot->DriverCMD.DriveGear == OI::TransmissionState::High)
    {
        pRobot->Transmission.Set(frc::DoubleSolenoid::Value::kReverse);
        DrivebaseDebug.PutString("Gear", "High");
    }
}

void Drivebase::AutoTransmission(OI::TransmissionState bTransmissionState)
{
    if(bTransmissionState == OI::TransmissionState::Low)
    {
        pRobot->Transmission.Set(frc::DoubleSolenoid::Value::kForward);
        DrivebaseDebug.PutString("Gear", "Low");
    }
    else if(bTransmissionState == OI::TransmissionState::High)
    {
        pRobot->Transmission.Set(frc::DoubleSolenoid::Value::kReverse);
        DrivebaseDebug.PutString("Gear", "High");
    }
}

bool Drivebase::DriveDistance(float distance, bool reset, bool GyroEnabled)
{
    static float startDistance = 0;//pRobot->MotorControl_L1.GetEncoder().GetPosition();
    if(reset)
    {
        startDistance = 0;//pRobot->MotorControl_L1.GetEncoder().GetPosition();
    }

    
    return true;
}
void Drivebase::test()
{
    DrivebaseDebug.PutNumber("forward", pRobot->DriverCMD.fMoveForward());
}
