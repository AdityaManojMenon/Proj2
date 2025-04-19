/**
 * @file MachineFactory2.cpp
 *
 * @author Aditya Menon
 */

#include "pch.h"
#include "MachineFactory2.h"
#include "Machine.h"
#include "Shape.h"
#include "Motor.h"
#include "Pulley.h"

/**
 * Create a machine of type 2
 * @return The created machine
 */
std::shared_ptr<Machine> MachineFactory2::Create()
{
    // The machine itself
    auto machine = std::make_shared<Machine>();

    const int BaseWidth = 325;   // Width of the base
    const int BaseHeight = 40;   // Height of the base

    const int MotorX = 0;        // Motor X location
    const int MotorY = 0;        // Motor Y location
    
    const int PostWidth = 20;    // Width of the post image
    const int PostHeight = 120;  // Height of the post image

    //
    // The base - using the sample code approach
    //
    auto base = std::make_shared<Shape>(machine.get());
    base->Rectangle(-BaseWidth/2, 0, BaseWidth, BaseHeight);
    base->SetImage(mImagesDir + L"/base.png");
    machine->AddComponent(base);

    // Left post - 35% taller
    auto leftPost = std::make_shared<Shape>(machine.get());
    leftPost->Rectangle(-PostWidth/2, -PostHeight * 1.35, PostWidth, PostHeight * 1.35);
    leftPost->SetImage(mImagesDir + L"/post.png");
    leftPost->SetPosition(-BaseWidth/2 + 50, 0);
    machine->AddComponent(leftPost);

    // Right post - normal size
    auto rightPost = std::make_shared<Shape>(machine.get());
    rightPost->Rectangle(-PostWidth/2, -PostHeight, PostWidth, PostHeight);
    rightPost->SetImage(mImagesDir + L"/post.png");
    rightPost->SetPosition(BaseWidth/2 - 50, 0);
    machine->AddComponent(rightPost);

    //
    // The motor
    //
    auto motor = std::make_shared<Motor>(machine.get());
    motor->SetPosition(MotorX, MotorY);
    motor->SetSpeed(1.0);    // Set the motor speed to exactly 1 rotation per second
    motor->SetRunning(true);
    machine->AddComponent(motor);

    //
    // The pulleys 
    // (only 2 external pulleys that connect to motor's shaft)
    //
    
    // Pulley 1 (Left pulley)
    auto pulley1 = std::make_shared<Pulley>(machine.get(), 25);
    pulley1->SetImage(mImagesDir + L"/pulley4.png");
    pulley1->SetPosition(-BaseWidth/4, 125);
    machine->AddComponent(pulley1);
    motor->AddComponent(pulley1);
    
    // Pulley 2 (Right pulley)
    auto pulley2 = std::make_shared<Pulley>(machine.get(), 20);
    pulley2->SetImage(mImagesDir + L"/pulley4.png");
    pulley2->SetPosition(BaseWidth/4, 125);
    machine->AddComponent(pulley2);
    motor->AddComponent(pulley2);
    
    // Motor's shaft is already the source pulley, no need to create it
    // The connections are handled automatically by the motor when adding components

    return machine;
} 