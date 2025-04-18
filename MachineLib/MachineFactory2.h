/**
 * @file MachineFactory2.h
 *
 * @author Aditya Menon
 *
 * Factory class that creates Machine 2
 */

#ifndef CANADIANEXPERIENCE_MACHINEFACTORY2_H
#define CANADIANEXPERIENCE_MACHINEFACTORY2_H

#include <memory>
#include <string>

class Machine;

/**
 * Factory class that creates Machine 2
 */
class MachineFactory2
{
private:
    /// Directory containing the machine images
    std::wstring mImagesDir;

public:
    /**
     * Constructor
     * @param imagesDir Directory containing the machine images
     */
    MachineFactory2(std::wstring imagesDir) : mImagesDir(imagesDir) {}

    /**
     * Create a machine of type 2
     * @return The created machine
     */
    std::shared_ptr<Machine> Create();
};

#endif //CANADIANEXPERIENCE_MACHINEFACTORY2_H 