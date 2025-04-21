/**
 * @file Shape.h
 * @author Adi M
 *
 * Class for shapes in the machine system
 */
 
#ifndef SHAPE_H
#define SHAPE_H

#include "Component.h"
#include "Sink.h"

/**
 * Class that represents a shape component
 */
class Shape : public Component, public Sink {
public:
    /// Constructor
    Shape();
    
    /**
     * Add a point to the shape
     * @param point Point to add
     */
    void AddPoint(wxPoint point);
    
    /**
     * Set the color of the shape
     * @param color Color to set
     */
    void SetColor(wxColor color);
    
    /**
     * Draw the shape
     * @param graphics Graphics context to draw on
     * @param position Position to draw at
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position) override;
    
    /**
     * Set the time for this component
     * @param time Time in seconds
     */
    void SetTime(double time) override;
};

#endif //SHAPE_H 
 
 
 
 