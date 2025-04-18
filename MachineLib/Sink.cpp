/**
 * @file Sink.cpp
 *
 * @author Aditya Menon
 */

#include "pch.h"
#include "Sink.h"
#include "Machine.h"
#include "Source.h"
#include "Pulley.h"
#include "Shape.h"
#include "Component.h"

/**
 * Constructor
 * @param machine The machine this sink is part of
 */
Sink::Sink(Machine* machine) : Component(machine)
{
    // Set up the sink appearance
    mPolygon.Rectangle(-25, -25, 50, 50);
    mPolygon.SetColor(wxColour(128, 0, 0)); // Dark red
}

/**
 * Set the source for this sink
 * @param source Source to set
 */
void Sink::SetSource(std::shared_ptr<Source> source)
{
    mSource = source;
}

/**
 * Set the rotation for this sink
 * @param rotation Rotation value (0-1)
 */
void Sink::SetRotation(double rotation)
{
    mRotation = rotation;
    
    // Update the attached component if any
    if (mComponent != nullptr)
    {
        // Apply rotation to the component
        // Different components may have different ways to handle rotation
    }
    
    // Update the pulley if any
    if (mPulley != nullptr)
    {
        // Apply rotation to the pulley
        mPulley->SetRotation(mRotation);
    }
    
    // Update the shape if any
    if (mShape != nullptr)
    {
        // Apply rotation to the shape
        // We might rotate the shape directly
    }
}

/**
 * Set the component this sink is attached to
 * @param component Component to set
 */
void Sink::SetComponent(std::shared_ptr<Component> component)
{
    mComponent = component;
}

/**
 * Set the pulley this sink is connected to
 * @param pulley Pulley to set
 */
void Sink::SetPulley(std::shared_ptr<Pulley> pulley)
{
    mPulley = pulley;
}

/**
 * Set the shape this sink is connected to
 * @param shape Shape to set
 */
void Sink::SetShape(std::shared_ptr<Shape> shape)
{
    mShape = shape;
}

/**
 * Update for the current time
 * @param time Current time in seconds
 */
void Sink::SetTime(double time)
{
    // If we have a source, we might get rotation from it
    // Otherwise we might use time to calculate rotation
    
    // For now, just a simple rotation based on time
    if (mSource == nullptr)
    {
        // Calculate rotation based on time
        double rotation = fmod(time * 0.25, 1.0);
        SetRotation(rotation);
    }
    
    // Pass time to component, pulley and shape as needed
    if (mComponent != nullptr)
    {
        mComponent->SetTime(time);
    }
    
    if (mPulley != nullptr)
    {
        mPulley->SetTime(time);
    }
}

/**
 * Draw this sink
 * @param graphics Graphics context to draw on
 */
void Sink::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Draw the base sink component
    Component::Draw(graphics);
    
    // Draw the pulley if we have one
    if (mPulley != nullptr)
    {
        // The pulley might be positioned relative to the sink
        graphics->PushState();
        
        // Apply any transformations for the pulley
        // ...
        
        // Draw the pulley
        mPulley->Draw(graphics);
        
        graphics->PopState();
    }
    
    // Draw the shape if we have one
    if (mShape != nullptr)
    {
        // The shape might be positioned relative to the sink
        graphics->PushState();
        
        // Apply any transformations for the shape
        // ...
        
        // Draw the shape
        mShape->Draw(graphics, wxPoint(0, 0));
        
        graphics->PopState();
    }
} 