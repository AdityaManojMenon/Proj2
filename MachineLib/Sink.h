/**
 * @file Sink.h
 *
 * @author Aditya Menon
 *
 * Class representing a sink component of a machine that receives rotation
 */

#ifndef CANADIANEXPERIENCE_SINK_H
#define CANADIANEXPERIENCE_SINK_H

#include "Component.h"
#include <memory>

// Forward declarations
class Machine;
class Source;
class Pulley;
class Shape;

/**
 * Class representing a sink component of a machine that receives rotation
 */
class Sink : public Component
{
private:
    /// The source that drives this sink (association)
    std::shared_ptr<Source> mSource;
    
    /// The component this sink is attached to (association)
    std::shared_ptr<Component> mComponent;
    
    /// The pulley this sink is connected to (composition)
    std::shared_ptr<Pulley> mPulley;
    
    /// The shape this sink is connected to (composition)
    std::shared_ptr<Shape> mShape;
    
    /// The current rotation
    double mRotation = 0.0;

public:
    /**
     * Constructor
     * @param machine The machine this sink is part of
     */
    Sink(Machine* machine);

    /** Default constructor (disabled) */
    Sink() = delete;

    /** Copy constructor (disabled) */
    Sink(const Sink &) = delete;

    /** Assignment operator (disabled) */
    void operator=(const Sink &) = delete;

    /**
     * Set the source for this sink
     * @param source Source to set
     */
    void SetSource(std::shared_ptr<Source> source);
    
    /**
     * Set the rotation for this sink
     * @param rotation Rotation value (0-1)
     */
    void SetRotation(double rotation) override;
    
    /**
     * Set the component this sink is attached to
     * @param component Component to set
     */
    void SetComponent(std::shared_ptr<Component> component);
    
    /**
     * Set the pulley this sink is connected to
     * @param pulley Pulley to set
     */
    void SetPulley(std::shared_ptr<Pulley> pulley);
    
    /**
     * Set the shape this sink is connected to
     * @param shape Shape to set
     */
    void SetShape(std::shared_ptr<Shape> shape);
    
    /**
     * Update for the current time
     * @param time Current time in seconds
     */
    virtual void SetTime(double time) override;
    
    /**
     * Draw this sink
     * @param graphics Graphics context to draw on
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
};

#endif //CANADIANEXPERIENCE_SINK_H 