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



float GarminLidar::read()
{
    uint8_t  distance_data[2];
    Lidar.Read(0x10, 2, distance_data);
    LidarDebug.PutNumber("High Bit", distance_data[1]);
    LidarDebug.PutNumber("Low Bit", distance_data[0]);
    uint16_t truedistance;
    truedistance = (distance_data[1]<<8) | (distance_data[0]);
    return truedistance;
}

int GarminLidar::IterativeDistance()
{
    
    static int prevValue = -1;
    // if(dioTrigger.Get())
    // {
    //     dioTrigger.Set(false);
    // }

    if(!dioMeasuring.Get())//this is when it is not measuring
    {
        prevValue = this->read();
        dioTrigger.Set(!dioTrigger.Get());
    }


    this->distance = prevValue;
    return prevValue;


}

bool GarminLidar::Connected()
{
    return !Lidar.AddressOnly();
}