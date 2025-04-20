/**
 * @file MachineFactory1.cpp
 * @author Anik Momtaz
 */

#include "pch.h"
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include "MachineFactory1.h"
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
MachineFactory1::MachineFactory1(std::wstring resourcesDir) :
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
std::shared_ptr<Machine> MachineFactory1::Create()
{
    // The machine itself
    auto machine = std::make_shared<Machine>(1);

    const int BaseWidth = 325;  // Width of the base
    const int BaseHeight = 40;  // Height of the base
    const int MotorX = 20;      // Motor X location

    //
    // The base
    //
    auto base = std::make_shared<Shape>();
    base->Rectangle(-BaseWidth/2, 0, BaseWidth, BaseHeight);
    base->SetImage(mImagesDir + L"/base.png");
    machine->AddComponent(base);

    //
    // The motor
    //
    auto motor = std::make_shared<Motor>(mImagesDir);
    motor->SetPosition(MotorX, -38);
    // Set motor speed to exactly 1.0 rotation per second as required
    motor->SetSpeed(1.0);
    machine->AddComponent(motor);

    //
    // The pulley (used instead of a shaft) driven by the motor
    // Radius=15pixels
    //
    auto pulley = std::make_shared<Pulley>(15);
    // Using pulley2.png as the rotating element to show motor rotation
    pulley->SetImage(mImagesDir + L"/pulley2.png");
    // Position the pulley at the motor's center
    pulley->SetPosition(MotorX, -38 - Motor::Size/2);
    // No phase offset so it starts at 0 position
    pulley->SetPhase(0.0);
    machine->AddComponent(pulley);

    // Connect the motor to drive the pulley
    motor->AddSink(pulley.get());

    return machine;
} 