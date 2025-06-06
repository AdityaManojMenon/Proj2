/**
 * @file Motor.cpp
 * @author Aditya Menon
 */
 
#include "pch.h"
#include "Motor.h"
#include "Polygon.h"


using namespace std;

/// Size of the shaft
const int ShaftRadius = 15;

/**
 * Constructor
 */
Motor::Motor()
{
    // Create the motor body
    auto base = GetBase();
    base->CenteredSquare(Size);
    base->SetColor(*wxBLUE);
    
    // No shaft visualization - using pulley instead
}

/**
 * Constructor with images directory
 * @param imagesDir Directory containing images
 */
Motor::Motor(std::wstring imagesDir)
{
    // Create the motor body
    auto base = GetBase();
    base->Rectangle(-Size/2, -Size/2, Size, Size);
    base->SetImage(imagesDir + L"/motor3.png");
    
    // No shaft visualization - using pulley instead
}

/**
 * Set the motor speed
 * @param speed Speed in rotations per second
 */
void Motor::SetSpeed(double speed)
{
    mSpeed = speed;
}

/**
 * Get the motor speed
 * @return Speed in rotations per second
 */
double Motor::GetSpeed()
{
    return mSpeed;
}

/**
 * Draw the motor
 * @param graphics Graphics context to draw on
 * @param position Position to draw at
 */
void Motor::Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position)
{
    // Calculate the actual position considering component position
    wxPoint actualPosition = wxPoint(position.x + GetPosition().x, position.y + GetPosition().y);
    
    if(GetBase() != nullptr)
    {
        // Important: Do NOT apply rotation to the motor base
        // Override the default Component::Draw behavior to keep motor static
        GetBase()->SetRotation(0);  // Keep motor at 0 rotation
        
        // Draw the polygon
        GetBase()->DrawPolygon(graphics, actualPosition.x, actualPosition.y);
    }
}

/**
 * Set the time for this component
 * @param time Current time in seconds
 */
void Motor::SetTime(double time)
{
    Component::SetTime(time);
    
    // Compute rotation based on time and speed
    // For slower rotation, divide speed by a factor
    double adjustedSpeed = mSpeed / 5.0;  // 5x slower rotation
    double rotation = time * adjustedSpeed;
    
    // Calculate rotation in radians
    double rotationRadians = rotation * 2 * M_PI;
    
    // Store the rotation value but don't apply it to our base polygon
    // This prevents the motor image from rotating
    SetCurrentRotation(rotationRadians);
    
    // Only drive components that are explicitly connected to this motor
    for (auto component : mDrivenComponents)
    {
        if (component != nullptr)
        {
            // Set the current rotation for the driven component
            component->SetCurrentRotation(rotationRadians);
        }
    }
}

/**
 * Hit test for the motor
 * @param pos Position to test
 * @return true if position is in motor
 */
bool Motor::HitTest(wxPoint pos)
{
    // Simple hit test - check if within motor size
    double halfSize = Size / 2.0;
    if(pos.x >= -halfSize && pos.x <= halfSize &&
       pos.y >= -halfSize && pos.y <= halfSize)
    {
        return true;
    }
    
    return false;
}

/**
 * Add a sink that will be driven by this motor
 * @param sink Pointer to sink component
 */
void Motor::AddSink(Component* sink)
{
    if (sink != nullptr)
    {
        // Add this sink to our driven components
        mDrivenComponents.push_back(sink);
    }
}

/**
 * Get the source component for this motor
 * @return Pointer to the source
 */
std::shared_ptr<Component> Motor::GetSource()
{
    // For now just return nullptr
    return nullptr;
}
