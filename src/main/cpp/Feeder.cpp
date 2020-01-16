/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Feeder.h"

Feeder::Feeder(Robot * pRobot) {
    this->pRobot = pRobot;
}
//up function, down function


//========================================================================================================
//Function to spin balls to go up feeder
//========================================================================================================
void Feeder::GoUpManual(float power) {
    pRobot->FeederMotor.Set(ControlMode::PercentOutput, power);
}