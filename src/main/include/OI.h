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
  bool BreakAuto();


  //Driver Commands
  float fMoveForward();
  float fRotate();
  float fTankLeft();
  float fTankRight();
  float fStrafe(); //this is just for use when testing with mecanum
  bool  bManualRotate();


  

  
  enum DriveMode{Unknown, Manual, Automatic};
  enum TransmissionState{High, Low};

  TransmissionState       DriveGear;
  DriveMode               CurrDriveMode;

  bool flipDrive = false;

//CoDriver COmmands

  bool Shoot();
  bool EndShoot();

//intake
  bool IntakeOut();
  bool RunIntake();
  bool ReverseIntake();
  bool bIntakeOut;
  bool bLimeLightOff = false;

//feeder
  float fBottomFeederSpeed();
  float fTopFeederSpeed();
  float speedMult = .9;

//shooter
  bool bShooterOpen();
  bool AutoAim();
  float fManualShootSpeed();
  float fManualHoodSpeed();
  float fManualTurretSpeed();  


  //control pannel
  bool CPRotate();
  float CPManualRotate();
  bool CPToColor();
  
  //climb
  int moveOnBar = 0;
  bool BarRoll();
  float fClimbSpeed();
  bool bClimbUp();
  bool climbUp = false;

  // Test commands
  bool      bTestButton(int iButton);
  float     fTestValue(int iControl);

  float     fTestSelector(float increment = .1);


  protected:
    frc::XboxController   Xbox1{XBOX_ONE};
    frc::XboxController   Xbox2{XBOX_TWO};
    frc::XboxController   Xbox3{XBOX_THREE};
};
