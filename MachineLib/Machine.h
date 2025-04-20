/**
 * @file Machine.h
 * @author Adi M
 *
 * Class for the machine
 */
 
#ifndef MACHINE_H
#define MACHINE_H

#include <memory>
#include <vector>

// Forward references
class Component;
class MachineSystem;

/**
 * Class for the machine
 */
class Machine {
private:
    /// Machine number
    int mMachineNum = 0;
    
    /// Flag value
    int mFlag = 0;
    
    /// The components that make up the machine
    std::vector<std::shared_ptr<Component>> mComponents;

public:
    Machine();
    
    /**
     * Constructor with a machine number parameter
     * @param machineNum The machine number
     */
    Machine(int machineNum);

    /**
     * Draw the machine
     * @param graphics Graphics context to draw on
     * @param position Position to draw at
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position);
    
    /**
     * Add a component to the machine
     * @param component Component to add
     */
    void AddComponent(std::shared_ptr<Component> component);
    
    /**
     * Get a pointer to the machine system
     * @return Pointer to IMachineSystem object
     */
    MachineSystem* GetSystem();
    
    /**
     * Test if a point is within the machine
     * @param pos Position to test
     * @return true if hit
     */
    bool HitTest(wxPoint pos);
    
    /**
     * Set the machine number
     * @param num Machine number to set
     */
    void SetMachineNum(int num);
    
    /**
     * Set the flag value
     * @param flag Flag value to set
     */
    void SetFlag(int flag);
    
    /**
     * Get the current machine number
     * @return Machine number
     */
    int GetMachineNum();
    
    /**
     * Set the machine time
     * @param time Machine time in seconds
     */
    void SetTime(double time);
};

#endif //MACHINE_H
