/**
 * @file Bubble.cpp
 * @author Aditya Menon
 */

#include "pch.h"
#include "Bubble.h"
#include "Polygon.h"

/// Gravity is very mild for soap bubbles (slower falling)
const float Gravity = 1.0;

// Initialize static constants
const double Bubble::BubbleExpansionProbability = 0.05;
const int Bubble::BubbleMaximumRadius = 30;
const int Bubble::BubbleInitialRadius = 15; // Starting radius
const double Bubble::BubbleExpansionAmount = 0.5; // How much radius increases each time

/**
 * Constructor
 */
Bubble::Bubble()
{
    // Seed the random number generator
    std::random_device rd;
    mRandom.seed(rd());

    // Create the bubble image polygon
    mImage = std::make_shared<cse335::Polygon>();
    
    // Initialize radius
    mCurrentRadius = BubbleInitialRadius;
    
    // Create the circle based on initial radius
    // Note: The actual drawing will scale this base circle
    mImage->Circle(BubbleInitialRadius);
    
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
        // Calculate scale factor based on current radius vs initial radius
        double scale = mCurrentRadius / BubbleInitialRadius;
        
        // Save the current graphics state
        graphics->PushState();
        
        // Translate to the bubble's position
        graphics->Translate(mPosition.m_x, mPosition.m_y);
        
        // Scale the graphics context
        graphics->Scale(scale, scale);
        
        // Draw the polygon (at the origin, scaled)
        mImage->DrawPolygon(graphics, 0, 0);
        
        // Restore the graphics state
        graphics->PopState();
    }
}

/**
 * Update the bubble position and size
 * @param elapsed_time Time elapsed since last update
 */
void Bubble::Update(double elapsed_time)
{
    if (mPopped) return; // Do nothing if already popped

    // Use a larger time step for faster movement
    const double fixedTimeStep = 0.033;  // ~30fps equivalent - makes bubbles move faster
    
    // Apply mild gravity to the velocity
    mVelocity.m_y += Gravity * fixedTimeStep;
    
    // Apply velocity to position with fixed time step
    mPosition.m_x += mVelocity.m_x * fixedTimeStep;
    mPosition.m_y += mVelocity.m_y * fixedTimeStep;
    
    // Expansion logic
    std::uniform_real_distribution<> distribution(0.0, 1.0);
    if (distribution(mRandom) < BubbleExpansionProbability)
    {
        mCurrentRadius += BubbleExpansionAmount;
        
        // Check if bubble popped
        if (mCurrentRadius > BubbleMaximumRadius)
        {
            mPopped = true;
        }
    }
} 