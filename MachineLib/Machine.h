/**
 * @file Machine.h
 * @author Aditya Menon
 *
 * Class for a machine
 */
 
#ifndef MACHINE_H
#define MACHINE_H

#include <memory>
#include <vector>

// Forward references
class Component;
class MachineSystem;

/**
 * Class for a machine
 */
class Machine {
private:
    /// The machine number
    int mMachineNum = 0;
    
    /// Flag value for the machine
    int mFlag = 0;
    
    /// The components in this machine
    std::vector<std::shared_ptr<Component>> mComponents;
    
    /// The motor component
    std::shared_ptr<Component> mMotor;

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
     * Set the motor for this machine
     * @param motor Motor component
     */
    void SetMotor(std::shared_ptr<Component> motor);
    
    /**
     * Get a pointer to the machine system
     * @return Pointer to MachineSystem object
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
     * Get the components in this machine
     * @return Vector of components
     */
    std::vector<std::shared_ptr<Component>>& GetComponents() { return mComponents; }
};

#endif //MACHINE_H
