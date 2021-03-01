/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "ctre/Phoenix.h"
#include "limits.h"
#include "frc/smartdashboard/SmartDashboard.h"

class TurretEncoder {
 public:
  TurretEncoder(phoenix::motorcontrol::SensorCollection * sensor);
  phoenix::motorcontrol::SensorCollection * sensor;
  


  int getPwmPosition();


 private:
  int lastValue = INT_MIN;
};

/**
 * Reads PWM values from the AS5600.
 */
// public class AS5600EncoderPwm {
//  private final SensorCollection sensors;
//  private volatile int lastValue = Integer.MIN_VALUE;
//  public AS5600EncoderPwm(SensorCollection sensors) {
//  this.sensors = sensors;
//  }
//  public int getPwmPosition() {
//  int raw = sensors.getPulseWidthRiseToFallUs();
//  if (raw == 0) {
//  int lastValue = this.lastValue;
//  if (lastValue == Integer.MIN_VALUE) {
//  return 0;
//  }
//  return lastValue;
//  }
//  int actualValue = Math.min(4096, raw - 128);
//  lastValue = actualValue;
//  return actualValue;
//  }
// }
// --------------------