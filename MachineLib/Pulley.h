/**
 * @file Pulley.h
 * @author Adi M
 *
 * A pulley for the machine
 */
 
#ifndef PULLEY_H
#define PULLEY_H

#include "Component.h"
#include <vector>
#include "Source.h"
#include "Sink.h"

// Forward references
class Sink;
class Source;

/**
 * A pulley for the machine
 */
class Pulley : public Component {
private:
    /// The pulley radius
    double mRadius;
    
    /// The phase offset in radians
    double mPhase = 0;
    
    /// Speed multiplier (1.0 = same speed as source)
    double mSpeedMultiplier = 1.0;
    
    /// The pulley driving this one
    Pulley* mDrivingPulley = nullptr;
    
    /// Pulleys connected to this one
    std::vector<Pulley*> mConnectedPulleys;
    
    /// Components directly driven by this pulley (not via Source/Sink)
    std::vector<Component*> mDrivenComponents;
    
    /// Source for driving other components
    std::shared_ptr<Source> mSource;
    
    /// Sink for receiving rotation from other components
    std::shared_ptr<Sink> mSink;

public:
    /**
     * Constructor
     * @param radius Radius of the pulley in pixels
     */
    Pulley(double radius);
    
    void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position) override;
    
    void SetTime(double time) override;
    
    /**
     * Set the phase for the pulley
     * @param phase Phase in radians
     */
    void SetPhase(double phase);
    
    /**
     * Set the speed multiplier for this pulley
     * @param multiplier Speed multiplier (1.0 = same as source)
     */
    void SetSpeedMultiplier(double multiplier) { mSpeedMultiplier = multiplier; }
    
    /**
     * Get the speed multiplier for this pulley
     * @return Speed multiplier
     */
    double GetSpeedMultiplier() const { return mSpeedMultiplier; }
    
    /**
     * Get the pulley sink for connections
     * @return Pointer to sink
     */
    std::shared_ptr<Sink> GetSink();
    
    /**
     * Get the pulley source for connections
     * @return Pointer to source
     */
    std::shared_ptr<Source> GetSource();
    
    /**
     * Hit test for the pulley
     * @param pos Position to test
     * @return true if position is in pulley
     */
    bool HitTest(wxPoint pos) override;
    
    /**
     * Connect this pulley to another with a belt
     * @param pulley Pulley to connect to
     */
    void ConnectBelt(Pulley* pulley);
    
    /**
     * Connect another pulley to this one
     * @param pulley Pulley to connect
     */
    void ConnectPulley(Pulley* pulley);
    
    /**
     * Update the pulley's state
     * @param time Current time in seconds
     */
    void Update(double time);
    
    /**
     * Add a sink that will be driven by this pulley
     * @param sink Pointer to sink component
     */
    void AddSink(Component* sink);
    
    /**
     * Get current rotation
     * @return Rotation in radians
     */
    double GetCurrentRotation() { return Component::GetCurrentRotation(); }
    
    /**
     * Override to propagate rotation to connected components
     * @param rotation Rotation in radians
     */
    void SetCurrentRotation(double rotation) override;
};

#endif //PULLEY_H 
 
 
 
 