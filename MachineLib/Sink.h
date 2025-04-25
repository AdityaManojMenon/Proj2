/**
 * @file Sink.h
 * @author Aditya Menon
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
 * Class for a rotation sink
 */
class Sink {
private:
    /// The component we are connected to
    Component* mComponent = nullptr;

    /// The current rotation value
    double mRotation = 0;
    
    /// The source that drives this sink
    Source* mSource = nullptr;

public:
    /**
     * Constructor
     */
    Sink() {}

    /**
     * Destructor
     */
    virtual ~Sink() {}

    /**
     * Set the rotation value for this sink
     * @param rotation New rotation value
     */
    virtual void SetRotation(double rotation);

    /**
     * Get the current rotation value
     * @return Current rotation in rotations (0-1)
     */
    double GetRotation() { return mRotation; }

    /**
     * Set the component this sink is connected to
     * @param component Component pointer
     */
    void SetComponent(Component* component) { mComponent = component; }

    /**
     * Get the component this sink is connected to
     * @return Component pointer
     */
    Component* GetComponent() { return mComponent; }
    
    /**
     * Set the source that drives this sink
     * @param source Source pointer
     */
    void SetSource(Source* source) { mSource = source; }
    
    /**
     * Get the source that drives this sink
     * @return Source pointer
     */
    Source* GetSource() { return mSource; }
};

#endif //SINK_H 
 
 
 
 
 