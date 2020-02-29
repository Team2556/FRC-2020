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
    frc::SmartDashboard::PutNumber("Red Detected", detectedColor.red);
    frc::SmartDashboard::PutNumber("Green Detected", detectedColor.green);
    frc::SmartDashboard::PutNumber("Blue Detected", detectedColor.blue);
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
        frc::SmartDashboard::PutString("Color", "Red");
        return 'R';
    } 
    else if(colorsRGB[0] <= testVal && colorsRGB[1] >= testVal && colorsRGB[2] <= testVal) 
    {
        //Color is Green
        frc::SmartDashboard::PutString("Color", "Green");
        return 'G';
    } 
    else if(colorsRGB[0] <= testVal && colorsRGB[1] >= testVal && colorsRGB[2] >= testVal) 
    {
        //Color is Blue
        frc::SmartDashboard::PutString("Color", "Blue");
        return 'B';
    } 
    else if(colorsRGB[0] >= testVal && colorsRGB[1] >= testVal && colorsRGB[2] <= testVal) 
    {
        //Color is Yellow
        frc::SmartDashboard::PutString("Color", "Yellow");
        return 'Y';
    }
    else return 'X';
}



//====================================================================================================================
//Rotate
//====================================================================================================================
//returns false until the panel is rotated to spinNum rotations
bool ControlPanel::Rotate(int spinNum) {

    if(!ServoDown()) {
        ServoDown();
        return false;
    }

    frc::SmartDashboard::PutNumber("Rotations", rotations);

    //sets colorNum as a one letter string representing the first letter of red, green, blue, and yellow
    static char colorNumInit = DetermineColor();
    //basically calling DetermineColor() but cooler
    char colorNum = colorNumInit;
    //how many rotations have been completed
    bool newColor = false;
    if(rotations < spinNum)
    {
        //Talon spins the control panel
        pRobot->CtrlPanelMotor.Set(ControlMode::PercentOutput, 0.5);
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
        return true;
    }

    return false;
}


//===========================================================================================================
//Rotates to the color returned from game data
//===========================================================================================================
bool ControlPanel::RotateToColor(char givenColor)
{
    if(!ServoDown()) {
        ServoDown();
        return false;
    }

    char colorNeeded = givenColor;
    try
    {
        colorNeeded = GetColorNeeded();
        frc::SmartDashboard::PutString("GameData", "Rotating to " + colorNeeded);
    }
    catch(std::exception) 
    {
        frc::SmartDashboard::PutString("GameData", "No GameData Color");
    }

    if(DetermineColor() == colorNeeded)
    {
        ServoUp();
        return true;
    }
    else
    {
        pRobot->CtrlPanelMotor.Set(ControlMode::PercentOutput, 0.5);
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
char ControlPanel::GetColorNeeded() {
    std::string gameData;
    gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
    return gameData[0];
}


//Set the servo to either up or down on function call, becomes true once the servo is at desired position
bool ControlPanel::ServoUp() {
    pRobot->CtrlServo.SetAngle(0);
    if(pRobot->CtrlServo.GetAngle() == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool ControlPanel::ServoDown() {
    pRobot->CtrlServo.SetAngle(90);
    if(pRobot->CtrlServo.GetAngle() == 90) {
        return true;
    }
    else {
        return false;
    }
}