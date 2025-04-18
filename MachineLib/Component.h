/**
 * @file Component.h
 *
 * @author Aditya Menon
 *
 * Base class for machine components
 */

#ifndef CANADIANEXPERIENCE_COMPONENT_H
#define CANADIANEXPERIENCE_COMPONENT_H

#include "Polygon.h"
#include <memory>
#include <vector>

// Forward declaration
class Machine;

/**
 * Base class for machine components
 */
class Component
{
protected:
    /// The machine this component is part of
    Machine* mMachine = nullptr;

    /// The position of this component
    wxPoint2DDouble mPosition = wxPoint2DDouble(0, 0);

    /// The rotation of this component in turns (0-1)
    double mRotation = 0;

    /// The polygon used to draw this component
    cse335::Polygon mPolygon;

public:
    /// Default constructor (disabled)
    Component() = delete;

    /**
     * Constructor
     * @param machine The machine this component is part of
     */
    Component(Machine* machine);

    /// Destructor
    virtual ~Component() = default;

    /// Copy constructor (disabled)
    Component(const Component &) = delete;

    /// Assignment operator (disabled)
    void operator=(const Component &) = delete;

    /**
     * Set the position of this component
     * @param x X position
     * @param y Y position
     */
    virtual void SetPosition(double x, double y);

    /**
     * Get the X coordinate of the component
     * @return X coordinate in pixels
     */
    double GetX() const { return mPosition.m_x; }

    /**
     * Get the Y coordinate of the component
     * @return Y coordinate in pixels
     */
    double GetY() const { return mPosition.m_y; }

    /**
     * Get the position of the component
     * @return Position in pixels as a point
     */
    wxPoint2DDouble GetPosition() const { return mPosition; }

    /**
     * Draw this component
     * @param graphics Graphics context to draw on
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * Set the rotation of this component
     * @param rotation Rotation in turns (0-1 is one complete rotation)
     */
    virtual void SetRotation(double rotation);

    /**
     * Get the rotation of this component
     * @return Rotation in turns (0-1 is one complete rotation)
     */
    double GetRotation() const { return mRotation; }

    /**
     * Update the component for the current time
     * @param time Current machine time in seconds
     */
    virtual void SetTime(double time) {}
};

#endif //CANADIANEXPERIENCE_COMPONENT_H 