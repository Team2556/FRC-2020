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
    ServoDown();
    frc::Color            detectedColor = ColorSensor.GetColor();
    frc::SmartDashboard::PutNumber("Red Detected", detectedColor.red);
    frc::SmartDashboard::PutNumber("Green Detected", detectedColor.green);
    frc::SmartDashboard::PutNumber("Blue Detected", detectedColor.blue);
}

//return a letter R, G, B, or Y representing the different possible colors 
int ControlPanel::DetermineColor() {
    frc::Color            detectedColor = ColorSensor.GetColor();
    //create RGB array from sensor
    double colorsRGB[3] = {detectedColor.red, detectedColor.green, detectedColor.blue};
    float testVal = 0.35;
    if(colorsRGB[0] >= 0.45) 
    {
        //Color is Red
        frc::SmartDashboard::PutString("Color", "Red");
        return 0;
    } 
    else if(colorsRGB[0] <= testVal && colorsRGB[1] >= testVal && colorsRGB[2] <= testVal) 
    {
        //Color is Green
        frc::SmartDashboard::PutString("Color", "Green");
        return 1;
    } 
    else if(colorsRGB[0] <= testVal && colorsRGB[1] >= testVal && colorsRGB[2] >= testVal) 
    {
        //Color is Blue
        frc::SmartDashboard::PutString("Color", "Blue");
        return 2;
    } 
    else if(colorsRGB[0] >= 0.3 && colorsRGB[1] >= testVal && colorsRGB[2] <= testVal) 
    {
        //Color is Yellow
        frc::SmartDashboard::PutString("Color", "Yellow");
        return 3;
    }
    else return -1;
}



//====================================================================================================================
//Rotate
//====================================================================================================================
//returns false until the panel is rotated to spinNum rotations
bool ControlPanel::Rotate(int spinNum) {

    ServoDown();
    static int counter = 0;
    if(counter < 8)
    {
        counter++;
        return false;
    }

    frc::SmartDashboard::PutNumber("Rotations", rotations);

    //sets colorNum as a one letter string representing the first letter of red, green, blue, and yellow
    static int colorNumInit = DetermineColor();
    //basically calling DetermineColor() but cooler
    frc::SmartDashboard::PutNumber("Init Color", colorNumInit);
    int colorNum = DetermineColor();
    frc::SmartDashboard::PutNumber("Current Color", colorNum);
    //how many rotations have been completed
    static bool newColor = false;
    if(rotations < 2 * spinNum)
    {
        //Talon spins the control panel
        pRobot->CtrlPanelMotor.Set(ControlMode::PercentOutput, 0.2);
        //Once the control panel is spun off of the init color, it is a new color
        if(DetermineColor() != colorNumInit && newColor == false) newColor = true;
        
        if(colorNumInit == colorNum && newColor)
        {
            //a rotation has been completed
            rotations++;
            //ensures that a new color is found before iterating rotations again
            newColor = false;
        }

    }
    else {
        rotations = 0;
        ServoUp();
        counter = 0;
        return true;
    }

    return false;
}


//===========================================================================================================
//Rotates to the color returned from game data
//===========================================================================================================
bool ControlPanel::RotateToColor(int givenColor)
{
    ServoDown();
    static int counter = 0;
    if(counter < 8)
    {
        counter++;
        return false;
    }
    int colorNeeded = -1;
    if(GetColorNeeded() == -1) {
        colorNeeded = givenColor;
    }
    else {
        colorNeeded = GetColorNeeded();
    }
    int currColor = DetermineColor();
    frc::SmartDashboard::PutNumber("Rotating To:", colorNeeded);
    frc::SmartDashboard::PutNumber("Current Color", currColor);
    
    if(currColor == colorNeeded)
    {
        ServoUp();
        counter = 0;
        return true;
    }
    else
    {
        pRobot->CtrlPanelMotor.Set(ControlMode::PercentOutput, 0.2);
    }
    return false;
}


//this function is called from init when the B button is pressed
void ControlPanel::ManualRotate(int i) {
    //rotate the control panel
    pRobot->CtrlPanelMotor.Set(ControlMode::PercentOutput,  i * 0.5);

}


//find the color that robot needs to rotate control panel to
//Returns R, G, B, or Y
int ControlPanel::GetColorNeeded() {
    std::string gameData;
    gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
    if(gameData[0] == 'R')
    {
        return 1;
    }
    if(gameData[0] == 'G')
    {
        return 2;
    }
    if(gameData[0] == 'B')
    {
        return 3;
    }
    if(gameData[0] == 'Y')
    {
        return 0;
    }
    else 
    {
        return -1;
    }
}


//Set the servo to either up or down on function call, becomes true once the servo is at desired position
bool ControlPanel::ServoUp() {
    int angle = 135;
    pRobot->CtrlServo.SetAngle(angle);
    if(pRobot->CtrlServo.GetAngle() == angle) {
        return true;
    }
    else {
        return false;
    }
}

bool ControlPanel::ServoDown() {
    int angle = 80;
    pRobot->CtrlServo.SetAngle(angle);
    if(pRobot->CtrlServo.GetAngle() == angle) {
        return true;
    }
    else {
        return false;
    }
}