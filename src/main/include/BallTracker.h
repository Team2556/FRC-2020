// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <vector>
#include <mutex>
#include <thread>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>

#include "cameraserver/CameraServer.h"

#include "frc/Preferences.h"

#include "Debug.h"

class FoundBall
{
  public:
    FoundBall(int x, int y, int area)
    {
      this->x = x;
      this->y = y;
      this->area = area;
    }

    // copy constructor
    FoundBall(const FoundBall &old_obj)
    {
      this->x = old_obj.x;
      this->y = old_obj.y;
      this->area = old_obj.area;
    }

    int x;
    int y;
    int area;
};

class BallTracker {
 public:
  BallTracker();
  void Init();


  std::vector<FoundBall> getBalls();

  void TrackThread();
  void UpdateThreshold();

  Debug BallDebug{"Subsystems/BallTracker"};

  private:
    void update();
    void sortContours( std::vector<std::vector<cv::Point>> &values, int left, int right);
    int partition(std::vector<std::vector<cv::Point>> &values, int left, int right);
    std::vector<FoundBall> balls;
    std::mutex getBallsLock;
    cs::CvSink cvSink;
    std::thread * trackingThread;

    int               HueLo, HueHi;
    int		            SatLo, SatHi;
    int		            ValLo, ValHi;

    frc::Preferences *  pPrefs;
};
