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
    CPDebug.PutNumber("Red Detected", detectedColor.red);
    CPDebug.PutNumber("Green Detected", detectedColor.green);
    CPDebug.PutNumber("Blue Detected", detectedColor.blue);
    DetermineColor();
    // pRobot->CtrlPanelMotor.Set(ControlMode::PercentOutput, 0.25);

    // static int counter = 0;
    // static bool done = false;
    // if(DetermineColor() == 1 && done == false) {
    //     counter++;
    // }
    // else if(counter > 0 && DetermineColor() != 1) {
    //     done = true;
    // }
    // frc::SmartDashboard::PutNumber("Count", counter);
}

//return 0, 1, 2, or 3 representing red, green, blue, or yellow
int ControlPanel::DetermineColor() {
    //saves the last color to know when the next color on the wheel is being seen accurately
    //ensures that color blending is not an issue
    static int previousColor = -1;


    frc::Color            detectedColor = ColorSensor.GetColor();
    //create RGB array from sensor
    double colorsRGB[3] = {detectedColor.red, detectedColor.green, detectedColor.blue};
    
    
    if(colorsRGB[0] >= 0.4)
    {
        if(previousColor != 1 && previousColor != -1) //if previous color was not green, then the current color cannot be red.
        {
            return previousColor;
        }
        else
        {
            //Color is Red
            frc::SmartDashboard::PutString("Color", "Red");
            previousColor = 0;
            return 0;
        }
    } 
    else if(colorsRGB[2] >= 0.25) 
    {
        if(previousColor != 3 && previousColor != -1) //if previous color was not yellow, then the current color cannot be blue.
        {
            return previousColor;
        }
        else 
        {
            //Color is Blue
            CPDebug.PutString("Color", "Blue");
            previousColor = 2;
            return 2;
        }
    } 
    else if(colorsRGB[0] <= 0.3) 
    {
        if(previousColor != 2 && previousColor != -1)
        {
            return previousColor;
        }
        else
        {
            //Color is Green
            CPDebug.PutString("Color", "Green");
            previousColor = 1;
            return 1;
        }
    } 
    else
    {
        if(previousColor != 0 && previousColor != -1)
        {
            return previousColor;
        }
        else
        {
            //Color is Yellow
            CPDebug.PutString("Color", "Yellow");
            previousColor = 3;
            return 3;
        }
    }
}



//====================================================================================================================
//Rotate
//====================================================================================================================
//returns false until the panel is rotated to spinNum rotations
bool ControlPanel::Rotate(int spinNum) {

    ServoDown();
    static int counter = 0;
    if(counter < 25)
    {
        counter++;
        return false;
    }

    frc::SmartDashboard::PutNumber("Rotations", rotations);

    //sets colorNum to the number representing the color being read when function starts
    static int colorNumInit = DetermineColor();
    //if we rotate a second time, colorNum is what is read when function starts
    if(colorNumInit == -1)
    {
        colorNumInit = DetermineColor();
    }


    CPDebug.PutNumber("Init Color", colorNumInit);
    int colorNum = DetermineColor();
    CPDebug.PutNumber("Current Color", colorNum);
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
        colorNumInit = -1;
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
    if(counter < 25)
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
    CPDebug.PutNumber("Rotating To:", colorNeeded);
    CPDebug.PutNumber("Current Color", currColor);
    static bool spun = false;
    if(currColor == colorNeeded && spun)
    {
        ServoUp();
        counter = 0;
        spun = false;
        return true;
    }
    else
    {
        pRobot->CtrlPanelMotor.Set(ControlMode::PercentOutput, 0.2);
    }
    if(colorNeeded != currColor)
    {
        spun = true;
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
int ControlPanel::GetColorNeeded() 
{
    std::string gameData;
    gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();


    if(gameData[0] == 'R')
    {
        return 2;
    }
    if(gameData[0] == 'G')
    {
        return 3;
    }
    if(gameData[0] == 'B')
    {
        return 0;
    }
    if(gameData[0] == 'Y')
    {
        return 1;
    }
    else 
    {
        return -1;
    }
}

bool ControlPanel::RotationControl(bool reset) 
{
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