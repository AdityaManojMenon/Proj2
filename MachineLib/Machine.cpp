/**
 * @file Machine.cpp
 *
 * @author Aditya Menon
 */

#include "pch.h"
#include "Machine.h"
#include "Motor.h"
#include "Component.h"


/**
 * Constructor
 */
Machine::Machine()
{
    // Initialize with a default frame rate of 30 frames per second
    // This means one complete rotation will take exactly 1 second
    // at speed = 1.0
    mFrameRate = 30.0;
}

/**
 * Draw the machine at the current location
 * @param graphics Graphics context to draw on
 */
void Machine::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();
    
    graphics->Translate(mLocation.x, mLocation.y);
    
    // Draw all machine components
    for (auto component : mComponents)
    {
        component->Draw(graphics);
    }
    
    graphics->PopState();
}

/**
 * Set the machine animation frame
 * @param frame Frame number
 */
void Machine::SetMachineFrame(int frame)
{
    mFrame = frame;
    
    // Calculate the time based on the frame rate
    // This converts frame numbers to seconds
    // Example: At 30fps, frame 30 = 1 second, frame 60 = 2 seconds
    double time = (double)frame / mFrameRate;
    
    // Update all components with the current time
    for (auto component : mComponents)
    {
        component->SetTime(time);
    }
}

/**
 * Choose which machine to create
 * @param machine Machine number
 */
void Machine::ChooseMachine(int machine)
{
    // Just set the machine number
    mMachineNumber = machine;
}

/**
 * Get the current machine time
 * @return Machine time in seconds
 */
double Machine::GetMachineTime() const
{
    return (double)mFrame / mFrameRate;
}

/**
 * Set the flag from the control panel
 * @param flag Flag to set
 */
void Machine::SetFlag(int flag)
{
    mFlag = flag;
    
    // Handle flag state changes
    if (mFlag == 1)
    {
        // Start machines at their designated times
        for (auto motor : mMotors)
        {
            motor->SetRunning(true);
        }
    }
    else if (mFlag == 0)
    {
        // Stop all machines
        for (auto motor : mMotors)
        {
            motor->SetRunning(false);
        }
    }
}

/**
 * Add a component to the machine
 * @param component Component to add
 */
void Machine::AddComponent(std::shared_ptr<Component> component)
{
    mComponents.push_back(component);
} 