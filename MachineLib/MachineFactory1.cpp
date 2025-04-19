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
#include "Pulley.h"


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
    
    const int PostWidth = 20;    // Width of the post image
    const int PostHeight = 160;  // Height of the post image

    const int PlatformWidth = 325;   // Width of the base
    const int PlatformHeight = 40;   // Height of the base

    //
    // The base - using the sample code approach
    //
    auto base = std::make_shared<Shape>(machine.get());
    base->Rectangle(-BaseWidth/2, 0, BaseWidth, BaseHeight);
    base->SetImage(mImagesDir + L"/base.png");
    machine->AddComponent(base);


    //
    // The platform
    //
    auto platform = std::make_shared<Shape>(machine.get());
    platform->Rectangle(-275, -285, PlatformWidth, PlatformHeight);
    platform->SetImage(mImagesDir + L"/platform.png");
    machine->AddComponent(platform);

    // Left post - 35% taller
    auto leftPost = std::make_shared<Shape>(machine.get());
    leftPost->Rectangle(-PostWidth/2, -PostHeight * 1.35, PostWidth, PostHeight * 1.65);
    leftPost->SetImage(mImagesDir + L"/post.png");
    leftPost->SetPosition(-BaseWidth/2 + 50, 177);
    machine->AddComponent(leftPost);

    // Right post - normal size
    auto rightPost = std::make_shared<Shape>(machine.get());
    rightPost->Rectangle(-PostWidth/2, -PostHeight, PostWidth, PostHeight);
    rightPost->SetImage(mImagesDir + L"/post.png");
    rightPost->SetPosition(BaseWidth/2 - 50, 121);
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
    auto pulley1 = std::make_shared<Pulley>(machine.get(), 33);
    pulley1->SetImage(mImagesDir + L"/pulley.png");
    pulley1->SetPosition(BaseWidth/2 - 275, -300);
    machine->AddComponent(pulley1);
    motor->AddComponent(pulley1);
    
    // Pulley 2 (Right pulley)
    auto pulley2 = std::make_shared<Pulley>(machine.get(), 33);
    pulley2->SetImage(mImagesDir + L"/pulley.png");
    pulley2->SetPosition(BaseWidth/2 - 50, -195);
    machine->AddComponent(pulley2);
    motor->AddComponent(pulley2);

    // Pulley 3 (small pulley)
    auto pulley3 = std::make_shared<Pulley>(machine.get(), 15);
    pulley3->SetImage(mImagesDir + L"/pulley2.png");
    pulley3->SetPosition(BaseWidth/2 - 52, -195);
    machine->AddComponent(pulley3);
    motor->AddComponent(pulley3);

    // Pulley 4 (small pulley)
    auto pulley4 = std::make_shared<Pulley>(machine.get(), 15);
    pulley4->SetImage(mImagesDir + L"/pulley2.png");
    pulley4->SetPosition(BaseWidth/2 - 275, -300);
    machine->AddComponent(pulley4);
    motor->AddComponent(pulley4);

    
    return machine;
} 