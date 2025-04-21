/**
 * @file Sink.cpp
 * @author Adi M
 */

#include "pch.h"
#include "Sink.h"
#include "Source.h"
#include "Component.h"

/**
 * Set the rotation for this sink
 * @param rotation Rotation in radians
 */
void Sink::SetRotation(double rotation)
{
    mRotation = rotation;
    
    // Update the component's rotation when the sink receives rotation
    if (mComponent != nullptr)
    {
        mComponent->SetCurrentRotation(rotation);
    }
} 
 
 
 
 