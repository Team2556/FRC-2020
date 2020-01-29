
/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

OI::OI() 
{
    CurrDriveMode = DriveMode::Manual;
    bIntakeOut = false;
    
}

bool OI::testBool()
{
    return false;
}
//==============================================================================
//General
//==============================================================================

void OI::UpdateOI()
{/*
    if(Xbox1.GetBumper(frc::XboxController::kRightHand) && !Xbox1.GetBumper(frc::XboxController::kLeftHand))
    {
        DriveGear = OI::TransmissionState::High;
        frc::SmartDashboard::PutString("Transmission State", "High");
    }
    else if(Xbox1.GetBumper(frc::XboxController::kLeftHand) && !Xbox1.GetBumper(frc::XboxController::kRightHand))
    {
        DriveGear = OI::TransmissionState::Low;
        frc::SmartDashboard::PutString("Transmission State", "Low");
    }
    */
    if(Xbox1.GetTriggerAxis(frc::XboxController::kRightHand)> .5)
    {
        DriveGear = OI::TransmissionState::High;
        frc::SmartDashboard::PutString("Transmission State", "High");
    }
    else 
    {
        DriveGear = OI::TransmissionState::Low;
        frc::SmartDashboard::PutString("Transmission State", "Low");
    }
}

//==============================================================================
//Drivebase
//==============================================================================
    
float OI::fMoveForward()
{
    return Xbox1.GetY(frc::XboxController::kLeftHand);
}

float OI::fStrafe()
{
    return Xbox1.GetX(frc::XboxController::kLeftHand);
}


float OI::fRotate()
{
    return -Xbox1.GetX(frc::XboxController::kRightHand);
}


//==============================================================================

float OI::CPManualRotate()
{
    if(Xbox2.GetBButton())
    {
        return 1.0;
    }
    else
    {
        return 0;
    }
}

bool OI::IntakeOut()
{
    if(Xbox2.GetBButtonPressed())
    {
        bIntakeOut = !bIntakeOut;
    }
    return bIntakeOut;
}

bool OI::RunIntake()
{
    return Xbox2.GetAButton();
}

bool OI::ReverseIntake()
{
    return false;
    
    if(!Xbox2.GetAButton() && Xbox2.GetYButton())
    {
        return true;
    }
    
}
bool OI::CPRotate()
{
    return Xbox2.GetBumper(frc::XboxController::kLeftHand);
}
//==============================================================================

float OI::fClimb()
{
    if(Xbox2.GetTriggerAxis(frc::XboxController::kRightHand) > 0.1 && Xbox2.GetTriggerAxis(frc::XboxController::kLeftHand) < 0.1)
    {
        return Xbox2.GetTriggerAxis(frc::XboxController::kRightHand); 
    } 
    else if (Xbox2.GetTriggerAxis(frc::XboxController::kLeftHand) > 0.1 && Xbox2.GetTriggerAxis(frc::XboxController::kRightHand) < 0.1)  
    {
        return Xbox2.GetTriggerAxis(frc::XboxController::kLeftHand);
    }
    else
    {
        return 0;
    }
}

bool OI::CPToColor()
{
    return Xbox2.GetBumper(frc::XboxController::kRightHand);
}

bool OI::BarRoll()
{
    if(Xbox2.GetStartButton())
    {
        moveOnBar++;
    }
    if(moveOnBar % 2 == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

// ----------------------------------------------------------------------------
// Test commands
// ----------------------------------------------------------------------------

// Designate some buttons as test buttons just to be able to test
// some functionality.
bool OI::bTestButton(int iButton)
    {
    bool    bButtonValue;

    if ((iButton < 0) || (iButton > 5))
        return false;

#ifdef JOYSTICK
    switch (iButton)
        {
        case 0  : bButtonValue = JStick1.GetRawButton( 2); break;   // Thumb
        case 1  : bButtonValue = JStick1.GetRawButton(11); break;
        case 2  : bButtonValue = JStick1.GetRawButton(12); break;
        case 3  : bButtonValue = JStick1.GetRawButton( 9); break;
        case 4  : bButtonValue = JStick1.GetRawButton(10); break;
        case 5  : bButtonValue = JStick1.GetRawButton( 7); break;
        default : bButtonValue = false;                    break;
        }

#else
    switch (iButton)
        {
        case 0 :
            bButtonValue = Xbox2.GetAButton();
            break;
        case 1 :
            bButtonValue = Xbox2.GetBButton();
            break;
        case 2 :
            bButtonValue = Xbox2.GetXButton();
            break;
        case 3 :
            bButtonValue = Xbox2.GetYButtonPressed();
            break;
        case 4 :
            bButtonValue = Xbox2.GetBumper(frc::XboxController::JoystickHand::kLeftHand);
            break;
        case 5 :
            bButtonValue = Xbox2.GetBumper(frc::XboxController::JoystickHand::kRightHand);
            break;
        case 6:
            bButtonValue = Xbox1.GetAButton();
            break;
        default :
            bButtonValue = false;
            break;
        }
#endif

    return bButtonValue;
    }
    

// ----------------------------------------------------------------------------

// Return a control test value
// From -1.0 to +1.0
float OI::fTestValue(int iControl)
{
    float   fControlValue;

    if ((iControl < 0) || (iControl > 5))
    {
        return 0.0;
    }
    switch (iControl)
    {
        case 0 :
            fControlValue = Xbox2.GetTriggerAxis(frc::XboxController::JoystickHand::kRightHand);
            break;
        case 1 :
            fControlValue = Xbox2.GetTriggerAxis(frc::XboxController::JoystickHand::kLeftHand);
            break;
        case 2 :
            fControlValue = Xbox2.GetX(frc::XboxController::kLeftHand);
            break;
        case 3 :
            fControlValue = Xbox2.GetY(frc::XboxController::kLeftHand);
            break;
        case 4 :
            fControlValue = Xbox1.GetTriggerAxis(frc::XboxController::kRightHand);
            break;
        case 5 :
            fControlValue = Xbox1.GetY(frc::XboxController::kLeftHand);
            break;
        default :
            fControlValue = 0.0;
            break;
    }

    return fControlValue;
}