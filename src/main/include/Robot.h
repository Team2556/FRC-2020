/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>
#include "RobotMap.h"
#include "OI.h"

#include <frc/WPILib.h>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include "rev/CANSparkMax.h"



class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;


  rev::CANSparkMax        MotorControl_L1{LEFT_DRIVE_1, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax        MotorControl_L2{LEFT_DRIVE_2, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax        MotorControl_R1{RIGHT_DRIVE_1, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax        MotorControl_R2{RIGHT_DRIVE_2, rev::CANSparkMax::MotorType::kBrushless};

  frc::SpeedControllerGroup   Left_Drive_Group{MotorControl_L1, MotorControl_L2};
  frc::SpeedControllerGroup   Right_Drive_Group{MotorControl_R1, MotorControl_R2};

  frc::DifferentialDrive WestCoastDrive{Left_Drive_Group, Right_Drive_Group};

  OI                      DriverCMD{};

  

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;
};
