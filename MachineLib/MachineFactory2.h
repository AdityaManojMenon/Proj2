/**
 * @file MachineFactory2.h
 * @author Your Name
 *
 * Factory class for creating type 2 machines
 */
 
#ifndef MACHINEFACTORY2_H
#define MACHINEFACTORY2_H

#include <memory>
#include <string>

// Forward references
class Machine;

/**
 * Factory class that creates type 2 machines
 */
class MachineFactory2 {
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
    MachineFactory2(std::wstring resourcesDir);
    
    /**
     * Create a machine of type 2
     * @return Pointer to created machine
     */
    std::shared_ptr<Machine> Create();
};

#endif //MACHINEFACTORY2_H 