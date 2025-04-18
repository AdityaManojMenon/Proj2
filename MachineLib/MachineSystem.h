/**
 * @file MachineSystem.h
 *
 * @author Aditya Menon
 *
 * Implementation of the IMachineSystem interface
 */

#ifndef CANADIANEXPERIENCE_MACHINESYSTEM_IMPL_H
#define CANADIANEXPERIENCE_MACHINESYSTEM_IMPL_H

// Make sure IMachineSystem is included correctly
#include "IMachineSystem.h"
#include "Machine.h"

/**
 * Implementation of the IMachineSystem interface
 */
class MachineSystem : public IMachineSystem
{
private:
    /// The machine system
    std::shared_ptr<Machine> mMachine;

    /// The resources directory
    std::wstring mResourcesDir;

public:
    /**
     * Constructor
     * @param resourcesDir Path to the resources directory
     */
    MachineSystem(std::wstring resourcesDir);

    /// Destructor
    virtual ~MachineSystem() = default;

    /// Copy constructor (disabled)
    MachineSystem(const MachineSystem &) = delete;

    /// Assignment operator (disabled)
    void operator=(const MachineSystem &) = delete;

    /**
     * Set the position for the root of the machine
     * @param location The x,y location to place the machine
     */
    virtual void SetLocation(wxPoint location) override;

    /**
     * Get the location of the machine
     * @return Location x,y in pixels as a point
     */
    virtual wxPoint GetLocation() override;

    /**
     * Draw the machine at the currently specified location
     * @param graphics Graphics object to render to
     */
    virtual void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Set the current machine animation frame
     * @param frame Frame number
     */
    virtual void SetMachineFrame(int frame) override;

    /**
     * Set the expected frame rate in frames per second
     * @param rate Frame rate in frames per second
     */
    virtual void SetFrameRate(double rate) override;

    /**
     * Set the machine number
     * @param machine An integer number. Each number makes a different machine
     */
    virtual void ChooseMachine(int machine) override;

    /**
     * Get the current machine number
     * @return Machine number integer
     */
    virtual int GetMachineNumber() override;

    /**
     * Get the current machine time.
     * @return Machine time in seconds
     */
    virtual double GetMachineTime() override;

    /**
     * Set the flag from the control panel
     * @param flag Flag to set
     */
    virtual void SetFlag(int flag) override;
};

#endif //CANADIANEXPERIENCE_MACHINESYSTEM_IMPL_H 