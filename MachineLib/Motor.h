/**
 * @file Motor.h
 *
 * @author Aditya Menon
 *
 * Class representing a motor component of a machine
 */

#ifndef CANADIANEXPERIENCE_MOTOR_H
#define CANADIANEXPERIENCE_MOTOR_H

#include "Component.h"
#include <vector>
#include <memory>

// Forward declarations
class Machine;

/**
 * Class representing a motor component of a machine
 */
class Motor : public Component
{
private:
    /// All the components driven by this motor
    std::vector<std::shared_ptr<Component>> mDriven;

    /// The speed of the motor in rotations per second
    double mSpeed = 0.2;

    /// Flag indicating if the motor is running
    bool mRunning = false;

    /// The current time for the motor
    double mCurrentTime = 0;

    /// The shaft/pulley polygon that rotates
    cse335::Polygon mShaft;

    /// The motor body polygon
    cse335::Polygon mMotor;

public:
    /// Size of the motor in pixels
    static const int Size = 80;

    /**
     * Constructor
     * @param machine The machine this motor is part of
     */
    Motor(Machine* machine);

    /** Default constructor (disabled) */
    Motor() = delete;

    /** Copy constructor (disabled) */
    Motor(const Motor &) = delete;

    /** Assignment operator (disabled) */
    void operator=(const Motor &) = delete;

    /**
     * Draw this motor
     * @param graphics Graphics context to draw on
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Set the position of this motor
     * @param x X position
     * @param y Y position
     */
    void SetPosition(double x, double y) override;

    /**
     * Test whether a point hits this object
     * @param pos Position to test
     * @return true if a hit, false otherwise
     */
    bool HitTest(wxPoint pos);

    /**
     * Add a component to be driven by this motor
     * @param component Component to drive
     */
    void AddComponent(std::shared_ptr<Component> component);

    /**
     * Set the speed of the motor
     * @param speed Speed in rotations per second
     */
    void SetSpeed(double speed) { mSpeed = speed; }

    /**
     * Get the speed of the motor
     * @return Speed in rotations per second
     */
    double GetSpeed() const { return mSpeed; }

    /**
     * Set the motor running state
     * @param running true if the motor should be running
     */
    void SetRunning(bool running) { mRunning = running; }

    /**
     * Get the running state of the motor
     * @return true if the motor is running
     */
    bool IsRunning() const { return mRunning; }

    /**
     * Set the current time
     * @param time Current time in seconds
     */
    void SetTime(double time) override;
};

#endif //CANADIANEXPERIENCE_MOTOR_H 