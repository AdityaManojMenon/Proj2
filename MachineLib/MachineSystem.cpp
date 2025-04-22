/**
 * @file MachineSystem.cpp
 * @author Aditya Menon
 */
 
#include "pch.h"
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include "MachineSystem.h"
#include "Machine.h"
#include "MachineFactory1.h"
#include "MachineFactory2.h"
#include "Component.h"

/// The images directory
const std::wstring ImagesDirectory = L"/images";

/**
 * Constructor
 * @param resourcesDir Directory for resources
 */
MachineSystem::MachineSystem(const std::wstring& resourcesDir)
{
    mResourcesDir = resourcesDir;
    
    // If resource directory isn't provided, use executable path
    if (mResourcesDir.empty())
    {
        // Get directory the executable is in
        auto exePath = wxStandardPaths::Get().GetExecutablePath();
        mResourcesDir = wxFileName(exePath).GetPath().ToStdWstring();
    }
    
    // Set up the images directory
    imageDir = mResourcesDir + ImagesDirectory;
    
    // Initialize default values
    mFrameRate = 30.0;      // Default to 30 frames per second
    mMachineNum = 1;        // Default to machine 1
    mFrame = 0;
    mTime = 0;
    mPosition = wxPoint(400, 400);  // Set machine at center of window
    
    // Create machine factories
    mFactory1 = MachineFactory1::Create(mResourcesDir);
    mFactory2 = MachineFactory2::Create(mResourcesDir);
    
    // Create initial machine (machine #1)
    mMachine = mFactory1->Create();
}

/**
 * Set the position for the root of the machine
 * @param location The x,y location to place the machine
 */
void MachineSystem::SetLocation(wxPoint location)
{
    mPosition = location;
}

/**
 * Get the location of the machine
 * @return Location x,y in pixels as a point
 */
wxPoint MachineSystem::GetLocation()
{
    return mPosition;
}

/**
 * Draw the machine at the currently specified location
 * @param graphics Graphics object to render to
 */
void MachineSystem::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Just forward to the machine's Draw function
    if (mMachine != nullptr)
    {
        // Draw the machine
        mMachine->Draw(graphics, mPosition);
    }
    else
    {
        // If machine is null, draw a visual indication
        graphics->SetBrush(wxBrush(wxColour(255, 0, 0)));
        graphics->DrawRectangle(mPosition.x, mPosition.y, 100, 100);
    }
}

/**
 * Set the current machine animation frame
 * @param frame Frame number
 */
void MachineSystem::SetMachineFrame(int frame)
{
    mFrame = frame;
    
    // Compute the new machine time
    double machineTime = mFrame / mFrameRate;
    
    // If we are at a valid frame rate
    if (mFrameRate > 0)
    {
        if (machineTime >= mStartTime && (mEndTime <= 0 || machineTime <= mEndTime))
        {
            // Machine is running
            mIsRunning = true;
            
            // Compute the time relative to the start time
            double runningTime = machineTime - mStartTime;
            
            // Set the machine time
            this->SetTime(runningTime);
        }
        else
        {
            // Machine is not running
            mIsRunning = false;
            
            // Reset the machine
            this->SetTime(0);
        }
    }
}

/**
 * Set the expected frame rate in frames per second
 * @param rate Frame rate in frames per second
 */
void MachineSystem::SetFrameRate(double rate)
{
    mFrameRate = rate;
}

/**
 * Set the machine number
 * @param machine An integer number. Each number makes a different machine
 */
void MachineSystem::ChooseMachine(int machine)
{
    if (machine != mMachineNum)
    {
        mMachineNum = machine;
        
        switch (machine)
        {
        case 1:
            mMachine = mFactory1->Create();
            break;
            
        case 2:
            mMachine = mFactory2->Create();
            break;
            
        default:
            // If invalid machine number, default to machine 1
            mMachine = mFactory1->Create();
            break;
        }
        
        double machineTime = mFrame / mFrameRate;
        
        if (machineTime >= mStartTime && (mEndTime <= 0 || machineTime <= mEndTime))
        {
            // Machine is running
            double runningTime = machineTime - mStartTime;
            
            // Set the machine time
            this->SetTime(runningTime);
        }
    }
}

/**
 * Get the current machine number
 * @return Machine number integer
 */
int MachineSystem::GetMachineNumber()
{
    return mMachineNum;
}

/**
 * Get the current machine time.
 * @return Machine time in seconds
 */
double MachineSystem::GetMachineTime()
{
    return mTime;
}

/**
 * Set the flag from the control panel
 * @param flag Flag to set
 */
void MachineSystem::SetFlag(int flag)
{
    if (mMachine != nullptr)
    {
        mMachine->SetFlag(flag);
    }
}

/**
 * Set the time for this machine
 * @param time Time in seconds
 */
void MachineSystem::SetTime(double time)
{
    mTime = time;
    
    if (mMachine != nullptr)
    {
        // Get the components from the machine
        auto& components = mMachine->GetComponents();
        
        // First pass: update all components for time
        for(auto component : components)
        {
            component->SetTime(time);
        }
        
        // Second pass: ensure rotation propagation
        for(auto component : components)
        {
            component->SetTime(time);
        }
        
        // Third pass to fully synchronize
        for(auto component : components)
        {
            component->SetTime(time);
        }
    }
}

/**
 * Set the start time for this machine
 * @param startTime Time in seconds when the machine starts
 */
void MachineSystem::SetStartTime(double startTime)
{
    mStartTime = startTime;
}

/**
 * Set the end time for this machine
 * @param endTime Time in seconds when the machine stops (0 means run indefinitely)
 */
void MachineSystem::SetEndTime(double endTime)
{
    mEndTime = endTime;
}

/**
 * Determine if the machine should be running at the current time
 * @return true if running
 */
bool MachineSystem::IsRunning()
{
    return mIsRunning;
}

/**
 * Hit test on the machine
 * @param pos Position to test
 * @return true if pos is within the machine
 */
bool MachineSystem::HitTest(wxPoint pos)
{
    if (mMachine != nullptr)
    {
        // Adjust position relative to machine location
        wxPoint relativePt(pos.x - mPosition.x, pos.y - mPosition.y);
        return mMachine->HitTest(relativePt);
    }
    
    return false;
}
