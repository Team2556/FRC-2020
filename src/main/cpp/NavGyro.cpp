/*
 * NavGyro.cpp
 *
 *  Created on: Feb 1, 2018
 *      Author: team2556
 */

// https://www.kauailabs.com/public_files/navx-mxp/apidocs/c++/class_a_h_r_s.html
// http://first.wpi.edu/FRC/roborio/release/docs/cpp/classfrc_1_1ADXRS450__Gyro.html

#include "frc/WPILib.h"

//#include "RobotMap.h"

#ifdef NAVX
#include <frc/AHRS.h>
#endif

#ifdef ADXRS_GYRO
#include <ADXRS450_Gyro.h>
#endif

#include <NavGyro.h>

float fNormalizeAngle360(float fAngle);
float fNormalizeAngle180(float fAngle);

// ============================================================================
// NavGyro
// ============================================================================

// ----------------------------------------------------------------------------
// Constructor / Destructor
// ----------------------------------------------------------------------------

NavGyro::NavGyro()
    {
#ifdef NAVX
    // Make the NavX control object
    pNavX = new AHRS(SPI::Port::kMXP);
#endif

#ifdef ADXRS_GYRO
    pADXRS = new frc::ADXRS450_Gyro(frc::SPI::Port::kOnboardCS0);
#endif

    pYawPIDOutput = new NavGyroYawOutput(&fYawPIDValue);
    pYawPID       = new frc::PIDController(0.05, 0.000, -0.00, this, pYawPIDOutput);
//    pYawPID->SetInputRange(-1.0, 1.0);
    pYawPID->SetOutputRange(-0.75, 0.75);
    pYawPID->Disable();
//    bPIDEnabled = false;

    }


// ----------------------------------------------------------------------------

NavGyro::~NavGyro()
    {
	// TODO Auto-generated destructor stub
    }

// ----------------------------------------------------------------------------
// Methods
// ----------------------------------------------------------------------------

void NavGyro::Init(bool bPIDEnableVal)
    {
    // Get the initial starting angle
#ifdef NAVX
    fGyroCommandYaw = pNavX->GetYaw();
    pNavX->ResetDisplacement();
#endif
#ifdef ADXRS_GYRO
//    pADXRS->Calibrate();
    fGyroCommandYaw = pADXRS->GetAngle();
#endif

    pYawPID->Reset();
    PIDEnable(bPIDEnableVal);

    }


// ----------------------------------------------------------------------------

#ifdef NAVX
void NavGyro::UpdateValues()
{
	float fAccelX    = pNavX->GetRawAccelX();
	float fAccelY    = pNavX->GetRawAccelY();
	int   UpdateRate = pNavX->GetRequestedUpdateRate();
	bool  bMoving    = pNavX->IsMoving();
	pNavX->UpdateDisplacement(fAccelX,fAccelY,UpdateRate,true);
}
#endif

//-----------------------------------------------------------------------------

void NavGyro::SetCommandYaw(float fAngle)
    {
    fGyroCommandYaw = fNormalizeAngle360(fAngle);
    }


// ----------------------------------------------------------------------------

void NavGyro::SetCommandYawToCurrent()
    {
#ifdef NAVX
    fGyroCommandYaw = pNavX->GetYaw();
#endif
#ifdef ADXRS_GYRO
    fGyroCommandYaw = pADXRS->GetAngle();
#endif
    }

// ----------------------------------------------------------------------------
#if 1
bool NavGyro::GetPresetTurning()
{
    if(fabs(this->GetYawError())<10)
    {
    	return false;
    }
    else
    {
        return true;
    }
}

bool NavGyro::GetPresetTurning(float AllowableError)
{
    if(fabs(this->GetYawError())<AllowableError)
    {
    	return false;
    }
    else
    {
        return true;
    }
}
#endif


// ----------------------------------------------------------------------------

float NavGyro::GetYaw()
{

    return pNavX->GetYaw(); 

}


// ----------------------------------------------------------------------------

void NavGyro::ResetYaw()
{
#if defined(NAVX)
    pNavX->Reset();
#endif
    SetCommandYawToCurrent();
}


// ----------------------------------------------------------------------------

float  NavGyro::GetYawError()
    {
    return fNormalizeAngle180(fGyroCommandYaw - GetYaw());
    }


//-----------------------------------------------------------------------------
#if 0
float  NavGyro::CorrectRotate(float fRotateLess)
{
	if(fRotateLess >  0.5)
	{
		fRotateLess =  0.5;
	}
	if(fRotateLess < -0.5)
	{
		fRotateLess = -0.5;
	}
	return fRotateLess;
}
#endif

//-----------------------------------------------------------------------------
float  NavGyro::GetRotate(float fRotateMax)
{
    float fRotateCmd;

    if (pYawPID->IsEnabled())
        {
        fRotateCmd = -fYawPIDValue;
        }
    else
        {
        // Calculate drive train rotate command value
        fRotateCmd = this->GetYawError() * 0.025; // .05 on comp bot -- Houston

        // Make use rotate command doesn't exceed max limits
        if (fRotateCmd >  fRotateMax) fRotateCmd =  fRotateMax;
        if (fRotateCmd < -fRotateMax) fRotateCmd = -fRotateMax;
        }

    return fRotateCmd;
}


//-----------------------------------------------------------------------------

float NavGyro::GetTilt()
{
#if defined(NAVX)
    return pNavX->GetPitch();
#else
    return 0.0;
#endif
}

float NavGyro::GetTiltError()
{
    return fCommandTilt - this->GetTilt();
}


void NavGyro::ResetTilt()
{
    fCommandTilt = this->GetTilt();
}
//-----------------------------------------------------------------------------

#if defined(NAVX)
//-----------------------------------------------------------------------------

float	NavGyro::GetDisplacemetX()
{
    // Get X displacement and convert to feet
	return	pNavX->GetDisplacementX() * 3.28084;
}


//-----------------------------------------------------------------------------

float	NavGyro::GetDisplacemetY()
{
    // Get X displacement and convert to feet
	return	pNavX->GetDisplacementY() * 3.28084;
}


//-----------------------------------------------------------------------------

float NavGyro::GetDisplacemetZ()
    {
    // Get Z displacement and convert to feet
	return	pNavX->GetDisplacementZ()*3.28084;
    }
#endif


// ----------------------------------------------------------------------------

void NavGyro::PIDEnable(bool bEnable)
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

// ----------------------------------------------------------------------------

// This overloads the virtual PIDGet in PIDSource. Necessary to use this
// in a PIDController.
double NavGyro::PIDGet()
    {
    float fYawError = GetYawError();
    if (fYawError < -5.0) fYawError = -5.0;
    if (fYawError >  5.0) fYawError =  5.0;
    return fYawError;
    }


// ----------------------------------------------------------------------------
// Utilities
// ----------------------------------------------------------------------------

// Normalize fAngle range from 0.0 to 360.0

float fNormalizeAngle360(float fAngle)
    {
    while (fAngle <    0.0) fAngle += 360.0;
    while (fAngle >= 360.0) fAngle -= 360.0;
    return fAngle;
    }


// ----------------------------------------------------------------------------

// Normalize fAngle range from +180.0 to -180.0

float fNormalizeAngle180(float fAngle)
    {
    while (fAngle <  -180.0) fAngle += 360.0;
    while (fAngle >=  180.0) fAngle -= 360.0;
    return fAngle;
    }