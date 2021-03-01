
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
    frc::SmartDashboard::PutString("CameraSelected", "1");
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

    if(Xbox1.GetStartButtonPressed())
    {
        flipDrive = !flipDrive;
        if(flipDrive)
        {
            frc::SmartDashboard::PutString("CameraSelected", "1");
        }
        else
        {
            frc::SmartDashboard::PutString("CameraSelected", "0");
        }
    }
    
    if(Xbox3.GetStartButtonPressed())
    {
        bLimeLightOff = !bLimeLightOff;
    }
    frc::SmartDashboard::PutBoolean("Climber Up", climbUp);
    bClimbUp();
}

bool OI::BreakAuto()
{
    return Xbox1.GetBackButton() || Xbox2.GetBackButton();
}

//==============================================================================
//Drivebase
//==============================================================================
    
float OI::fMoveForward()
{
    return -Xbox1.GetY(frc::XboxController::kLeftHand);
}

float OI::fStrafe()
{
    return Xbox1.GetX(frc::XboxController::kLeftHand);
}

float OI::sign(float value)
{
    return (!std::signbit(value))*2 - 1;
}

std::string OI::GetCamera()
{
    // static bool Cam1 = false;
    // bool switching = Xbox1.GetYButtonPressed();
    // if(switching)
    // {
    //     Cam1 = !Cam1;
    //     if(Cam1)
    //     {
    //         return "1";
    //     }
    //     else
    //     {
    //         return "0";
    //     }
    // }
    // return "-1";
    std::string returnString = "-1";
    if(driveDirChanged)
    {
        if(flipDrive)
        {
            returnString = "1";
        }
        else
        {
            returnString = "0";
        }
    }
    driveDirChanged = false;
    return returnString;
}

float OI::fRotate()
{
    #define MAX_ROTATE  .7
    float speed = -Xbox1.GetX(frc::XboxController::kRightHand);
    speed = pow(speed, 2)*.7*sign(speed);
    if (speed < -MAX_ROTATE)
    {
        speed = -MAX_ROTATE;
    }
    if (speed > MAX_ROTATE)
    {
        speed = MAX_ROTATE;
    }
    return speed;
}

float OI::fTankLeft()
{
    return -Xbox1.GetY(frc::XboxController::kLeftHand);
}

float OI::fTankRight()
{
    return -Xbox1.GetY(frc::XboxController::kRightHand);
}

bool OI::bQuickTurn()
{
    return !Xbox1.GetBumper(frc::XboxController::kLeftHand);
}

bool OI::bManualRotate()
{
    if ((fRotate() > .05) || (fRotate() < -.05))
        return true;
    else
        return false;
}

//==============================================================================
//Co-Driver
//==============================================================================

bool OI::Shoot()
{
    return Xbox2.GetTriggerAxis(frc::XboxController::JoystickHand::kRightHand);
}
bool OI::bShootPreset1()
{
    return Xbox2.GetStickButton(frc::XboxController::kLeftHand);
}

bool OI::EndShoot()
{
    return Xbox2.GetTriggerAxis(frc::XboxController::JoystickHand::kLeftHand);
}
float OI::CPManualRotate()
{
     return 0.0;
    if(Xbox3.GetXButton())
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
    if(!Xbox2.GetAButton() && Xbox2.GetYButton())
    {
        return true;
    }
    else
    {
        return false;
    }
    
}


bool OI::bShooterOpen()
{
    static bool shooterOpen = false;
    if (Xbox2.GetBackButtonPressed())
    {
        shooterOpen = !shooterOpen;
    }
    return shooterOpen;
}

float OI::fBottomFeederSpeed()
{
    if(Xbox2.GetPOV() == 270)
    {
        return 1;
    }
    else if(Xbox2.GetPOV() == 0)
    {
        return 1;
    }
    else if (Xbox2.GetPOV() == 180 || Xbox2.GetBumper(frc::XboxController::kRightHand))
    {
        return -1;
    }
    else
    {
        return 0.0;
    }
}

float OI::fTopFeederSpeed()
{
    if(Xbox2.GetPOV() == 90)
    {
        return -.7;
    }
    else if(Xbox2.GetPOV() == 0)
    {
        return -.7;
    }
    else if (Xbox2.GetPOV() == 180 )
    {
        return .7;
    }
    else
    {
        return 0.0;
    }
}

float OI::fManualShootSpeed()
{
    float speed = Xbox2.GetTriggerAxis(frc::XboxController::JoystickHand::kRightHand);
    // if (Xbox3.GetPOV() == 0)
    // {
    //     speedMult += .01;
    // }
    // else if (Xbox3.GetPOV() == 180)
    // {
    //     speedMult -= .01;
    // }
    if(Xbox2.GetY(frc::XboxController::kLeftHand)<-.5)
    {
        speedMult += .01;
    }
    else if(Xbox2.GetY(frc::XboxController::kLeftHand)>.5)
    {
        speedMult -= .01;
    }
    frc::SmartDashboard::PutNumber("Speed Percent", speedMult);
    return speed* speedMult;
}

float OI::fManualHoodSpeed()
{
    return .3*Xbox2.GetY(frc::XboxController::JoystickHand::kRightHand);
}

float OI::fManualTurretSpeed()
{
    return Xbox2.GetX(frc::XboxController::JoystickHand::kRightHand);
}



bool OI::CPRotate()
{
    return Xbox1.GetXButtonPressed();
}
//==============================================================================

bool OI::AutoAim()
{
    return Xbox2.GetStartButton();
}
float OI::fClimbSpeed()
{
    // if(Xbox2.GetTriggerAxis(frc::XboxController::kRightHand) > 0.1 && Xbox2.GetTriggerAxis(frc::XboxController::kLeftHand) < 0.1)
    // {
    //     return Xbox2.GetTriggerAxis(frc::XboxController::kRightHand); 
    // } 
    // else if (Xbox2.GetTriggerAxis(frc::XboxController::kLeftHand) > 0.1 && Xbox2.GetTriggerAxis(frc::XboxController::kRightHand) < 0.1)  
    // {
    //     return -Xbox2.GetTriggerAxis(frc::XboxController::kLeftHand);
    // }
    // else
    // {
    //     return 0;
    // }
    if (Xbox1.GetPOV() == 0)
    {
        return -.75;
    }
    else if (Xbox1.GetPOV() == 180)
    {
        return .75;
    }
    else 
    {
        return 0;
    }
}

bool OI::bClimbUp()
{
    if(Xbox2.GetBumperPressed(frc::XboxController::kLeftHand))
    {
        climbUp = !climbUp;
    }
    return climbUp;
}

bool OI::CPToColor()
{
    return Xbox3.GetBumper(frc::XboxController::kRightHand);
}

// ----------------------------------------------------------------------------
// Test commands
// ----------------------------------------------------------------------------

// Designate some buttons as test buttons just to be able to test
// some functionality.
bool OI::bTestButton(int iButton)
    {
    bool    bButtonValue;
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
        case 7:
            bButtonValue = Xbox1.GetBButton();
            break;
        case 8:
            bButtonValue = Xbox3.GetAButtonPressed();
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
        case 6 :
            fControlValue = Xbox2.GetX(frc::XboxController::kRightHand);
            break;
        default :
            fControlValue = 0.0;
            break;
    }

    return fControlValue;
}

float OI::fTestSelector(float increment)
{
    static float fValue = 0;
    if(Xbox2.GetPOV() == 0)
    {
        fValue += increment;
    }
    else if(Xbox2.GetPOV() == 180)
    {
        fValue -= increment;
    }

    return fValue;
}