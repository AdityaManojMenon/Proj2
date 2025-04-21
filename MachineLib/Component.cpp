/**
 * @file Component.cpp
 * @author Aditya Menon
 */
 
#include "pch.h"
#include "Component.h"
#include "Machine.h"
#include "Polygon.h"

using namespace std;

/**
 * Constructor
 */
Component::Component()
{
    mBase = make_shared<cse335::Polygon>();
}

/**
 * Destructor
 */
Component::~Component()
{
}

/**
 * Set the machine this component is associated with
 * @param machine Machine pointer
 */
void Component::SetMachine(Machine* machine)
{
    mMachine = machine;
}

/**
 * Draw the component
 * @param graphics Graphics context to draw on
 * @param position Position to draw at
 */
void Component::Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position)
{
    // Calculate the actual position considering component position and center
    wxPoint actualPosition = wxPoint(position.x + mPosition.x, position.y + mPosition.y);
    
    if(mBase != nullptr)
    {
        // Make sure current rotation with phase is applied to the base
        // This ensures motor and pulley rotations are properly visualized
        mBase->SetRotation(mCurrentRotation + mPhase * 2 * M_PI);
        
        // Draw the polygon
        mBase->DrawPolygon(graphics, actualPosition.x, actualPosition.y);
    }
}

/**
 * Get the current rotation
 * @return Rotation in radians
 */
double Component::GetRotation()
{
    return mRotation;
}

/**
 * Get the base polygon
 * @return Polygon that makes up the base
 */
std::shared_ptr<cse335::Polygon> Component::GetBase()
{
    return mBase;
}

/**
 * Set the time for the component
 * @param time Time in seconds
 */
void Component::SetTime(double time)
{
    // Base implementation does nothing with time
    // Components only rotate when explicitly driven by
    // a motor or pulley through the SetCurrentRotation method
}

/**
 * Set the current rotation of the component
 * @param rotation Rotation in radians
 */
void Component::SetCurrentRotation(double rotation)
{
    mCurrentRotation = rotation;
}

/**
 * Get the machine this component is associated with
 * @return Machine pointer
 */
Machine* Component::GetMachine()
{
    return mMachine;
}

/**
 * Test if a point is within this component
 * @param pos Position to test
 * @return true if hit
 */
bool Component::HitTest(wxPoint pos)
{
    // Default implementation - the base component doesn't respond to hits
    return false;
}

/**
 * Set the position of this component
 * @param x X position in pixels
 * @param y Y position in pixels
 */
void Component::SetPosition(int x, int y)
{
    mPosition = wxPoint(x, y);
}

/**
 * Set the position of this component
 * @param position Position in pixels
 */
void Component::SetPosition(wxPoint position)
{
    mPosition = position;
}

/**
 * Draw a rectangle for this component
 * @param x Left edge
 * @param y Top edge
 * @param width Width of rectangle
 * @param height Height of rectangle
 */
void Component::Rectangle(int x, int y, int width, int height)
{
    if (mBase != nullptr)
    {
        mBase->Rectangle(x, y, width, height);
    }
}

/**
 * Set an image for this component
 * @param filename Image filename
 */
void Component::SetImage(const std::wstring& filename)
{
    if (mBase != nullptr)
    {
        mBase->SetImage(filename);
    }
}

/**
 * Set the phase offset for rotation
 * @param phase Phase offset (0-1)
 */
void Component::SetPhase(double phase)
{
    mPhase = phase;
}

/**
 * Place the component relative to an offset
 * @param offset Offset position
 */
void Component::Place(wxPoint offset)
{
    mPosition = offset;
}

/**
 * Helper function to set an image with proper path checking
 * @param imagePath Path to the image
 * @param defaultColor Default color to use if image not found
 * @return True if image was set successfully
 */
bool Component::SetComponentImage(const std::wstring& imagePath, wxColour defaultColor)
{
    if (mBase == nullptr)
    {
        return false;
    }
    
    // First check if file exists
    if (wxFileExists(imagePath))
    {
        mBase->SetImage(imagePath);
        return true;
    }
    else
    {
        // Log a warning and use a color instead
        wxLogWarning(L"Image not found: %s - using default color instead", imagePath);
        mBase->SetColor(defaultColor);
        return false;
    }
}
