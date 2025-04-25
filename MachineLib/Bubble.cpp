/**
 * @file Bubble.cpp
 * @author Aditya Menon
 */

#include "pch.h"
#include "Bubble.h"
#include "Polygon.h"

/// Gravity is very mild for soap bubbles (slower falling)
const float Gravity = 2.0;

/**
 * Constructor
 */
Bubble::Bubble()
{
    // Create the bubble image
    mImage = std::make_shared<cse335::Polygon>();
    
    // Use fixed size for all bubbles instead of random sizing
    double radius = 15.0;  // Fixed bubble size
    mImage->Circle(radius);
    
    // Set a semi-transparent light blue color
    mImage->SetColor(wxColor(100, 200, 255, 180));  // Light blue with transparency
    
    // Initialize position and velocity to zero
    mPosition = wxPoint2DDouble(0, 0);
    mVelocity = wxPoint2DDouble(0, 0);
}

/**
 * Set the image for the bubble
 * @param imagePath Path to the bubble image
 */
void Bubble::SetImage(const std::wstring& imagePath)
{
    // Check if file exists before trying to load
    wxFileName file(imagePath);
    if (!file.FileExists())
    {
        // Use a bright color if image can't be found
        if (mImage != nullptr)
        {
            mImage->SetColor(wxColor(255, 0, 0, 200));
        }
        return;
    }
    
    if (mImage != nullptr)
    {
        mImage->SetImage(imagePath);
    }
}

/**
 * Draw the bubble
 * @param graphics Graphics context to draw on
 */
void Bubble::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (mImage != nullptr)
    {
        // Draw the bubble
        mImage->DrawPolygon(graphics, mPosition.m_x, mPosition.m_y);
    }
}

/**
 * Update the bubble position
 * @param elapsed_time Time elapsed since last update
 */
void Bubble::Update(double elapsed_time)
{
    // Use a larger time step for faster movement
    const double fixedTimeStep = 0.033;
    
    // Apply mild gravity to the velocity
    mVelocity.m_y += Gravity * fixedTimeStep;
    
    // Apply velocity to position with fixed time step
    mPosition.m_x += mVelocity.m_x * fixedTimeStep;
    mPosition.m_y += mVelocity.m_y * fixedTimeStep;
} 