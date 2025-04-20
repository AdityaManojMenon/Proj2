/**
 * @file MachineFactory1.h
 * @author Your Name
 *
 * Factory class for creating type 1 machines
 */
 
#ifndef MACHINEFACTORY1_H
#define MACHINEFACTORY1_H

#include <memory>
#include <string>

// Forward references
class Machine;

/**
 * Factory class that creates type 1 machines
 */
class MachineFactory1 {
private:
    /// Resources directory
    std::wstring mResourcesDir;
    
    /// Images directory
    std::wstring mImagesDir;

public:
    /**
     * Constructor
     * @param resourcesDir Path to the resources directory
     */
    MachineFactory1(std::wstring resourcesDir);
    
    /**
     * Create a machine of type 1
     * @return Pointer to created machine
     */
    std::shared_ptr<Machine> Create();
};

#endif //MACHINEFACTORY1_H 