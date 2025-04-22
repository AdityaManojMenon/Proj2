/**
 * @file MachineSystem.h
 * @author Aditya Menon
 *
 * Implementation of the machine system
 */
 
#ifndef MACHINESYSTEM_H
#define MACHINESYSTEM_H

#include "IMachineSystem.h"
#include <memory>
#include <string>

// Forward references
class Machine;
class MachineFactory1;
class MachineFactory2;

/**
 * Class that directly implements the IMachineSystem interface
 */
class MachineSystem : public IMachineSystem {
private:
    /// The frame rate in frames per second
    double mFrameRate = 0;
    
    /// Current frame
    int mFrame = 0;
    
    /// Current time in seconds
    double mTime = 0;
    
    /// Machine number
    int mMachineNum = 1;
    
    /// Machine position
    wxPoint mPosition = wxPoint(0,0);
    
    /// Directory for the resources
    std::wstring mResourcesDir;
    
    /// Directory for the images
    std::wstring imageDir;
    
    /// Start time
    double mStartTime = 0;
    
    /// End time (0 means machine runs indefinitely)
    double mEndTime = 0;
    
    /// Flag value
    int mFlag = 0;
    
    /// The actual machine that we are using
    std::shared_ptr<Machine> mMachine;
    
    /// The machine factory for type 1 machines
    std::shared_ptr<MachineFactory1> mFactory1;
    
    /// The machine factory for type 2 machines
    std::shared_ptr<MachineFactory2> mFactory2;
    
    /// Whether the machine is currently running
    bool mIsRunning = false;

public:
    /**
     * Constructor
     * @param resourcesDir Directory for resources
     */
    MachineSystem(const std::wstring& resourcesDir = L"");
    
    /**
     * Set the position for the root of the machine
     * @param location The x,y location to place the machine
     */
    void SetLocation(wxPoint location) override;

    /**
     * Get the location of the machine
     * @return Location x,y in pixels as a point
     */
    wxPoint GetLocation() override;

    /**
     * Draw the machine at the currently specified location
     * @param graphics Graphics object to render to
     */
    void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Set the current machine animation frame
     * @param frame Frame number
     */
    void SetMachineFrame(int frame) override;

    /**
     * Set the expected frame rate in frames per second
     * @param rate Frame rate in frames per second
     */
    void SetFrameRate(double rate) override;

    /**
     * Set the machine number
     * @param machine An integer number. Each number makes a different machine
     */
    void ChooseMachine(int machine) override;

    /**
     * Get the current machine number
     * @return Machine number integer
     */
    int GetMachineNumber() override;

    /**
     * Get the current machine time.
     * @return Machine time in seconds
     */
    double GetMachineTime() override;

    /**
     * Set the flag from the control panel
     * @param flag Flag to set
     */
    void SetFlag(int flag) override;
    
    /**
     * Set the time for this machine
     * @param time Time in seconds
     */
    void SetTime(double time);
    
    /**
     * Set the start time for this machine
     * @param startTime Time in seconds when the machine starts
     */
    void SetStartTime(double startTime);
    
    /**
     * Set the end time for this machine
     * @param endTime Time in seconds when the machine stops (0 means run indefinitely)
     */
    void SetEndTime(double endTime);
    
    /**
     * Determine if the machine should be running at the current time
     * @return true if running
     */
    bool IsRunning();
    
    /**
     * Hit test on the machine
     * @param pos Position to test
     * @return true if pos is within the machine
     */
    bool HitTest(wxPoint pos);
};

#endif //MACHINESYSTEM_H
