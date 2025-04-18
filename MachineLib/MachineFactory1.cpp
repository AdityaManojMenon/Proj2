/**
 * @file MachineFactory1.cpp
 *
 * @author Aditya Menon
 */

#include "pch.h"
#include "MachineFactory1.h"
#include "Machine.h"
#include "Shape.h"
#include "Motor.h"
#include "Polygon.h"

/**
 * Create a machine of type 1
 * @return The created machine
 */
std::shared_ptr<Machine> MachineFactory1::Create()
{
    // The machine itself
    auto machine = std::make_shared<Machine>();

    const int BaseWidth = 325;   // Width of the base
    const int BaseHeight = 40;   // Height of the base

    const int MotorX = 20;       // Motor X location
    const int MotorY = 0;        // Motor Y location

    //
    // The base - using the sample code approach
    //
    auto base = std::make_shared<Shape>(machine.get());
    base->Rectangle(-BaseWidth/2, 0, BaseWidth, BaseHeight);
    
    // Ensure we use the correct path for the base image
    // Using the image directory passed into the constructor
    base->SetImage(mImagesDir + L"/base.png");
    machine->AddComponent(base);

    //
    // The motor
    //
    auto motor = std::make_shared<Motor>(machine.get());
    motor->SetPosition(MotorX, MotorY);
    motor->SetSpeed(1.0);    // Set the motor speed to exactly 1 rotation per second
    motor->SetRunning(true);
    machine->AddComponent(motor);

    return machine;
} 