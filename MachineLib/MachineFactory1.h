/**
 * @file MachineFactory1.h
 * @author Aditya Menon
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

    /**
     * Constructor - private to enforce use of static factory method
     * @param resourcesDir Path to the resources directory
     */
    MachineFactory1(std::wstring resourcesDir) : mResourcesDir(resourcesDir) {}

public:
    /**
     * Create an instance of the factory
     * @param resourcesDir Path to the resources directory
     * @return Shared pointer to factory instance
     */
    static std::shared_ptr<MachineFactory1> Create(std::wstring resourcesDir)
    {
        // Use the placement new method to construct the object
        return std::shared_ptr<MachineFactory1>(new MachineFactory1(resourcesDir));
    }
    
    /**
     * Create a machine of type 1
     * @return Pointer to created machine
     */
    std::shared_ptr<Machine> Create();
};

#endif //MACHINEFACTORY1_H 
 
 
 
 