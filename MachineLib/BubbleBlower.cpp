/**
 * @file BubbleBlower.cpp
 * @author 
 */

#include "pch.h"
#include "BubbleBlower.h"
#include "Bubble.h"
#include "Polygon.h"

// Initialize static constants
const double BubbleBlower::BubblePerRotation = 5.0;
const double BubbleBlower::BubbleVariancePerSecond = 100.0;
const double BubbleBlower::BubbleAngleVariance = 0.1;
const double BubbleBlower::BubbleMachineAngleRange = 0.25;
const double BubbleBlower::BubbleBlowerOffset = 100.0;
const double BubbleBlower::BubbleBlowerOffsetVariance = 5.0;
const double BubbleBlower::BubbleMinimumVelocity = 20.0;
const double BubbleBlower::BubbleMaximumVelocity = 40.0;

/**
 * Constructor
 */
BubbleBlower::BubbleBlower()
{
    // Create the base for the bubble blower, but make it invisible
    auto base = GetBase();
    base->Rectangle(-BubbleBlowerWidth / 2, BubbleBlowerHiltOffset, BubbleBlowerWidth, BubbleBlowerHeight);
    base->SetColor(wxColor(0, 0, 0, 0));  // Transparent color
    
    // Create the sink for rotation input
    mSink = std::make_shared<Sink>();
    mSink->SetComponent(this);
    
    // Initialize the random number generator
    std::random_device rd;  // Generates a random seed
    mRandom.seed(rd());     // Seed the random number generator
    
    // Tilt the bubble blower slightly to the left (negative rotation)
    SetCurrentRotation(-0.12);  // About -43 degrees (increased from -0.07/-25 degrees)
}

/**
 * Draw the bubble blower and its bubbles
 * @param graphics Graphics context to draw on
 * @param position Position to draw at
 */
void BubbleBlower::Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position)
{
    // Draw the bubble blower itself 
    Component::Draw(graphics, position);
    
    // Draw all the bubbles with correct positioning
    // We need to apply the position offset to the bubbles since they're in component coordinates
    for (auto bubble : mBubbles)
    {
        // Get the bubble's current position
        wxPoint2DDouble bubblePos = bubble->GetPosition();
        
        // Save original position
        wxPoint2DDouble originalPos = bubblePos;
        
        // Apply machine position offset to convert from component to screen coordinates
        bubblePos.m_x += position.x;
        bubblePos.m_y += position.y;
        
        // Temporarily set the bubble's position to the adjusted position
        bubble->SetPosition(bubblePos);
        
        // Draw the bubble
        bubble->Draw(graphics);
        
        // Restore the original position 
        bubble->SetPosition(originalPos);
    }
}

/**
 * Update the bubble blower and its bubbles
 * @param time Current time in seconds
 */
void BubbleBlower::Update(double time)
{
    // Create new bubbles
    BlowBubbles(time);
    
    // Remove bubbles that have gone far off-screen
    // Use much larger boundaries to ensure bubbles completely exit the view
    auto iter = mBubbles.begin();
    while (iter != mBubbles.end())
    {
        auto bubble = *iter;
        bubble->Update(time);
        
        auto pos = bubble->GetPosition();
        
        // Only remove bubbles when they are very far off screen
        // This prevents bubbles from appearing to "pop" at the edges
        if (pos.m_y > 600 || pos.m_y < -600 || 
            pos.m_x > 800 || pos.m_x < -800)
        {
            iter = mBubbles.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}

/**
 * Set the time for this component
 * @param time Time in seconds
 */
void BubbleBlower::SetTime(double time)
{
    Component::SetTime(time);
    
    // Only update if time is positive (after start button is clicked)
    if (time > 0)
    {
        // Update the component at this time step
        Update(time);
    }
    else
    {
        // Reset previous rotation when time is reset
        mPreviousRotation = GetCurrentRotation();
    }
}

/**
 * Create a single bubble with randomized parameters
 */
void BubbleBlower::CreateBubble()
{
    // GetRotation gets the rotation of the bubble blower.
    // This code computes a vector to the emitting end of the
    // bubble blower. The random value means that position is over
    // the entire end of the machine, not just a single point.
    auto angle = GetRotation() * 2 * M_PI + Random(-BubbleMachineAngleRange, BubbleMachineAngleRange);
    auto dx = sin(angle);
    auto dy = -cos(angle);

    auto angle1 = angle + Random(-BubbleAngleVariance, BubbleAngleVariance) + M_PI / 2;
    auto dx1 = sin(angle1);
    auto dy1 = -cos(angle1);

    double offset = BubbleBlowerOffset + Random(-BubbleBlowerOffsetVariance, BubbleBlowerOffsetVariance);
    double velocity = Random(BubbleMinimumVelocity, BubbleMaximumVelocity);

    // Add a left offset of 35 pixels to move bubble creation position leftward
    wxPoint2DDouble bubblePosition(
        (float)(GetX() + dx * offset - 35),  // Increased from -20 to -35 pixels
        (float)(GetY() + dy * offset)
    );
    wxPoint2DDouble bubbleVelocity((float)(dx1 * velocity), (float)(dy1 * velocity));
    
    // Create a new bubble
    auto bubble = std::make_shared<Bubble>();
    bubble->SetPosition(bubblePosition);
    bubble->SetVelocity(bubbleVelocity);
    
    // Set the bubble image
    if (!mImageDirectory.empty())
    {
        std::wstring imagePath = mImageDirectory + L"/bubble.png";
        bubble->SetImage(imagePath);
    }
    else
    {
        // Force red color for visibility if no image
        bubble->GetImage()->SetColor(wxColor(255, 0, 0, 255));
    }
    
    // Add to collection
    AddBubble(bubble);
}

/**
 * Blow bubbles based on the current time
 * @param time Current time in seconds
 */
void BubbleBlower::BlowBubbles(double time)
{
    // Calculate rotation for bubble generation
    double currentRotation = GetCurrentRotation();
    double rotation = currentRotation - mPreviousRotation;
    mPreviousRotation = currentRotation;
    
    // Prevent negative rotation (which can happen with direction changes)
    if (rotation < 0)
    {
        rotation = 0;
    }
    
    // Compute how many bubbles to generate for this amount of rotation
    // First calculate using the specification formula
    auto baseNum = int(rotation * (BubblePerRotation + Random(-BubbleVariancePerSecond/2, BubbleVariancePerSecond)));
    
    // Increase bubble count by 30%
    auto num = int(baseNum * 1.3);
    
    // Ensure at least one bubble is created if there is meaningful rotation
    if (rotation > 0.02 && num < 1)
    {
        num = 1;
    }
    
    // Create the bubbles
    for (int i = 0; i < num; i++)
    {
        CreateBubble();
    }
}

/**
 * Add a bubble to the bubble blower
 * @param bubble Bubble to add
 */
void BubbleBlower::AddBubble(std::shared_ptr<Bubble> bubble)
{
    mBubbles.push_back(bubble);
}

/**
 * Test if a point is within the bubble blower
 * @param pos Position to test
 * @return true if position is in bubble blower
 */
bool BubbleBlower::HitTest(wxPoint pos)
{
    // Simple rectangular hit test
    if (pos.x >= -BubbleBlowerWidth/2 && pos.x <= BubbleBlowerWidth/2 &&
        pos.y >= BubbleBlowerHiltOffset && pos.y <= BubbleBlowerHiltOffset + BubbleBlowerHeight)
    {
        return true;
    }
    
    return false;
}

/**
 * Generate a uniform distribution random number from fmValue to toValue
 * @param fmValue Minimum value to generate
 * @param toValue Maximum value to generate
 * @return Random number
 */
double BubbleBlower::Random(double fmValue, double toValue)
{
    std::uniform_real_distribution<> distribution(fmValue, toValue);
    return distribution(mRandom);
} 