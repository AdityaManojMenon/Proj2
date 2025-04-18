/**
 * @file MachineSystem.cpp
 *
 * @author Aditya Menon
 */

#include "pch.h"
#include "MachineSystem.h"
#include "Machine.h"

/**
 * Constructor
 * @param resourcesDir Path to the resources directory
 */
MachineSystem::MachineSystem(std::wstring resourcesDir) : mResourcesDir(resourcesDir)
{
    // Create an empty machine - will be replaced in ChooseMachine
    mMachine = std::make_shared<Machine>();
}

/**
 * Set the position for the root of the machine
 * @param location The x,y location to place the machine
 */
void MachineSystem::SetLocation(wxPoint location)
{
    mMachine->SetLocation(location);
}

/**
 * Get the location of the machine
 * @return Location x,y in pixels as a point
 */
wxPoint MachineSystem::GetLocation()
{
    return mMachine->GetLocation();
}

/**
 * Draw the machine at the currently specified location
 * @param graphics Graphics object to render to
 */
void MachineSystem::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
    mMachine->DrawMachine(graphics);
}

/**
 * Set the current machine animation frame
 * @param frame Frame number
 */
void MachineSystem::SetMachineFrame(int frame)
{
    mMachine->SetMachineFrame(frame);
}

/**
 * Set the expected frame rate in frames per second
 * @param rate Frame rate in frames per second
 */
void MachineSystem::SetFrameRate(double rate)
{
    mMachine->SetFrameRate(rate);
}

/**
 * Set the machine number
 * @param machine An integer number. Each number makes a different machine
 */
void MachineSystem::ChooseMachine(int machine)
{
    // Access the globally declared machines from MachineSystemFactory.cpp
    extern std::shared_ptr<Machine> gMachine1;
    extern std::shared_ptr<Machine> gMachine2;
    
    if (machine == 1 && gMachine1 != nullptr)
    {
        mMachine = gMachine1;
        // Make sure the machine number is set correctly
        mMachine->ChooseMachine(1);
    }
    else if (machine == 2 && gMachine2 != nullptr)
    {
        mMachine = gMachine2;
        // Make sure the machine number is set correctly
        mMachine->ChooseMachine(2);
    }
    else 
    {
        // Fallback to the original behavior
        mMachine->ChooseMachine(machine);
    }
}

/**
 * Get the current machine number
 * @return Machine number integer
 */
int MachineSystem::GetMachineNumber()
{
    return mMachine->GetMachineNumber();
}

/**
 * Get the current machine time.
 * @return Machine time in seconds
 */
double MachineSystem::GetMachineTime()
{
    return mMachine->GetMachineTime();
}

/**
 * Set the flag from the control panel
 * @param flag Flag to set
 */
void MachineSystem::SetFlag(int flag)
{
    mMachine->SetFlag(flag);
} 