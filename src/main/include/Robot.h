/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include "ctre\Phoenix.h"
#include "AHRS.h"
#include "frc/WPILib.h"
#include <frc/PowerDistributionPanel.h>
#include <iostream>
#include "rev/CANSparkMax.h"
#include "rev/ColorSensorV3.h"
#include <frc/util/Color.h>
#include <frc/DriverStation.h>


class Robot : public frc::TimedRobot {
 public:



  PowerDistributionPanel    PDP{0};
  frc::Preferences       *  pPrefs;

  WPI_TalonSRX    FeederMotor{CAN_FEEDER};

  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;
};
