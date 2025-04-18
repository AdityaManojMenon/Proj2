/**
 * @file Source.cpp
 *
 * @author Aditya Menon
 */

#include "pch.h"
#include "Source.h"
#include "Machine.h"
#include "Motor.h"
#include "Pulley.h"
#include "Sink.h"

/**
 * Constructor
 * @param machine The machine this source is part of
 */
Source::Source(Machine* machine) : Component(machine)
{
    // Set up the source appearance
    mPolygon.Rectangle(-30, -30, 60, 60);
    mPolygon.SetColor(wxColour(0, 128, 0)); // Green
}

/**
 * Add a sink to this source
 * @param sink Sink to add
 */
void Source::AddSink(std::shared_ptr<Sink> sink)
{
    mSinks.push_back(sink);
}

/**
 * Add a motor to this source
 * @param motor Motor to add
 */
void Source::AddMotor(std::shared_ptr<Motor> motor)
{
    mMotors.push_back(motor);
}

/**
 * Add a pulley to this source
 * @param pulley Pulley to add
 */
void Source::AddPulley(std::shared_ptr<Pulley> pulley)
{
    mPulleys.push_back(pulley);
}

/**
 * Generate rotation
 * @param rotation Rotation value (0-1)
 */
void Source::GenerateRotation(double rotation)
{
    mRotation = rotation;
    
    // Update motors
    for (auto motor : mMotors)
    {
        motor->SetRotation(mRotation);
    }
    
    // Update pulleys
    for (auto pulley : mPulleys)
    {
        pulley->SetRotation(mRotation);
    }
    
    // Update connected sinks
    for (auto sink : mSinks)
    {
        // Set rotation on connected sinks
        sink->SetRotation(mRotation);
    }
}

/**
 * Set the current time
 * @param time Current time in seconds
 */
void Source::SetTime(double time)
{
    // Generate rotation based on time
    // Simple implementation - just use time directly for rotation
    double rotation = fmod(time * 0.2, 1.0); // 0.2 rotations per second
    GenerateRotation(rotation);
}

/**
 * Draw this source
 * @param graphics Graphics context to draw on
 */
void Source::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    Component::Draw(graphics);
} 