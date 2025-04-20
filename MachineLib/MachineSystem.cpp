/**
 * @file MachineSystem.cpp
 * @author Adi M
 */

#include "pch.h"
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include "MachineSystem.h"
#include "Machine.h"
#include "MachineFactory1.h"
#include "MachineFactory2.h"

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
    
    // Create machine factories
    mFactory1 = std::make_shared<MachineFactory1>(mResourcesDir);
    mFactory2 = std::make_shared<MachineFactory2>(mResourcesDir);
    
    // Create initial machine (machine #1)
    ChooseMachine(1);
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
        mMachine->Draw(graphics, mPosition);
    }
}

/**
 * Set the current machine animation frame
 * @param frame Frame number
 */
void MachineSystem::SetMachineFrame(int frame)
{
    mFrame = frame;
    
    // Compute time in seconds based on frame rate
    if (mFrameRate > 0)
    {
        mTime = double(frame) / mFrameRate;
    }
    
    // Check if the machine should be running based on start/end times
    mIsRunning = (mTime >= mStartTime) && (mEndTime == 0 || mTime <= mEndTime);
    
    if (mMachine != nullptr)
    {
        if (mIsRunning)
        {
            // If running, update with the time since start
            double runningTime = mTime - mStartTime;
            mMachine->SetTime(runningTime);
        }
        else
        {
            // If not running, set to time 0 (stopped state)
            mMachine->SetTime(0);
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
    mMachineNum = machine;
    
    // Create a machine based on the machine number
    switch(machine)
    {
        case 1:
            if (mFactory1 != nullptr)
            {
                mMachine = mFactory1->Create();
            }
            break;
            
        case 2:
            if (mFactory2 != nullptr)
            {
                mMachine = mFactory2->Create();
            }
            break;
            
        default:
            // Default to machine 1 if invalid number
            if (mFactory1 != nullptr)
            {
                mMachine = mFactory1->Create();
            }
            break;
    }
    
    if (mMachine != nullptr)
    {
        mMachine->SetMachineNum(machine);
        
        // Apply current time if the machine is running
        if (mIsRunning && mTime >= mStartTime)
        {
            double runningTime = mTime - mStartTime;
            mMachine->SetTime(runningTime);
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
    mFlag = flag;
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
        mMachine->SetTime(time);
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
