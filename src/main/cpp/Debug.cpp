/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Debug.h"

Debug::Debug(std::string name) 
{
    table = nt::NetworkTableInstance::GetDefault().GetTable(name);
}

void Debug::PutString(std::string key, std::string value)
{
    table->PutString(key, value);
}

void Debug::PutNumber(std::string key, float value)
{
    table->PutNumber(key, value);
}

void Debug::PutBoolean(std::string key, bool value)
{
    table->PutBoolean(key, value);
}

