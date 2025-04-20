/**
 * @file MachineFactory2.cpp
 * @author Anik Momtaz
 */

#include "pch.h"
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include "MachineFactory2.h"
#include "Machine.h"
#include "Motor.h"
#include "Pulley.h"
#include "Shape.h"

using namespace std;

/// The images directory in resources
const std::wstring ImagesDirectory = L"/images";

/**
 * Constructor
 * @param resourcesDir Path to the resources directory
 */
MachineFactory2::MachineFactory2(std::wstring resourcesDir) :
        mResourcesDir(resourcesDir)
{
    // If a resource directory isn't provided, use the executable path
    if (mResourcesDir.empty())
    {
        // Get directory the executable is in
        auto exePath = wxStandardPaths::Get().GetExecutablePath();
        mResourcesDir = wxFileName(exePath).GetPath().ToStdWstring();
    }
    
    mImagesDir = mResourcesDir + ImagesDirectory;
}

/**
 * Factory method to create machine
 * @return Pointer to created machine
 */
std::shared_ptr<Machine> MachineFactory2::Create()
{
    // Create a machine of a different type
    auto machine = std::make_shared<Machine>(2);

    const int BaseWidth = 350;  // Width of the base
    const int BaseHeight = 45;  // Height of the base
    
    //
    // The base
    //
    auto base = std::make_shared<Shape>();
    base->Rectangle(-BaseWidth/2, 0, BaseWidth, BaseHeight);
    base->SetImage(mImagesDir + L"/base2.png");
    machine->AddComponent(base);

    //
    // The motor
    //
    auto motor = std::make_shared<Motor>(mImagesDir);
    motor->SetPosition(30, -40);
    motor->SetSpeed(0.5); // Half speed for machine type 2
    machine->AddComponent(motor);

    //
    // First pulley driven by the motor
    //
    auto pulley1 = std::make_shared<Pulley>(20);
    pulley1->SetImage(mImagesDir + L"/pulley1.png");
    pulley1->SetPosition(30, -100);
    machine->AddComponent(pulley1);
    
    //
    // Second pulley driven by the first
    //
    auto pulley2 = std::make_shared<Pulley>(15);
    pulley2->SetImage(mImagesDir + L"/gear1.png");
    pulley2->SetPosition(100, -100);
    pulley2->SetPhase(0.25); // Quarter turn offset
    machine->AddComponent(pulley2);

    // Connect the components
    motor->AddSink(pulley1.get());
    // In a real implementation, we would connect pulley1 to pulley2
    // pulley1->AddSink(pulley2.get());

    return machine;
} 