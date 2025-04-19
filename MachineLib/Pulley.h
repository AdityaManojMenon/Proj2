/**
 * @file Pulley.h
 *
 * @author Aditya Menon
 *
 * Class representing a pulley component of a machine
 */

#ifndef CANADIANEXPERIENCE_PULLEY_H
#define CANADIANEXPERIENCE_PULLEY_H

#include "Component.h"
#include <memory>
#include <vector>

// Forward declarations
class Machine;

/**
 * Class representing a pulley component of a machine
 */
class Pulley : public Component
{
private:
    /// The radius of the pulley
    double mRadius = 0;
    
    /// Connected pulleys
    std::vector<std::shared_ptr<Pulley>> mConnectedPulleys;

public:
    /**
     * Constructor
     * @param machine The machine this pulley is part of
     * @param radius The radius of the pulley in pixels
     */
    Pulley(Machine* machine, double radius);

    /** Default constructor (disabled) */
    Pulley() = delete;

    /** Copy constructor (disabled) */
    Pulley(const Pulley &) = delete;

    /** Assignment operator (disabled) */
    void operator=(const Pulley &) = delete;

    /**
     * Set the image for this pulley
     * @param filename Filename for the image
     */
    void SetImage(std::wstring filename);

    /**
     * Get the radius of the pulley
     * @return Radius in pixels
     */
    double GetRadius() const { return mRadius; }

    /**
     * Connect this pulley to another pulley
     * @param pulley The pulley to connect to
     */
    void ConnectPulley(std::shared_ptr<Pulley> pulley);

    /**
     * Get the connected pulleys
     * @return Vector of connected pulleys
     */
    std::vector<std::shared_ptr<Pulley>> GetConnectedPulleys() const { return mConnectedPulleys; }

    /**
     * Test if a point is inside the pulley (for mouse interaction)
     * @param x X position to test
     * @param y Y position to test
     * @return True if the point is inside the pulley
     */
    bool HitTest(double x, double y);

    /**
     * Update component for the current time
     * @param time Current machine time in seconds
     */
    virtual void SetTime(double time) override;

    /**
     * Draw this pulley
     * @param graphics Graphics context to draw on
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
};

#endif //CANADIANEXPERIENCE_PULLEY_H 