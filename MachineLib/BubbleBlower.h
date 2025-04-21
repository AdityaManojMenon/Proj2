/**
 * @file BubbleBlower.h
 * @author 
 *
 * Class for a bubble blower
 */

#ifndef BUBBLEBLOWER_H
#define BUBBLEBLOWER_H

#include "Component.h"
#include "Sink.h"
#include <memory>
#include <list>
#include <random>

// Forward references
class Bubble;

/**
 * Class for a bubble blower
 */
class BubbleBlower : public Component {
private:
    /// The bubble rate (bubbles per rotation)
    double mBubbleRate = 5.0;
    
    /// Collection of bubbles managed by this machine
    std::list<std::shared_ptr<Bubble>> mBubbles;
    
    /// The sink for receiving rotation
    std::shared_ptr<Sink> mSink;
    
    /// Random number generator
    std::mt19937 mRandom;
    
    /// Previous rotation value
    double mPreviousRotation = 0;
    
    /// Width of the bubble blower in pixels
    static const int BubbleBlowerWidth = 50;
    
    /// Height of the bubble blower in pixels
    static const int BubbleBlowerHeight = 150;
    
    /// Y offset to the hilt of the bubble blower in pixels
    static const int BubbleBlowerHiltOffset = 10;
    
    /// Average number of bubbles created per rotation
    static const double BubblePerRotation;
    
    /// Variance in how many bubbles are created
    static const double BubbleVariancePerSecond;
    
    /// Range of the random angle bubbles will be blown at
    static const double BubbleAngleVariance;
    
    /// Angle range for the tip of the bubble blower in radians
    static const double BubbleMachineAngleRange;
    
    /// Offset to the tip of bubble blower from middle in pixels
    static const double BubbleBlowerOffset;
    
    /// Random variance in the bubble blower offset
    static const double BubbleBlowerOffsetVariance;
    
    /// Minimum bubble velocity
    static const double BubbleMinimumVelocity;
    
    /// Maximum bubble velocity
    static const double BubbleMaximumVelocity;
    
    /// Image directory path for loading bubble image
    std::wstring mImageDirectory;

public:
    BubbleBlower();
    
    /**
     * Draw the bubble blower and its bubbles
     * @param graphics Graphics context to draw on
     * @param position Position to draw at
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position) override;
    
    /**
     * Set the time for this component
     * @param time Time in seconds
     */
    void SetTime(double time) override;
    
    /**
     * Update the bubble blower and its bubbles
     * @param time Current time in seconds
     */
    void Update(double time);
    
    /**
     * Blow bubbles based on the current time
     * @param time Current time in seconds
     */
    void BlowBubbles(double time);
    
    /**
     * Create a single bubble with randomized parameters
     */
    void CreateBubble();
    
    /**
     * Add a bubble to the bubble blower
     * @param bubble Bubble to add
     */
    void AddBubble(std::shared_ptr<Bubble> bubble);
    
    /**
     * Test if a point is within the bubble blower
     * @param pos Position to test
     * @return true if position is in bubble blower
     */
    bool HitTest(wxPoint pos) override;
    
    /**
     * Generate a uniform distribution random number from fmValue to toValue
     * @param fmValue Minimum value to generate
     * @param toValue Maximum value to generate
     * @return Random number
     */
    double Random(double fmValue, double toValue);
    
    /**
     * Get the sink for this bubble blower
     * @return Sink pointer
     */
    std::shared_ptr<Sink> GetSink() { return mSink; }
    
    /**
     * Get X position of the bubble blower
     * @return X position
     */
    double GetX() { return GetPosition().x; }
    
    /**
     * Get Y position of the bubble blower
     * @return Y position
     */
    double GetY() { return GetPosition().y; }
    
    /**
     * Set the image directory for bubble images
     * @param directory Directory path for images
     */
    void SetImageDirectory(const std::wstring& directory) { mImageDirectory = directory; }
};

#endif //BUBBLEBLOWER_H 