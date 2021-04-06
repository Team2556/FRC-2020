// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "BallTracker.h"

BallTracker::BallTracker()
{
    pPrefs = frc::Preferences::GetInstance();
    cvSink = frc::CameraServer::GetInstance()->GetVideo();
}

void BallTracker::Init()
{
    HueLo = pPrefs->GetInt("Target Hue Lo", 0);
    HueHi = pPrefs->GetInt("Target Hue Hi", 255);
    SatLo = pPrefs->GetInt("Target Sat Lo", 0);
    SatHi = pPrefs->GetInt("Target Sat Hi", 255);
    ValLo = pPrefs->GetInt("Target Val Lo", 250);
    ValHi = pPrefs->GetInt("Target Val Hi", 255);

    pPrefs->PutInt("Target Hue Lo", HueLo);
    pPrefs->PutInt("Target Hue Hi", HueHi);
    pPrefs->PutInt("Target Sat Lo", SatLo);
    pPrefs->PutInt("Target Sat Hi", SatHi);
    pPrefs->PutInt("Target Val Lo", ValLo);
    pPrefs->PutInt("Target Val Hi", ValHi);
    trackingThread = new std::thread(&BallTracker::TrackThread, this);
    trackingThread->detach();\
}

void BallTracker::UpdateThreshold()
{
    HueLo = pPrefs->GetInt("Target Hue Lo", 0);
    HueHi = pPrefs->GetInt("Target Hue Hi", 255);
    SatLo = pPrefs->GetInt("Target Sat Lo", 0);
    SatHi = pPrefs->GetInt("Target Sat Hi", 255);
    ValLo = pPrefs->GetInt("Target Val Lo", 250);
    ValHi = pPrefs->GetInt("Target Val Hi", 255);

    pPrefs->PutInt("Target Hue Lo", HueLo);
    pPrefs->PutInt("Target Hue Hi", HueHi);
    pPrefs->PutInt("Target Sat Lo", SatLo);
    pPrefs->PutInt("Target Sat Hi", SatHi);
    pPrefs->PutInt("Target Val Lo", ValLo);
    pPrefs->PutInt("Target Val Hi", ValHi);
}
std::vector<FoundBall> BallTracker::getBalls()
{
    getBallsLock.lock();
    std::vector<FoundBall> tempBalls = balls;
    getBallsLock.unlock();
    return balls;
}

int BallTracker::partition(std::vector<std::vector<cv::Point>> &values, int left, int right) {
    int pivotIndex = left + (right - left) / 2;
    double pivotValue = cv::contourArea(values[pivotIndex]);
    int i = left, j = right;
    std::vector<cv::Point> temp;
    while(i <= j) {
        while(cv::contourArea(values[i]) < pivotValue) {
            i++;
        }
        while(cv::contourArea(values[j]) > pivotValue) {
            j--;
        }
        if(i <= j) {
            temp = values[i];
            values[i] = values[j];
            values[j] = temp;
            i++;
            j--;
        }
    }
    return i;
}

void BallTracker::sortContours(std::vector<std::vector<cv::Point>> &values, int left, int right)
{
    if(left < right) {
        int pivotIndex = partition(values, left, right);
        sortContours(values, left, pivotIndex - 1);
        sortContours(values, pivotIndex, right);
    }
}

void BallTracker::update()
{
    int     iCenterX, iCenterY;
    int     iMatchesFound;
    int     bTargetTracked;

    cv::Mat                                 FrameCam;
    cv::Mat                                 FrameHsv;
    cv::Mat                                 FrameThreshold;
//  cv::Mat                                 FrameEdges;
    cv::Mat                                 FrameDraw;
    cv::Mat                                 FrameCamStatus;

    std::vector< std::vector<cv::Point> >   Contours;

    while (cvSink.GrabFrame(FrameCam) == 0) {};

    cv::cvtColor(FrameCam, FrameHsv,  cv::COLOR_BGR2HSV);

    cv::inRange(FrameHsv, cv::Scalar(HueLo, SatLo, ValLo), cv::Scalar(HueHi, SatHi, ValHi), FrameThreshold);

    cv::findContours(FrameThreshold, Contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

    sortContours(Contours, 0, Contours.size() - 1);

    std::vector<FoundBall>   frameBalls;

    for(int i = 0; i < Contours.size(); i++)
    {
        cv::Rect tempRect = cv::boundingRect(Contours[i]);
        frameBalls.push_back(FoundBall(tempRect.x, tempRect.y, cv::contourArea(Contours[i])));
    }

    getBallsLock.lock();
    balls.clear();
    for(int i = 0; i < frameBalls.size(); i++)
    {
        balls.push_back(frameBalls[i]);
    }
    getBallsLock.unlock();
}

void BallTracker::TrackThread()
{
    while(true)
    {
        this->update();
    }
}