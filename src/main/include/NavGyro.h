/*
 * NavGyro.h
 *
 *  Created on: Feb 1, 2018
 *      Author: team2556
 */
#define NAVX
//#define ADXRS_GYRO

#ifndef SRC_NAVGYRO_H_
#define SRC_NAVGYRO_H_

#ifdef NAVX
#include <AHRS.h>
#endif

#ifdef ADXRS_GYRO
#include "frc/wpilib.h"
#endif

class NavGyroYawOutput;

// ============================================================================

class NavGyro : public frc::PIDSource
{
public:
    // Constructor / Destructor
    NavGyro();
    virtual ~NavGyro();

private:
    // Data
#ifdef NAVX
    AHRS                * pNavX;
#endif
#ifdef ADXRS_GYRO
    frc::ADXRS450_Gyro  * pADXRS;
#endif

public:
    NavGyroYawOutput    * pYawPIDOutput;
    PIDController       * pYawPID;

    float		fGyroCommandYaw;
    float       fYawPIDValue;
    float       fCommandTilt;
//    bool        bPIDEnabled;
    bool		bPresetTurning; // GET RID OF THIS!!!!

    // Methods
    void    Init(bool vPIDEnable = false);
    void    UpdateValues();
    void    SetCommandYaw(float fAngle);
    void    SetCommandYawToCurrent();
    bool    GetPresetTurning();
    bool    GetPresetTurning(float AllowableError);
    void    ResetYaw();
    float   GetYaw();
    float   GetYawError();
    float   GetTiltError();
    void    ResetTilt();
	float   FindRoll();
//    float  CorrectRotate(float fRotateLess);
    float   GetTilt();
    float   GetRoll();
    float   GetRotate(float fRotateMax = 0.5);

    void    PIDEnable(bool bEnable);
    double  PIDGet();

#ifdef NAVX
    float	GetDisplacemetX();
    float	GetDisplacemetY();
    float	GetDisplacemetZ();
#endif
    
};

// ============================================================================

class NavGyroYawOutput : public frc::PIDOutput
{
public:
    NavGyroYawOutput(float * pfYawPIDVar) : pfYawPID(pfYawPIDVar) {}

    float       * pfYawPID;

    void PIDWrite(double dOutput) { *pfYawPID = dOutput; }
};


#endif /* SRC_NAVGYRO_H_ */