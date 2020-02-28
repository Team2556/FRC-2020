/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "GarminLidar.h"
#include "frc/smartdashboard/SmartDashboard.h"

GarminLidar::GarminLidar() 
{

}

float GarminLidar::distance()
{
    Lidar.Write(0x00, 0x04);
    bool measuring = true;

    uint8_t  data[1];
    while (measuring)
    {
        
        Lidar.Read(0x01, 1, data);
        measuring = (data[0]%2) == 0;

    }
    uint8_t  distance_data[2];
    Lidar.Read(0x10, 2, distance_data);
    uint16_t truedistance;
    truedistance = (distance_data[1]<<8) | (distance_data[0] & 16);
    frc::SmartDashboard::PutNumber("High Bit", distance_data[1]);
    frc::SmartDashboard::PutNumber("Low Bit", distance_data[0]);
    return truedistance;
}

bool GarminLidar::Connected()
{
    return !Lidar.AddressOnly();
}