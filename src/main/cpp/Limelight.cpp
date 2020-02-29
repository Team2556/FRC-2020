/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Limelight.h"

Limelight::Limelight() 
{

}

double Limelight::Area()
{
    
    return table->GetNumber("ta",0.0);
}

double Limelight::Skew()
{
    return table->GetNumber("ts",0.0);
}

double Limelight::HorizontalOffset()
{
    return table->GetNumber("tx",0.0);
}

double Limelight::VerticalOffset()
{
    return table->GetNumber("ty",0.0);
}

void Limelight::SetValue(std::string Key, int Value)
{
    table->PutNumber(Key, Value);
}

double Limelight::Width()
{
    return table->GetNumber("thor", 0.0);
}

double Limelight::Height()
{
    return table->GetNumber("tvert", 0.0);
}

double Limelight::Angle()
{
    double angleconst = frc::SmartDashboard::GetNumber("Angle Constant", 0.0);
    frc::SmartDashboard::PutNumber("Angle Constant", angleconst);
    return (this->Width()/this->Height())*angleconst;
}

double Limelight::Ratio()
{
    return this->Width()/this->Height();
}

bool Limelight::HasTarget()
{
    float value = table->GetNumber("tv", 0);
    return value > .5;
}

void Limelight::TopRow()
{
    std::vector<double> temp;
    std::vector<double> cornY = table->GetNumberArray("tcorny", temp);
    std::vector<double> cornX = table->GetNumberArray("tcornx", temp);

    int length = cornY.size();
    bool used[8] = {false, false, false, false, false, false, false, false};

    int bestI;
    for(int i = 0; i < 4; i++)
    {
        bestI = 0;
        while(used[bestI])
        {
            bestI++;
        }

        for(int j = 0; j < length; j++)
        {
            if (cornY[j]<cornY[bestI] && used[j] == false)
            {
                bestI = j;
            }
        }
        results[i][0] = cornX[bestI];
        results[i][1] = cornY[bestI];
        used[bestI] = true;
    } 

    for (int i = 0; i < 4; i++)
    {
        for(int j = i+1; j < 4; j++)
        {
            if(results[j][0] < results[i][0]) 
            {
                double tempX = results[i][0];
                double tempY = results[i][1];
                results[i][0] = results[j][0];
                results[i][1] = results[j][1];
                results[j][0] = tempX;
                results[j][1] = tempY;
                //i = 0;
            }
        }
    }

    /*
    for(int j = 0; j<2;j++)
    {
        for(int i = 0; i<4;i++)
        {
            std::cout<<"   "<<results[i][j];
        }
        std::cout<<"\n";
    }
    std::cout<<"\n\n";
*/
}


void Limelight::GetDrive(float * fForward, float *fStrafe, float * fRotate, bool * bFOD)
{

    *bFOD = false;

    double widthL = (results[1][0] - results[0][0]);
    double widthR = (results[3][0] - results[2][0]);
    double p = frc::SmartDashboard::GetNumber("P", 1);
    double P2 = frc::SmartDashboard::GetNumber("P2", 1);
    double ratio = -1*(widthL-widthR)/widthR;

    *fRotate = ratio*p;
    *fStrafe = -ratio*P2;

    std::cout<<ratio<<"\n";
    
}

double Limelight::NewRatio()
{
    double widthL = (results[1][0] - results[0][0]);
    double widthR = (results[3][0] - results[2][0]);
    double p = frc::SmartDashboard::GetNumber("P", 1);
    double P2 = frc::SmartDashboard::GetNumber("P2", 1);
    double ratio = -1*(widthL-widthR)/widthR;


    return ratio;
}


float Limelight::GetDistanceToTarget() 
{
    const float targetWidth = 21.3205;
    float height = Height() / 240;
    float width =  Width() / 320;

    float distanceByHeight = height / tan(Angle());
    float leg1 = sqrt((targetWidth * targetWidth) - (width * width));
    float leg2 = sqrt((distanceByHeight * distanceByHeight) - (width * width));
    float distanceToOppSide = leg1 + leg2;

    float term1 = distanceToOppSide * distanceToOppSide;
    float term2 = (targetWidth * targetWidth)/4;
    float term3 = targetWidth * distanceToOppSide;
    float term4 = sqrt(1-((width/targetWidth) * width/targetWidth));

    float trueDistance = sqrt(term1 + term2 - (term3 * term4));
    return trueDistance;
}