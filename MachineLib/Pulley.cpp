#include "pch.h"
#include "Pulley.h"
#include "Machine.h"

/**
 * Set the image for this pulley
 * @param filename Filename for the image
 */
void Pulley::SetImage(std::wstring filename)
{
    mPolygon.SetImage(filename);
}

/**
 * Constructor
 * @param machine The machine this pulley is part of
 * @param radius The radius of the pulley in pixels
 */
Pulley::Pulley(Machine* machine, double radius) : Component(machine)
{
    // Set the radius
    mRadius = radius;
    
    // Create a circular polygon for the pulley
    mPolygon.Circle(radius);
}

/**
 * Connect this pulley to another pulley
 * @param pulley The pulley to connect to
 */
void Pulley::ConnectPulley(std::shared_ptr<Pulley> pulley)
{
    // Add the pulley to our connected pulleys list
    mConnectedPulleys.push_back(pulley);
}

/**
 * Draw this pulley
 * @param graphics Graphics context to draw on
 */
void Pulley::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Draw the base pulley shape
    Component::Draw(graphics);
    
    // We could also draw connections to other pulleys here
}

/**
 * Test if a point is inside the pulley (for mouse interaction)
 * @param x X position to test
 * @param y Y position to test
 * @return True if the point is inside the pulley
 */
bool Pulley::HitTest(double x, double y)
{
    // Convert the point to relative coordinates
    double relX = x - GetPosition().m_x;
    double relY = y - GetPosition().m_y;
    
    // Calculate the distance from center
    double distance = sqrt(relX * relX + relY * relY);
    
    // Check if the point is within the radius
    return distance <= mRadius;
}

/**
 * Update component for the current time
 * @param time Current machine time in seconds
 */
void Pulley::SetTime(double time)
{
    // Component::SetTime takes care of setting the time
    Component::SetTime(time);
    
    // The motor in Motor.cpp will handle setting rotation directly,
    // so we don't need to do anything special here
}