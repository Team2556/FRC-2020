/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ControlPanel.h"

ControlPanel::ControlPanel(Robot * pRobot) {
    this->pRobot = pRobot;
}

//Display RGB values from V3 color sensor to smartdashboard
void ControlPanel::ColorTest() {
    frc::Color            detectedColor = ColorSensor.GetColor();
    CPDebug.PutNumber("Red Detected", detectedColor.red);
    CPDebug.PutNumber("Green Detected", detectedColor.green);
    CPDebug.PutNumber("Blue Detected", detectedColor.blue);
}

//return a letter R, G, B, or Y representing the different possible colors 
char ControlPanel::DetermineColor() {
    frc::Color            detectedColor = ColorSensor.GetColor();
    //create RGB array from sensor
    double colorsRGB[3] = {detectedColor.red, detectedColor.green, detectedColor.blue};
    float testVal = 0.35;
    if(colorsRGB[0] >= testVal && colorsRGB[1] <= testVal && colorsRGB[2] <= testVal) 
    {
        //Color is Red
        CPDebug.PutString("Color", "Red");
        return 'R';
    } 
    else if(colorsRGB[0] <= testVal && colorsRGB[1] >= testVal && colorsRGB[2] <= testVal) 
    {
        //Color is Green
        CPDebug.PutString("Color", "Green");
        return 'G';
    } 
    else if(colorsRGB[0] <= testVal && colorsRGB[1] >= testVal && colorsRGB[2] >= testVal) 
    {
        //Color is Blue
        CPDebug.PutString("Color", "Blue");
        return 'B';
    } 
    else if(colorsRGB[0] >= testVal && colorsRGB[1] >= testVal && colorsRGB[2] <= testVal) 
    {
        //Color is Yellow
        CPDebug.PutString("Color", "Yellow");
        return 'Y';
    }
    else return 'X';
}


void ControlPanel::Rotate(int spinNum) {
    //sets colorNum as a one letter string representing the first letter of red, green, blue, and yellow
    const char colorNumInit = ControlPanel::DetermineColor();
    //basically calling DetermineColor() but more optimized
    char colorNum = colorNumInit;
    //how many rotations have been completed
    int rotations = 0;
    bool newColor = false;
    if(rotations < spinNum)
    {
        //Talon spins the control panel
        pRobot->CtrlPanelMotor.Set(ControlMode::PercentOutput, 0.5);
        //Once the control panel is spun off of the init color, it is a new color
        if(ControlPanel::DetermineColor() != colorNumInit && newColor == false) newColor = true;
        
        if(colorNumInit == colorNum && newColor)
        {
            //a rotation has been completed
            rotations++;
            //ensures that a new color is found before iterating rotations again
            newColor = false;
        }

    }
    
    CPDebug.PutNumber("Rotations", rotations);

}


//===========================================================================================================
//Rotates to the color returned from game data
//===========================================================================================================
void ControlPanel::RotateToColor()
{
    {
        char colorNeeded = ControlPanel::GetColorNeeded();
        if(ControlPanel::DetermineColor() == colorNeeded)
        {
            return;
        }
        else
        {
            pRobot->CtrlPanelMotor.Set(ControlMode::PercentOutput, 0.5);
        }
    }
}


//this function is called from init when the B button is pressed
void ControlPanel::ManualRotate(int i) {
    //rotate the control panel
    pRobot->CtrlPanelMotor.Set(ControlMode::PercentOutput,  i * 0.5);

}


//find the color that robot needs to rotate control panel to
//Returns R, G, B, or Y
char ControlPanel::GetColorNeeded() {
    std::string gameData;
    gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
    return gameData[0];
}

bool ControlPanel::RotationControl(bool reset) {
    static int counter = 0;
    CPDebug.PutNumber("Rotate Counter", counter);
    if(reset)
    {
        counter = 0;
    }
    if(counter < 300) {
        pRobot->CtrlPanelMotor.Set(ControlMode::PercentOutput, 0.25);
        counter++;
        return false;
    } else {
        counter = 0;
        return true;
    }
}