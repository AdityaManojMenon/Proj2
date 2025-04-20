/**
 * @file Machine.cpp
 * @author Adi M
 */
 
#include "pch.h"
#include "Machine.h"
#include "Component.h"

/**
 * Constructor
 */
Machine::Machine()
{
}

/**
 * Constructor with machine number
 * @param machineNum Machine number
 */
Machine::Machine(int machineNum) : mMachineNum(machineNum)
{
}

/**
 * Draw the machine
 * @param graphics Graphics context to draw on
 * @param position Position to draw at
 */
void Machine::Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position)
{
    for(auto component : mComponents)
    {
        component->Draw(graphics, position);
    }
}

/**
 * Add a component to the machine
 * @param component Component to add
 */
void Machine::AddComponent(std::shared_ptr<Component> component)
{
    mComponents.push_back(component);
    component->SetMachine(this);
}

/**
 * Get a pointer to the machine system
 * @return Pointer to IMachineSystem object
 */
MachineSystem* Machine::GetSystem()
{
    return nullptr;
}

/**
 * Test if a point is within the machine
 * @param pos Position to test
 * @return true if hit
 */
bool Machine::HitTest(wxPoint pos)
{
    for(auto component : mComponents)
    {
        if(component->HitTest(pos))
        {
            return true;
        }
    }
    
    return false;
}

/**
 * Set the machine number
 * @param num Machine number to set
 */
void Machine::SetMachineNum(int num)
{
    mMachineNum = num;
}

/**
 * Set the flag value
 * @param flag Flag value to set
 */
void Machine::SetFlag(int flag)
{
    mFlag = flag;
}

/**
 * Get the current machine number
 * @return Machine number
 */
int Machine::GetMachineNum()
{
    return mMachineNum;
}

/**
 * Set the machine time
 * @param time Machine time in seconds
 */
void Machine::SetTime(double time)
{
    for(auto component : mComponents)
    {
        component->SetTime(time);
    }
}
