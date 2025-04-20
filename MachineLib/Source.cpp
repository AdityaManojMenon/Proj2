/**
 * @file Source.cpp
 */

#include "pch.h"
#include "Source.h"
#include "Sink.h"

/**
 * Add a sink to this source
 * @param sink Sink to add
 */
void Source::AddSink(Sink* sink)
{
    mSinks.push_back(sink);
    sink->SetSource(this);
}

/**
 * Set the rotation for this source
 * @param rotation Rotation amount in radians
 */
void Source::SetRotation(double rotation)
{
    mRotation = rotation;
    
    // Update all connected sinks with the new rotation
    for (auto sink : mSinks)
    {
        sink->SetRotation(rotation);
    }
}