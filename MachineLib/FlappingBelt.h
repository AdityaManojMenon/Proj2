/**
 * @file FlappingBelt.h
 * @author Aditya Menon
 *
 * Class for a flapping belt that animates like a real belt
 */

#ifndef FLAPPINGBELT_H
#define FLAPPINGBELT_H

#include "Component.h"
#include <memory>
#include <vector>

// Forward declaration
namespace cse335 {
    class Polygon;
}

/**
 * Class for a flapping belt that connects pulleys
 */
class FlappingBelt : public Component {
private:
    /// Points along the belt path
    std::vector<wxPoint> mPoints;
    
    /// Thickness of the belt
    double mThickness = 5.0;
    
    /// Color of the belt
    wxColor mColor = wxColor(0, 0, 0);
    
    /// Starting time - used for animation
    double mTime = 0;
    
    /// Maximum amount to rock the belt
    const double BeltRockAmount = 0.01;
    
    /// How quickly to rock the belt in radians per second
    /// This is divided by the length to get the actual rate
    const double BeltRockBaseRate = M_PI * 1000;

public:
    /**
     * Constructor
     */
    FlappingBelt();
    
    /**
     * Draw the belt
     * @param graphics Graphics context to draw on
     * @param position Position of the belt
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position) override;
    
    /**
     * Set the time for this component
     * @param time Time in seconds
     */
    virtual void SetTime(double time) override;
    
    /**
     * Add a point to the belt path
     * @param point Point to add
     */
    void AddPoint(wxPoint point);
    
    /**
     * Set the thickness of the belt
     * @param thickness Thickness in pixels
     */
    void SetThickness(double thickness) { mThickness = thickness; }
    
    /**
     * Set the color of the belt
     * @param color Color to set
     */
    void SetColor(wxColor color) { mColor = color; }
};

#endif //FLAPPINGBELT_H 