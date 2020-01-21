/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "frc/wpilib.h"
#include "RobotMap.h"

class OI {
 public:
  OI();

  //General Functions
  void UpdateOI();

  float fMoveForward();
  float fRotate();
  float fStrafe(); //this is just for use when testing with mecanum

  float fClimb();

  


  enum DriveMode{Unknown, Manual, Automatic};
  enum TransmissionState{High, Low};

  TransmissionState       DriveGear;
  DriveMode               CurrDriveMode;



  bool CPRotate();
  float CPManualRotate();
  bool CPToColor();

  // Test commands
  bool      bTestButton(int iButton);
  float     fTestValue(int iControl);


  protected:
    frc::XboxController   Xbox1{XBOX_ONE};
    frc::XboxController   Xbox2{XBOX_TWO};
};
