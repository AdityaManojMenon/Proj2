/**
 * @file Pulley.cpp
 * @author Adi M
 */

#include "pch.h"
#include "Pulley.h"
#include "Polygon.h"
#include "Source.h"
#include "Sink.h"
#include "Component.h"

/**
 * Constructor
 * @param radius Radius of the pulley in pixels
 */
Pulley::Pulley(double radius) : mRadius(radius)
{
    // Create the pulley base as a circle
    auto base = GetBase();
    base->Circle(radius);
    base->SetColor(*wxGREEN);
    
    // Create Source and Sink for rotation connections
    mSource = std::make_shared<Source>();
    mSink = std::make_shared<Sink>();
    
    // Set this component as the sink's component
    mSink->SetComponent(this);
}

/**
 * Connect this pulley to another with a belt
 * @param pulley Pulley to connect to
 */
void Pulley::ConnectBelt(Pulley* pulley)
{
    if (pulley == nullptr)
    {
        return;
    }
    
    // Add the pulley to our connected pulleys
    mConnectedPulleys.push_back(pulley);
    pulley->mDrivingPulley = this;
    
    // Connect our source to their sink
    if (mSource != nullptr && pulley->GetSink() != nullptr)
    {
        mSource->AddSink(pulley->GetSink().get());
    }
}

/**
 * Update the pulley's state
 * @param time Current time in seconds
 */
void Pulley::Update(double time)
{
    SetTime(time);
}

/**
 * Draw the pulley
 * @param graphics Graphics context to draw on
 * @param position Position to draw at
 */
void Pulley::Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position)
{
    Component::Draw(graphics, position);
}

/**
 * Hit test for the pulley
 * @param pos Position to test
 * @return true if position is in pulley
 */
bool Pulley::HitTest(wxPoint pos)
{
    // Simple circular hit test
    double distance = sqrt(pos.x * pos.x + pos.y * pos.y);
    return distance <= mRadius;
}

/**
 * Connect another pulley to this one
 * @param pulley Pulley to connect
 */
void Pulley::ConnectPulley(Pulley* pulley)
{
    ConnectBelt(pulley);
}

/**
 * Set the time for the pulley
 * @param time Current time in seconds
 */
void Pulley::SetTime(double time)
{
    Component::SetTime(time);
    
    // Get the current rotation that was set by the motor
    double rotation = GetCurrentRotation();
    
    // Apply rotation to the pulley base with phase offset
    GetBase()->SetRotation(rotation + mPhase);
    
    // Update the source rotation to drive other components
    if (mSource != nullptr)
    {
        mSource->SetRotation(rotation);
    }
}

/**
 * Set the phase for the pulley
 * @param phase Phase in radians
 */
void Pulley::SetPhase(double phase)
{
    mPhase = phase;
}

/**
 * Get the pulley sink for connections
 * @return Pointer to sink
 */
std::shared_ptr<Sink> Pulley::GetSink()
{
    return mSink;
}

/**
 * Get the pulley source for connections
 * @return Pointer to source
 */
std::shared_ptr<Source> Pulley::GetSource()
{
    return mSource;
}

/**
 * Add a sink that will be driven by this pulley
 * @param sink Pointer to sink component
 */
void Pulley::AddSink(Component* sink)
{
    // For components that have a sink, add it to our source
    if (sink != nullptr)
    {
        auto pulley = dynamic_cast<Pulley*>(sink);
        if (pulley != nullptr && pulley->GetSink() != nullptr && mSource != nullptr)
        {
            mSource->AddSink(pulley->GetSink().get());
        }
    }
} 