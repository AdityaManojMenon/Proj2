/**
 * @file MachineFactory2.h
 * @author Aditya Menon
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

    /**
     * Constructor - private to enforce use of static factory method
     * @param resourcesDir Path to the resources directory
     */
    MachineFactory2(std::wstring resourcesDir) : mResourcesDir(resourcesDir) {}

public:
    /**
     * Create an instance of the factory
     * @param resourcesDir Path to the resources directory
     * @return Shared pointer to factory instance
     */
    static std::shared_ptr<MachineFactory2> Create(std::wstring resourcesDir)
    {
        // Use the placement new method to construct the object
        return std::shared_ptr<MachineFactory2>(new MachineFactory2(resourcesDir));
    }
    
    /**
     * Create a machine of type 2
     * @return Pointer to created machine
     */
    std::shared_ptr<Machine> Create();
};

#endif //MACHINEFACTORY2_H 