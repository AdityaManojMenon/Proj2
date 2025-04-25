/**
 * @file Bubble.h
 * @author Aditya Menon
 *
 * Class for a bubble
 */

#ifndef BUBBLE_H
#define BUBBLE_H

#include <memory>
#include <random>

namespace cse335 {
    class Polygon;
}

/**
 * Class for a bubble
 */
class Bubble {
private:
    /// The image used for the bubble
    std::shared_ptr<cse335::Polygon> mImage;
    
    /// The velocity of the bubble
    wxPoint2DDouble mVelocity;
    
    /// The position of the bubble
    wxPoint2DDouble mPosition;
    
    /// The current radius of the bubble
    double mCurrentRadius;
    
    /// Flag to indicate if the bubble has popped
    bool mPopped = false;
    
    /// Random number generator
    std::mt19937 mRandom;

public:
    /// Probability of a bubble expanding
    static const double BubbleExpansionProbability;
    
    /// The maximum possible radius of a bubble, after which it pops
    static const int BubbleMaximumRadius;
    
    /// The initial radius of a new bubble
    static const int BubbleInitialRadius;
    
    /// The amount the radius increases on expansion
    static const double BubbleExpansionAmount;

    Bubble();
    
    /**
     * Draw the bubble
     * @param graphics Graphics context to draw on
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    
    /**
     * Set the position of the bubble
     * @param position Position in pixels
     */
    void SetPosition(wxPoint2DDouble position) { mPosition = position; }
    
    /**
     * Get the position of the bubble
     * @return Position in pixels
     */
    wxPoint2DDouble GetPosition() const { return mPosition; }
    
    /**
     * Set the velocity of the bubble
     * @param velocity Velocity in pixels per second
     */
    void SetVelocity(wxPoint2DDouble velocity) { mVelocity = velocity; }
    
    /**
     * Get the velocity of the bubble
     * @return Velocity in pixels per second
     */
    wxPoint2DDouble GetVelocity() const { return mVelocity; }
    
    /**
     * Set the image for the bubble
     * @param imagePath Path to the bubble image
     */
    void SetImage(const std::wstring& imagePath);
    
    /**
     * Get the image polygon
     * @return Pointer to the image polygon
     */
    std::shared_ptr<cse335::Polygon> GetImage() { return mImage; }
    
    /**
     * Update the bubble position and size
     * @param elapsed Elapsed time in seconds
     */
    void Update(double elapsed);
    
    /**
     * Check if the bubble has popped
     * @return True if the bubble has popped
     */
    bool HasPopped() const { return mPopped; }
};

#endif //BUBBLE_H 