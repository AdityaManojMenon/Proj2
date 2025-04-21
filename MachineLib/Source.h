/**
 * @file Source.h
 * @author Your Name
 *
 * Class for a source component
 */
 
#ifndef SOURCE_H
#define SOURCE_H

#include <vector>
#include <memory>

// Forward references
class Sink;

/**
 * Class for a source component
 */
class Source {
private:
    /// The collection of sinks driven by this source
    std::vector<Sink*> mSinks;
    
    /// Current rotation in radians
    double mRotation = 0;

public:
    Source() {}
    
    /**
     * Add a sink to this source
     * @param sink Sink to add
     */
    void AddSink(Sink* sink);
    
    /**
     * Set the rotation for this source
     * @param rotation Rotation amount in radians
     */
    void SetRotation(double rotation);
    
    /**
     * Get the current rotation
     * @return Rotation in radians
     */
    double GetRotation() const { return mRotation; }
};

#endif //SOURCE_H 
 
 
 
 