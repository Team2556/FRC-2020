/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "TurretEncoder.h"

TurretEncoder::TurretEncoder(phoenix::motorcontrol::SensorCollection * sensor) 
{
    this->sensor = sensor;
}

int TurretEncoder::getPwmPosition()
{
    int raw = sensor->GetPulseWidthRiseToFallUs();
    frc::SmartDashboard::PutNumber("Raw", raw);
    if (raw == 0)
    {
        int prevValue = this->lastValue;
    
        if(prevValue == INT_MIN)
        {
            return 0;
        }
        return prevValue;
    }
    int actualValue = std::min(4096, raw - 128);
    lastValue = actualValue;
    return actualValue;
}




