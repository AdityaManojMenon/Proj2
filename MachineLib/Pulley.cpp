/**
 * @file Pulley.cpp
 *
 * @author Aditya Menon
 */

#include "pch.h"
#include "Pulley.h"
#include "Machine.h"

/**
 * Constructor
 * @param machine The machine this pulley is part of
 * @param radius The radius of the pulley in pixels
 */
Pulley::Pulley(Machine* machine, double radius) : Component(machine)
{
    mRadius = radius;
    
    // Create the pulley with a circle shape
    mPolygon.Circle(radius);
    
    // Set the pulley image
    mPolygon.SetImage(L"images/pulley2.png");
}

/**
 * Connect this pulley to another pulley
 * @param pulley The pulley to connect to
 */
void Pulley::ConnectPulley(std::shared_ptr<Pulley> pulley)
{
    // Add to our list of connected pulleys
    mConnectedPulleys.push_back(pulley);
}

/**
 * Test if a point is inside the pulley (for mouse interaction)
 * @param x X position to test
 * @param y Y position to test
 * @return True if the point is inside the pulley
 */
bool Pulley::HitTest(double x, double y)
{
    // Calculate distance from center of pulley
    double dx = x - mPosition.m_x;
    double dy = y - mPosition.m_y;
    double distance = sqrt(dx * dx + dy * dy);
    
    // If distance is less than radius, the point is inside the pulley
    return distance <= mRadius;
}

/**
 * Update component for the current time
 * @param time Current machine time in seconds
 */
void Pulley::SetTime(double time)
{
    // Nothing to do for now - rotation is handled by the Motor class
}

/**
 * Draw this pulley
 * @param graphics Graphics context to draw on
 */
void Pulley::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Draw the pulley
    Component::Draw(graphics);
    
    // Draw the belts between this pulley and connected pulleys
    // This would be implemented in a more complete version
} 