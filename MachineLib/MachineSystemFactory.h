/**
 * @file MachineSystemFactory.h
 *
 * @author Aditya Menon
 *
 * Factory class that creates the machine system
 */

#ifndef CANADIANEXPERIENCE_MACHINESYSTEMFACTORY_H
#define CANADIANEXPERIENCE_MACHINESYSTEMFACTORY_H

#include <memory>
#include <string>

class IMachineSystem;

/**
 * Factory class that creates the machine system
 */
class MachineSystemFactory
{
private:
    /// Directory containing resource files
    std::wstring mResourcesDir;

public:
    /**
     * Constructor
     * @param resourcesDir Directory containing resource files
     */
    MachineSystemFactory(std::wstring resourcesDir) : mResourcesDir(resourcesDir) {}

    /**
     * Create a machine system
     * @return The created machine system
     */
    std::shared_ptr<IMachineSystem> CreateMachineSystem();
};

#endif //CANADIANEXPERIENCE_MACHINESYSTEMFACTORY_H