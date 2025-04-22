/**
 * @file Shape.cpp
 * @author Aditya Menon
 */

#include "pch.h"
#include "Shape.h"
#include "Polygon.h"

/**
 * Constructor
 */
Shape::Shape()
{
    // Set this sink's component to this shape
    Sink::SetComponent(this);
}

/**
 * Add a point to the shape
 * @param point Point to add
 */
void Shape::AddPoint(wxPoint point)
{
    GetBase()->AddPoint(point.x, point.y);
}

/**
 * Set the color of the shape
 * @param color Color to set
 */
void Shape::SetColor(wxColor color)
{
    GetBase()->SetColor(color);
}

/**
 * Draw the shape
 * @param graphics Graphics context to draw on
 * @param position Position to draw at
 */
void Shape::Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position)
{
    Component::Draw(graphics, position);
}

/**
 * Set the time for this component
 * @param time Time in seconds
 */
void Shape::SetTime(double time)
{
    Component::SetTime(time);
    
    // No time-based behavior is needed for a basic shape
    // Any rotation would be applied through the Sink interface
} 