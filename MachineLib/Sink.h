/**
 * @file Sink.h
 * @author Your Name
 *
 * Class for a sink component
 */
 
#ifndef SINK_H
#define SINK_H

#include <memory>

// Forward references
class Source;
class Component;

/**
 * Class for a sink component
 */
class Sink {
private:
    /// The source that drives this sink
    Source* mSource = nullptr;
    
    /// Current rotation in radians
    double mRotation = 0;
    
    /// The component this sink is associated with
    Component* mComponent = nullptr;

public:
    Sink() {}
    
    /**
     * Set the source that drives this sink
     * @param source Source pointer
     */
    void SetSource(Source* source) { mSource = source; }
    
    /**
     * Get the source that drives this sink
     * @return Source pointer
     */
    Source* GetSource() const { return mSource; }
    
    /**
     * Set the rotation for this sink
     * @param rotation Rotation in radians
     */
    void SetRotation(double rotation) { mRotation = rotation; }
    
    /**
     * Get the current rotation
     * @return Rotation in radians
     */
    double GetRotation() const { return mRotation; }
    
    /**
     * Set the component this sink is associated with
     * @param component Component pointer
     */
    void SetComponent(Component* component) { mComponent = component; }
    
    /**
     * Get the component this sink is associated with
     * @return Component pointer
     */
    Component* GetComponent() const { return mComponent; }
};

#endif //SINK_H 