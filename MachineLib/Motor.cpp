/**
 * @file Motor.cpp
 *
 * @author Aditya Menon
 */

#include "pch.h"
#include "Motor.h"
#include "Machine.h"

/**
 * Constructor
 * @param machine The machine this motor is part of
 */
Motor::Motor(Machine* machine) : Component(machine)
{
    // Create a blank polygon for the main component
    mPolygon.Rectangle(0, 0, 1, 1);
    mPolygon.SetColor(wxColour(0, 0, 0, 0)); // Transparent
    
    // Images are expected to be in the images directory - this is relative to application
    std::wstring imagesDir = L"images";
    
    // Create the motor body using motor3.png (stationary)
    mMotor.SetImage(imagesDir + L"/motor3.png");
    
    // Create a rectangle shape for the motor body - 80x80 square
    mMotor.Rectangle(-40, 10, 80, 80);
    
    // Create the pulley that will rotate inside the motor
    mShaft.SetImage(imagesDir + L"/pulley2.png");
    
    // Create a circle for the pulley - 30 pixels diameter
    mShaft.Circle(15);
    
    // Set rotation speed to exactly 1 rotation per second as specified
    mSpeed = 1.0;
}

/**
 * Set the position of this motor
 * @param x X position
 * @param y Y position
 */
void Motor::SetPosition(double x, double y)
{
    Component::SetPosition(x, y);
}

/**
 * Draw this motor
 * @param graphics Graphics context to draw on
 */
void Motor::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Draw the motor body (motor3.png) - stationary
    mMotor.DrawPolygon(graphics, mPosition.m_x, mPosition.m_y - 50);
    
    // Draw the rotating pulley in the middle of the motor
    mShaft.DrawPolygon(graphics, mPosition.m_x, mPosition.m_y - 78);
}

/**
 * Add a component to be driven by this motor
 * @param component Component to drive
 */
void Motor::AddComponent(std::shared_ptr<Component> component)
{
    mDriven.push_back(component);
}

/**
 * Test whether a point hits this object
 * @param pos Position to test
 * @return true if a hit, false otherwise
 */
bool Motor::HitTest(wxPoint pos)
{
    // Convert the point to relative coordinates
    double x = pos.x - mPosition.m_x;
    double y = pos.y - mPosition.m_y;
    
    // Check if it's inside the pulley (shaft) which is a circle
    double shaftX = x;
    double shaftY = y - 78;
    double shaftDistance = sqrt(shaftX * shaftX + shaftY * shaftY);
    if (shaftDistance <= 15)  // 15 is the radius of the shaft circle
    {
        return true;
    }
    
    // Check if it's inside the motor body (rectangle)
    if (x >= -40 && x <= 40 && y - 50 >= -40 && y - 50 <= 40)
    {
        return true;
    }
    
    return false;
}

/**
 * Set the current time
 * @param time Current time in seconds
 */
void Motor::SetTime(double time)
{
    // Only calculate rotation when the motor is running
    if (mRunning)
    {
        // Calculate rotation based on time and speed
        // For exactly 1 rotation per second, we only need the fractional part
        // of the time, multiplied by 2π for a full circle
        double rotationInTurns = fmod(time, 1.0);
        
        // Set the component rotation (0-1 range)
        mRotation = rotationInTurns;
        
        // Set the shaft rotation in radians (0-2π range)
        // 2π radians = 1 full turn (360 degrees)
        mShaft.SetRotation(rotationInTurns * 2 * M_PI);
        
        // Update all driven components 
        for (auto component : mDriven)
        {
            component->SetRotation(rotationInTurns);
        }
    }
} 

