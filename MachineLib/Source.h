/**
 * @file Source.h
 *
 * @author Aditya Menon
 *
 * Class representing a source component that drives rotation in a machine
 */

#ifndef CANADIANEXPERIENCE_SOURCE_H
#define CANADIANEXPERIENCE_SOURCE_H

#include "Component.h"
#include <memory>
#include <vector>

// Forward declarations
class Machine;
class Motor;
class Pulley;
class Sink;

/**
 * Class representing a source component that drives rotation in a machine
 */
class Source : public Component
{
private:
    /// Connected sink components
    std::vector<std::shared_ptr<Sink>> mSinks;
    
    /// Rotation value for generating rotation
    double mRotation = 0.0;
    
    /// Motors driven by this source
    std::vector<std::shared_ptr<Motor>> mMotors;
    
    /// Pulleys driven by this source
    std::vector<std::shared_ptr<Pulley>> mPulleys;

public:
    /**
     * Constructor
     * @param machine The machine this source is part of
     */
    Source(Machine* machine);

    /** Default constructor (disabled) */
    Source() = delete;

    /** Copy constructor (disabled) */
    Source(const Source &) = delete;

    /** Assignment operator (disabled) */
    void operator=(const Source &) = delete;
    
    /**
     * Add a sink to this source
     * @param sink Sink to add
     */
    void AddSink(std::shared_ptr<Sink> sink);
    
    /**
     * Add a motor to this source
     * @param motor Motor to add
     */
    void AddMotor(std::shared_ptr<Motor> motor);
    
    /**
     * Add a pulley to this source
     * @param pulley Pulley to add
     */
    void AddPulley(std::shared_ptr<Pulley> pulley);
    
    /**
     * Generate rotation
     * @param rotation Rotation value (0-1)
     */
    void GenerateRotation(double rotation);
    
    /**
     * Set the current time
     * @param time Current time in seconds
     */
    virtual void SetTime(double time) override;
    
    /**
     * Draw this source
     * @param graphics Graphics context to draw on
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
};

#endif //CANADIANEXPERIENCE_SOURCE_H 