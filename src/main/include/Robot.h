/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>



#include <frc/WPILib.h>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include "ctre\Phoenix.h"
#include "AHRS.h"
#include <frc/PowerDistributionPanel.h>
#include <iostream>
#include "rev/CANSparkMax.h"
#include "rev/ColorSensorV3.h"
#include <frc/util/Color.h>
#include <frc/DriverStation.h>
#include "rev/CANSparkMax.h"
#include "ctre/Phoenix.h"


#include "RobotMap.h"
#include "OI.h"
#include "Limelight.h"



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

  
  rev::CANSparkMax            MotorControl_L1{LEFT_DRIVE_1, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax            MotorControl_L2{LEFT_DRIVE_2, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax            MotorControl_R1{RIGHT_DRIVE_1, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax            MotorControl_R2{RIGHT_DRIVE_2, rev::CANSparkMax::MotorType::kBrushless};

/*
  WPI_TalonSRX          MotorControl_LF{1};
  WPI_TalonSRX          MotorControl_RF{2};
  WPI_TalonSRX          MotorControl_LR{3};
  WPI_TalonSRX          MotorControl_RR{4};
  frc::MecanumDrive     RobotDrive{MotorControl_LF, MotorControl_LR, MotorControl_RF, MotorControl_RR};
*/
  

  WPI_TalonSRX                Shooter_Motor_1{SHOOTER_1};
  WPI_TalonSRX                Shooter_Motor_2{SHOOTER_2};
  WPI_TalonSRX                Turret_Motor{TURRET};

  WPI_TalonSRX                CtrlPanelMotor{CPMOTOR};

  WPI_TalonSRX                ClimbingMotor{CLIMBMOTOR};




  
  frc::SpeedControllerGroup   Left_Drive_Group{MotorControl_L1, MotorControl_L2};
  frc::SpeedControllerGroup   Right_Drive_Group{MotorControl_R1, MotorControl_R2};

  frc::DifferentialDrive      WestCoastDrive{Left_Drive_Group, Right_Drive_Group};
  
 
  OI                          DriverCMD{};


  frc::DoubleSolenoid         Transmission{CAN_PCM, TRANSMISSION_LOW, TRANSMISSION_HIGH};

  Limelight                   MagicVision;

  

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;
};