/**
 * @file MachineFactory1.h
 *
 * @author Aditya Menon
 *
 * Factory class that creates Machine 1
 */

#ifndef CANADIANEXPERIENCE_MACHINEFACTORY1_H
#define CANADIANEXPERIENCE_MACHINEFACTORY1_H

#include <memory>
#include <string>

class Machine;

/**
 * Factory class that creates Machine 1
 */
class MachineFactory1
{
private:
    /// Directory containing the machine images
    std::wstring mImagesDir;

public:
    /**
     * Constructor
     * @param imagesDir Directory containing the machine images
     */
    MachineFactory1(std::wstring imagesDir) : mImagesDir(imagesDir) {}

    /**
     * Create a machine of type 1
     * @return The created machine
     */
    std::shared_ptr<Machine> Create();
};

#endif //CANADIANEXPERIENCE_MACHINEFACTORY1_H 