/**
 * @file Machine.h
 *
 * @author Aditya Menon
 *
 * Class that represents a machine
 */

#ifndef CANADIANEXPERIENCE_MACHINE_H
#define CANADIANEXPERIENCE_MACHINE_H

#include <vector>
#include <memory>
#include "Component.h"
#include "Motor.h"

/**
 * Class that represents a machine
 */
class Machine
{
private:
    /// The location of the machine
    wxPoint mLocation = wxPoint(0, 0);

    /// The components that make up the machine
    std::vector<std::shared_ptr<Component>> mComponents;

    /// The machine's motors
    std::vector<std::shared_ptr<Motor>> mMotors;

    /// The current frame
    int mFrame = 0;

    /// The frame rate in frames per second
    double mFrameRate = 30.0;

    /// The machine number
    int mMachineNumber = 1;

    /// The flag value from the control panel
    int mFlag = 0;

public:
    /// Constructor
    Machine();

    /// Destructor
    virtual ~Machine() = default;

    /// Copy constructor (disabled)
    Machine(const Machine &) = delete;

    /// Assignment operator (disabled)
    void operator=(const Machine &) = delete;

    /**
     * Set the machine location
     * @param location Location to set
     */
    void SetLocation(wxPoint location) { mLocation = location; }

    /**
     * Get the machine location
     * @return Location of the machine
     */
    wxPoint GetLocation() const { return mLocation; }

    /**
     * Draw the machine at the current location
     * @param graphics Graphics context to draw on
     */
    void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * Set the machine animation frame
     * @param frame Frame number
     */
    void SetMachineFrame(int frame);

    /**
     * Set the expected frame rate
     * @param rate Frame rate in frames per second
     */
    void SetFrameRate(double rate) { mFrameRate = rate; }

    /**
     * Choose a machine to build
     * @param machine Machine number
     */
    void ChooseMachine(int machine);

    /**
     * Get the current machine number
     * @return Machine number
     */
    int GetMachineNumber() const { return mMachineNumber; }

    /**
     * Get the current machine time
     * @return Machine time in seconds
     */
    double GetMachineTime() const;

    /**
     * Set the flag from the control panel
     * @param flag Flag to set
     */
    void SetFlag(int flag);

    /**
     * Add a component to the machine
     * @param component Component to add
     */
    void AddComponent(std::shared_ptr<Component> component);
};

#endif //CANADIANEXPERIENCE_MACHINE_H 