/**
 * @file Motor.h
 * @author Adi M
 *
 * Class for a motor
 */
 
#ifndef MOTOR_H
#define MOTOR_H

#include "Component.h"
#include <vector>

// Forward references
namespace cse335 {
    class Polygon;
}

/**
 * Class for a motor
 */
class Motor : public Component {
private:
    /// The motor speed
    double mSpeed = 1.0;
    
    /// Components driven by this motor
    std::vector<Component*> mDrivenComponents;

public:
    /// Size of the motor
    static const int Size = 80;
    
    Motor();
    
    /**
     * Constructor
     * @param imagesDir Directory containing images
     */
    Motor(std::wstring imagesDir);
    
    /**
     * Set the motor speed
     * @param speed Speed in rotations per second
     */
    void SetSpeed(double speed);
    
    /**
     * Get the motor speed
     * @return Speed in rotations per second
     */
    double GetSpeed();
    
    void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position) override;
    
    void SetTime(double time) override;
    
    /**
     * Hit test for the motor
     * @param pos Position to test
     * @return true if position is in motor
     */
    bool HitTest(wxPoint pos) override;
    
    /**
     * Add a sink that will be driven by this motor
     * @param sink Pointer to sink component
     */
    void AddSink(Component* sink);
    
    /**
     * Get the source component for this motor
     * @return Pointer to the source
     */
    std::shared_ptr<Component> GetSource();
};

#endif //MOTOR_H
