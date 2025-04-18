/**
 * @file MachineSystemFactory.cpp
 *
 * @author Anik Momtaz
 * @author Charles Owen
 *
 * You are allowed to change this file.
 */

#include "pch.h"
#include "MachineSystemFactory.h"
#include "MachineSystem.h"
#include "IMachineSystem.h"
#include "MachineFactory1.h"
#include "MachineFactory2.h"
#include "Machine.h"

/// Global variable to store the machines we created
std::shared_ptr<Machine> gMachine1 = nullptr;
std::shared_ptr<Machine> gMachine2 = nullptr;

/**
 * Create a machine system.
 * @return The created machine system
 */
std::shared_ptr<IMachineSystem> MachineSystemFactory::CreateMachineSystem()
{
    // Create a machine system with the resources directory
    auto system = std::make_shared<MachineSystem>(mResourcesDir);
    
    // Create the image directory path for factories
    std::wstring imagesDir = mResourcesDir + L"/images";
    
    // Create machine factories
    MachineFactory1 factory1(imagesDir);
    MachineFactory2 factory2(imagesDir);
    
    // Create machine of each type
    gMachine1 = factory1.Create();
    gMachine2 = factory2.Create();
    
    // Override the ChooseMachine behavior to use our created machines
    system->ChooseMachine(1);  // Default to machine 1
    
    return system;
}
