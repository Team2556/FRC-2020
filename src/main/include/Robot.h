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
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"


#include "RobotMap.h"
#include "OI.h"
#include "NavGyro.h"
#include "Limelight.h"
#include "GarminLidar.h"



class Robot : public frc::TimedRobot {
 public:



  PowerDistributionPanel    PDP{0};
  frc::Preferences       *  pPrefs;

  WPI_TalonSRX    FeederMotor{1};

  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestPeriodic() override;


  
  #ifndef MECANUM_DRIVE
  rev::CANSparkMax            MotorControl_L1{LEFT_DRIVE_1, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax            MotorControl_L2{LEFT_DRIVE_2, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax            MotorControl_R1{RIGHT_DRIVE_1, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax            MotorControl_R2{RIGHT_DRIVE_2, rev::CANSparkMax::MotorType::kBrushless};

  #endif

  rev::CANEncoder m_encoder = MotorControl_L1.GetEncoder();


  WPI_TalonSRX          MotorControl_LF{1};
  WPI_TalonSRX          MotorControl_RF{2};
  WPI_TalonSRX          MotorControl_LR{3};
  WPI_TalonSRX          MotorControl_RR{4};
  frc::MecanumDrive     RobotDrive{MotorControl_LF, MotorControl_LR, MotorControl_RF, MotorControl_RR};

  

  WPI_TalonSRX                Shooter_Motor_1{SHOOTER_1};
  WPI_TalonSRX                Shooter_Motor_2{SHOOTER_2};
  
  
  
  WPI_TalonSRX                Turret_Motor{TURRET};

  WPI_TalonSRX                Intake_Motor{CAN_INTAKE};
  WPI_TalonSRX                Feeder_Low_Motor{FEEDER_LOW};
  WPI_TalonSRX                Feeder_High_Motor{FEEDER_HIGH};
  WPI_TalonSRX                Hood_Motor{HOOD_LINKAGE};

  WPI_TalonSRX                CtrlPanelMotor{CPMOTOR};

  WPI_TalonSRX                ClimbingMotor{CLIMB_ROTATE_1};
  WPI_TalonSRX                WinchMotor{CLIMB_WINCH};
  


  #ifdef MECANUM_DRIVE
  frc::SpeedControllerGroup   Left_Drive_Group{Shooter_Motor_1};//MotorControl_L1, MotorControl_L2};
  frc::SpeedControllerGroup   Right_Drive_Group{Shooter_Motor_2};//MotorControl_R1, MotorControl_R2};
  #else
  frc::SpeedControllerGroup   Left_Drive_Group{MotorControl_L1, MotorControl_L2};
  frc::SpeedControllerGroup   Right_Drive_Group{MotorControl_R1, MotorControl_R2};
  #endif


  frc::DifferentialDrive      WestCoastDrive{Left_Drive_Group, Right_Drive_Group};
  
 
  OI                          DriverCMD;


  frc::DoubleSolenoid         Transmission{CAN_PCM, TRANSMISSION_LOW, TRANSMISSION_HIGH};
  frc::DoubleSolenoid         Intake_Solenoid{CAN_PCM, INTAKE_OUT, INTAKE_IN};
  frc::DoubleSolenoid         Shooter_Solenoid{CAN_PCM, SHOOTER_CLOSED, SHOOTER_OPEN};
  frc::DoubleSolenoid         Climb_Solenoid{CAN_PCM, CLIMB_UP, CLIMB_DOWN};

  Limelight                   MagicVision;
  NavGyro                     Nav;
  GarminLidar                 ShooterDistance;

  std::shared_ptr<NetworkTable> PixyTable = nt::NetworkTableInstance::GetDefault().GetTable("Pixy");

 //Test

float encoderstart;

  frc::SendableChooser<std::string> AutoChooser;

  const std::string AutoTeleop = "Teleop";
  const std::string Auto1 = "Auto 1";
  const std::string Auto2 = "Auto 2";
  const std::string Auto3 = "Auto 3";
  std::string AutoMode;


 private:
  
};
