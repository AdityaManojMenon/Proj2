/**
 * @file MachineFactory1.cpp
 * @author Aditya Menon
 */

#include "pch.h"
#include "MachineFactory1.h"
#include "Machine.h"
#include "Motor.h"
#include "Pulley.h"
#include "Shape.h"
#include "BubbleBlower.h"
#include "Bubble.h"

using namespace std;

/**
 * Factory method to create machine
 * @return Pointer to created machine
 */
std::shared_ptr<Machine> MachineFactory1::Create()
{
    /// The images directory in resources
    const std::wstring ImagesDirectory = L"/images";
    
    // Simply append the images directory to whatever path is provided
    mImagesDir = mResourcesDir + ImagesDirectory;
    
    // The machine itself
    auto machine = std::make_shared<Machine>(1);

    const int BaseWidth = 375;  // Width of the base
    const int BaseHeight = 40;  // Height of the base
    const int MotorX = 0;       // Motor X location
    
    // Post dimensions
    const int PostWidth = 20;   // Width of posts
    const int ShortPostHeight = 170; // Height of shorter post
    const int LongPostHeight = ShortPostHeight * 1.5; // Longer post is 50% taller
    const int LeftPostX = -100;  // Position of left post
    const int RightPostX = 100;  // Position of right post
    
    // Pulley dimensions
    const int Pulley2Radius = 15;  // Radius for pulley2
    const int Pulley4Radius = 35;  // Radius for pulley4
    const int TopPulleyY = -200;   // Y position for top pulleys
    
    // Platform dimensions
    const int PlatformWidth = 300;
    const int PlatformHeight = 40;
    const int PlatformX = -100;     // X position of platform
    const int PlatformY = -215;  // Y position of platform

    //
    // The base
    //
    auto base = std::make_shared<Shape>();
    base->Rectangle(-BaseWidth/2, 0, BaseWidth, BaseHeight);
    base->SetImage(mImagesDir + L"/base.png");

    //
    // The longer post (left of motor)
    //
    auto leftPost = std::make_shared<Shape>();
    // Set image first
    leftPost->SetImage(mImagesDir + L"/post.png");
    // Create centered rectangle for the post
    leftPost->Rectangle(-PostWidth/2, 0, PostWidth, LongPostHeight);
    leftPost->SetPosition(LeftPostX, -40);
    
    //
    // The shorter post (right of motor)
    //
    auto rightPost = std::make_shared<Shape>();
    // Set image first
    rightPost->SetImage(mImagesDir + L"/post.png");
    // Create centered rectangle for the post
    rightPost->Rectangle(-PostWidth/2, 0, PostWidth, ShortPostHeight);
    rightPost->SetPosition(RightPostX, -40);
    
    //
    // Platform
    //
    auto platform = std::make_shared<Shape>();
    platform->SetImage(mImagesDir + L"/platform.png");
    platform->Rectangle(-PlatformWidth/2, -PlatformHeight, PlatformWidth, PlatformHeight);
    platform->SetPosition(PlatformX, PlatformY);

    //
    // Belt between motor pulley and left pulley
    //
    // Create two separate lines for the belt instead of a filled shape
    auto beltLine1 = std::make_shared<Shape>();
    beltLine1->SetColor(wxColor(40, 40, 40)); // Darker black color for the belt
    
    auto beltLine2 = std::make_shared<Shape>();
    beltLine2->SetColor(wxColor(40, 40, 40)); // Darker black color for the belt
    
    // Source pulley position (pulley1 at motor)
    double x1 = MotorX;
    double y1 = -38 - Motor::Size/2;
    double r1 = Pulley2Radius - 3; // Inset by 3 pixels as suggested
    
    // Destination pulley position (pulley3)
    double x2 = LeftPostX;
    double y2 = -265;
    double r2 = Pulley4Radius - 3; // Inset by 3 pixels
    
    // Calculate the angle between centers
    double theta = atan2(y2 - y1, x2 - x1);
    
    // Calculate distance between centers
    double distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    
    // Calculate phi angle - this ensures tangent lines
    double phi = asin((r2 - r1) / distance);
    
    // First line of the belt - tangent point on first pulley to tangent point on second
    double beta1 = theta + phi + M_PI/2;
    double p1x1 = x1 + r1 * cos(beta1);
    double p1y1 = y1 + r1 * sin(beta1);
    double p2x1 = x2 + r2 * cos(beta1);
    double p2y1 = y2 + r2 * sin(beta1);
    
    // Second line of the belt - tangent point on first pulley to tangent point on second
    double beta2 = theta - phi - M_PI/2;
    double p1x2 = x1 + r1 * cos(beta2);
    double p1y2 = y1 + r1 * sin(beta2);
    double p2x2 = x2 + r2 * cos(beta2);
    double p2y2 = y2 + r2 * sin(beta2);
    
    // Calculate belt width vectors perpendicular to the belt line
    double belt_width = 6.0; // wider belt for better appearance
    double dx1 = p2x1 - p1x1;
    double dy1 = p2y1 - p1y1;
    double len1 = sqrt(dx1*dx1 + dy1*dy1);
    double nx1 = -dy1 / len1 * belt_width;
    double ny1 = dx1 / len1 * belt_width;
    
    // Add points for the first belt line to create a filled shape
    beltLine1->AddPoint(wxPoint(p1x1 - nx1/2, p1y1 - ny1/2));
    beltLine1->AddPoint(wxPoint(p2x1 - nx1/2, p2y1 - ny1/2));
    beltLine1->AddPoint(wxPoint(p2x1 + nx1/2, p2y1 + ny1/2));
    beltLine1->AddPoint(wxPoint(p1x1 + nx1/2, p1y1 + ny1/2));
    
    // Calculate width vector for the second belt line
    double dx2 = p2x2 - p1x2;
    double dy2 = p2y2 - p1y2;
    double len2 = sqrt(dx2*dx2 + dy2*dy2);
    double nx2 = -dy2 / len2 * belt_width;
    double ny2 = dx2 / len2 * belt_width;
    
    // Add points for the second belt line to create a filled shape
    beltLine2->AddPoint(wxPoint(p1x2 - nx2/2, p1y2 - ny2/2));
    beltLine2->AddPoint(wxPoint(p2x2 - nx2/2, p2y2 - ny2/2));
    beltLine2->AddPoint(wxPoint(p2x2 + nx2/2, p2y2 + ny2/2));
    beltLine2->AddPoint(wxPoint(p1x2 + nx2/2, p1y2 + ny2/2));
    
    // Additional belt lines that extend through the motor
    auto beltExtension1 = std::make_shared<Shape>();
    beltExtension1->SetColor(wxColor(40, 40, 40)); // Darker black color for the belt
    
    auto beltExtension2 = std::make_shared<Shape>();
    beltExtension2->SetColor(wxColor(40, 40, 40)); // Darker black color for the belt
    
    // Source pulley is at (MotorX, -38 - Motor::Size/2)
    double pulley1Y = -38 - Motor::Size/2; // Match the exact position of pulley1
    
    // Calculate vector perpendicular to the belt extension
    double dxe1 = MotorX - p1x1;
    double dye1 = pulley1Y - p1y1;
    double lene1 = sqrt(dxe1*dxe1 + dye1*dye1);
    double nxe1 = -dye1 / lene1 * belt_width;
    double nye1 = dxe1 / lene1 * belt_width;
    
    // Extend the first line through the motor to the source pulley
    beltExtension1->AddPoint(wxPoint(p1x1 - nx1/2, p1y1 - ny1/2));
    beltExtension1->AddPoint(wxPoint(MotorX - nxe1/2, pulley1Y - nye1/2));
    beltExtension1->AddPoint(wxPoint(MotorX + nxe1/2, pulley1Y + nye1/2));
    beltExtension1->AddPoint(wxPoint(p1x1 + nx1/2, p1y1 + ny1/2));
    
    // Calculate vector perpendicular to the second belt extension
    double dxe2 = MotorX - p1x2;
    double dye2 = pulley1Y - p1y2;
    double lene2 = sqrt(dxe2*dxe2 + dye2*dye2);
    double nxe2 = -dye2 / lene2 * belt_width;
    double nye2 = dxe2 / lene2 * belt_width;
    
    // Extend the second line through the motor to the source pulley
    beltExtension2->AddPoint(wxPoint(p1x2 - nx2/2, p1y2 - ny2/2));
    beltExtension2->AddPoint(wxPoint(MotorX - nxe2/2, pulley1Y - nye2/2));
    beltExtension2->AddPoint(wxPoint(MotorX + nxe2/2, pulley1Y + nye2/2));
    beltExtension2->AddPoint(wxPoint(p1x2 + nx2/2, p1y2 + ny2/2));
    
    //
    // Belt between connected_small_pulley_2 and pulley4
    //
    auto beltLine3 = std::make_shared<Shape>();
    beltLine3->SetColor(wxColor(40, 40, 40)); // Darker black color for the belt
    
    auto beltLine4 = std::make_shared<Shape>();
    beltLine4->SetColor(wxColor(40, 40, 40)); // Darker black color for the belt
    
    // Source pulley position (connected_small_pulley_2)
    double xs1 = LeftPostX;
    double ys1 = -265;
    double rs1 = Pulley2Radius - 3; // Inset by 3 pixels as suggested
    
    // Destination pulley position (pulley4)
    double xs2 = RightPostX;
    double ys2 = TopPulleyY;
    double rs2 = Pulley4Radius - 3; // Inset by 3 pixels
    
    // Calculate the angle between centers
    double thetas = atan2(ys2 - ys1, xs2 - xs1);
    
    // Calculate distance between centers
    double distances = sqrt(pow(xs2 - xs1, 2) + pow(ys2 - ys1, 2));
    
    // Calculate phi angle - this ensures tangent lines
    double phis = asin((rs2 - rs1) / distances);
    
    // First line of the belt - tangent point on first pulley to tangent point on second
    double betas1 = thetas + phis + M_PI/2;
    double ps1x1 = xs1 + rs1 * cos(betas1);
    double ps1y1 = ys1 + rs1 * sin(betas1);
    double ps2x1 = xs2 + rs2 * cos(betas1);
    double ps2y1 = ys2 + rs2 * sin(betas1);
    
    // Second line of the belt - tangent point on first pulley to tangent point on second
    double betas2 = thetas - phis - M_PI/2;
    double ps1x2 = xs1 + rs1 * cos(betas2);
    double ps1y2 = ys1 + rs1 * sin(betas2);
    double ps2x2 = xs2 + rs2 * cos(betas2);
    double ps2y2 = ys2 + rs2 * sin(betas2);
    
    // Calculate belt width vectors perpendicular to the belt line
    double dxs1 = ps2x1 - ps1x1;
    double dys1 = ps2y1 - ps1y1;
    double lens1 = sqrt(dxs1*dxs1 + dys1*dys1);
    double nxs1 = -dys1 / lens1 * belt_width;
    double nys1 = dxs1 / lens1 * belt_width;
    
    // Add points for the first belt line to create a filled shape
    beltLine3->AddPoint(wxPoint(ps1x1 - nxs1/2, ps1y1 - nys1/2));
    beltLine3->AddPoint(wxPoint(ps2x1 - nxs1/2, ps2y1 - nys1/2));
    beltLine3->AddPoint(wxPoint(ps2x1 + nxs1/2, ps2y1 + nys1/2));
    beltLine3->AddPoint(wxPoint(ps1x1 + nxs1/2, ps1y1 + nys1/2));
    
    // Calculate width vector for the second belt line
    double dxs2 = ps2x2 - ps1x2;
    double dys2 = ps2y2 - ps1y2;
    double lens2 = sqrt(dxs2*dxs2 + dys2*dys2);
    double nxs2 = -dys2 / lens2 * belt_width;
    double nys2 = dxs2 / lens2 * belt_width;
    
    // Add points for the second belt line to create a filled shape
    beltLine4->AddPoint(wxPoint(ps1x2 - nxs2/2, ps1y2 - nys2/2));
    beltLine4->AddPoint(wxPoint(ps2x2 - nxs2/2, ps2y2 - nys2/2));
    beltLine4->AddPoint(wxPoint(ps2x2 + nxs2/2, ps2y2 + nys2/2));
    beltLine4->AddPoint(wxPoint(ps1x2 + nxs2/2, ps1y2 + nys2/2));

    //
    // The motor
    //
    auto motor = std::make_shared<Motor>(mImagesDir);
    motor->SetPosition(MotorX, 0);
    motor->SetSpeed(1.0);

    //
    // The pulley (used instead of a shaft) driven by the motor
    // Radius=15pixels
    //
    auto pulley1 = std::make_shared<Pulley>(Pulley2Radius);
    // Using pulley2.png as the rotating element to show motor rotation
    pulley1->SetImage(mImagesDir + L"/pulley2.png");
    // Position the pulley at the motor's center
    pulley1->SetPosition(MotorX, -38 - Motor::Size/2);
    // No phase offset so it starts at 0 position
    pulley1->SetPhase(0.0);
    // This is the source pulley, so speed multiplier is 1.0
    pulley1->SetSpeedMultiplier(1.0);

    //
    // Second pulley4.png (top right)
    //
    auto pulley4 = std::make_shared<Pulley>(Pulley4Radius);
    pulley4->SetImage(mImagesDir + L"/pulley4.png");
    // Reposition to be more visible - place it at a moderate height between posts
    pulley4->SetPosition(RightPostX, TopPulleyY);
    pulley4->SetPhase(0.75); // Three-quarter rotation offset
    // Right pulleys rotate at 1/3 speed of source pulley
    pulley4->SetSpeedMultiplier(1.0/3.0);

    //
    // First pulley4.png (top left)
    //
    auto pulley3 = std::make_shared<Pulley>(Pulley4Radius);
    pulley3->SetImage(mImagesDir + L"/pulley4.png");
    // Reposition to be more visible - place it at a moderate height between posts
    pulley3->SetPosition(LeftPostX, -265);
    pulley3->SetPhase(0.5); // Half rotation offset
    // Left pulleys rotate at half speed of source pulley
    pulley3->SetSpeedMultiplier(0.5);

    //
    // Small connected pulley 1 (on center of pulley4)
    //
    auto connected_small_pulley_1 = std::make_shared<Pulley>(Pulley2Radius);
    connected_small_pulley_1->SetImage(mImagesDir + L"/pulley2.png");
    connected_small_pulley_1->SetPosition(RightPostX, TopPulleyY);
    connected_small_pulley_1->SetPhase(0.25); // Quarter rotation offset
    // Make the pulley with the flag rotate faster (full speed of source pulley)
    connected_small_pulley_1->SetSpeedMultiplier(1.0);

    //
    // Small connected pulley 2 (on center of pulley3)
    //
    auto connected_small_pulley_2 = std::make_shared<Pulley>(Pulley2Radius);
    connected_small_pulley_2->SetImage(mImagesDir + L"/pulley2.png");
    connected_small_pulley_2->SetPosition(LeftPostX, -265);
    connected_small_pulley_2->SetPhase(0.25); // Quarter rotation offset
    // Left pulleys rotate at half speed of source pulley
    connected_small_pulley_2->SetSpeedMultiplier(0.5);

    //
    // Flag attached to Small connected pulley 1
    //
    auto flag = std::make_shared<Shape>();
    flag->SetImage(mImagesDir + L"/flag.png");
    // Create a smaller rectangle for the flag to ensure it stays with the pulley
    flag->Rectangle(-25, -10, 35, 70);
    // Position it precisely at same position as connected_small_pulley_1
    flag->SetPosition(RightPostX, TopPulleyY);

    //
    // Black support stand on the platform
    //
    auto supportStand = std::make_shared<Shape>();
    // Create a black rectangle for the support stand
    supportStand->Rectangle(-40, -40, 15, 50);
    supportStand->SetColor(wxColor(0, 0, 0));  // Black color
    // Position it on top of the platform
    supportStand->SetPosition(PlatformX + 150, PlatformY - PlatformHeight);

    //
    // Blower on top of the support stand
    //
    auto blower = std::make_shared<Shape>();
    blower->SetImage(mImagesDir + L"/blower.png");
    // Create a rectangle for the blower
    blower->Rectangle(-53, -20, 40, 120);
    // Position it on top of the support stand
    blower->SetPosition(PlatformX + 150, PlatformY - PlatformHeight - 60);

    //
    // Bubble Blower connected to connected_small_pulley_2
    //
    auto bubbleBlower = std::make_shared<BubbleBlower>();
    // Position and tilt bubbleBlower
    bubbleBlower->SetPosition(50, -335);
    bubbleBlower->SetCurrentRotation(-0.25);  // Changed from SetRotation to SetCurrentRotation
    // Set image directory for the bubble blower to find bubble.png
    bubbleBlower->SetImageDirectory(mImagesDir);

    //
    // Set up ROTATION RELATIONSHIPS - BEFORE adding components to machine
    //
    
    // 1. Connect the motor to directly drive pulley1
    motor->AddSink(pulley1.get());
    
    // 2. Connect pulley1 to drive the large pulleys (pulley3 and pulley4)
    pulley1->ConnectBelt(pulley3.get());
    pulley1->ConnectBelt(pulley4.get());
    
    // 3. Connect the large pulleys to drive their small counterparts
    pulley3->ConnectPulley(connected_small_pulley_2.get());
    pulley4->ConnectPulley(connected_small_pulley_1.get());
    
    // 4. Connect the small pulley on pulley3 to drive pulley4 via belt
    connected_small_pulley_2->ConnectBelt(pulley4.get());
    
    // 5. Connect the flag to rotate with connected_small_pulley_1
    connected_small_pulley_1->AddSink(flag.get());
    
    // 6. Connect the bubble blower to be driven by connected_small_pulley_2
    connected_small_pulley_2->AddSink(bubbleBlower.get());
    
    //
    // NOW add all components to the machine in the correct drawing order
    //
    
    // Add the base
    machine->AddComponent(base);
    
    // Add the motor
    machine->AddComponent(motor);
    
    // Add the posts
    machine->AddComponent(leftPost);
    machine->AddComponent(rightPost);
    
    // Add platform
    machine->AddComponent(platform);
    
    // Add support stand and blower
    machine->AddComponent(supportStand);
    machine->AddComponent(blower);
    
    // Add the belts (now they'll appear on top of posts and motor)
    machine->AddComponent(beltLine1);
    machine->AddComponent(beltLine2);
    machine->AddComponent(beltLine3);
    machine->AddComponent(beltLine4);
    machine->AddComponent(beltExtension1);
    machine->AddComponent(beltExtension2);
    
    // Add all pulleys (these will be drawn on top of the belts)
    machine->AddComponent(pulley1);
    machine->AddComponent(pulley3);
    machine->AddComponent(pulley4);
    machine->AddComponent(connected_small_pulley_2);
    machine->AddComponent(connected_small_pulley_1);
    
    // Add the flag (drawn last so it appears on top)
    machine->AddComponent(flag);
    
    // Add the bubble blower (after the flag so bubbles appear on top)
    machine->AddComponent(bubbleBlower);
    
    return machine;
}

 