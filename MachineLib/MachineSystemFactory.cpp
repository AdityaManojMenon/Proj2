/**
 * @file MachineSystemFactory.cpp
 *
 * @author Anik Momtaz
 * @author Charles Owen
 *
 * You are allowed to change this file.
 */

#include "pch.h"
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include "MachineSystemFactory.h"
#include "MachineSystem.h"

/// The images directory
const std::wstring ImagesDirectory = L"/images";

/**
 * Constructor
 * @param resourcesDir Directory to load resources from
 */
MachineSystemFactory::MachineSystemFactory(std::wstring resourcesDir) : mResourcesDir(resourcesDir)
{
    // If resources directory is empty, use executable path
    if (mResourcesDir.empty())
    {
        auto exePath = wxStandardPaths::Get().GetExecutablePath();
        mResourcesDir = wxFileName(exePath).GetPath().ToStdWstring();
    }
}

/**
 * Create a machine system object
 *
 * Do not change the return type of this function!
 *
 * @return Object of type IMachineSystem
 */
std::shared_ptr<IMachineSystem> MachineSystemFactory::CreateMachineSystem()
{
    // The important part: Return our MachineSystem which implements IMachineSystem
    // This follows the instruction not to change the return type
    return std::make_shared<MachineSystem>(mResourcesDir);
}
