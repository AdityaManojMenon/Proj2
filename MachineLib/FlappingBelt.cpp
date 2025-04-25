/**
 * @file FlappingBelt.cpp
 * @author Aditya Menon
 */

#include "pch.h"
#include "FlappingBelt.h"
#include "Polygon.h"
#include "Component.h"
#include <cmath>

/**
 * Constructor
 */
FlappingBelt::FlappingBelt()
{
    // Create a minimal triangle shaped polygon that won't be visible
    // The Component class already creates a base polygon for us in its constructor
    // We just need to add points and set it as invisible
    auto base = GetBase();
    
    // Add three points to create a minimal triangle
    base->AddPoint(-1, -1);
    base->AddPoint(1, -1);
    base->AddPoint(0, 1);
    
    // Make the polygon invisible
    base->SetColor(wxColor(0, 0, 0, 0));
}

/**
 * Add a point to the belt path
 * @param point Point to add
 */
void FlappingBelt::AddPoint(wxPoint point)
{
    mPoints.push_back(point);
}

/**
 * Set the time for this component
 * @param time Time in seconds
 */
void FlappingBelt::SetTime(double time)
{
    Component::SetTime(time);
    mTime = time;
}

/**
 * Draw the belt
 * @param graphics Graphics context to draw on
 * @param position Position of the belt
 */
void FlappingBelt::Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position)
{
    // Call the parent to draw any underlying components
    Component::Draw(graphics, position);
    
    // Need at least two points to draw a belt
    if (mPoints.size() < 2)
        return;
        
    // Set the color and line width for the belt
    graphics->SetPen(wxPen(mColor, mThickness));
    
    // Create a path for the belt
    wxGraphicsPath path = graphics->CreatePath();
    
    // Start at the first point
    path.MoveToPoint(mPoints[0].x + position.x, mPoints[0].y + position.y);
    
    // For each line segment in the belt
    for (size_t i = 1; i < mPoints.size(); i++)
    {
        // Get the current point and previous point
        wxPoint start = mPoints[i-1];
        wxPoint end = mPoints[i];
        
        // Calculate distance between points
        double dx = end.x - start.x;
        double dy = end.y - start.y;
        double length = std::sqrt(dx * dx + dy * dy);
        
        // Skip very short segments
        if (length < 1.0)
            continue;
            
        // Calculate unit vector perpendicular to the line segment
        double perpX = -dy / length;
        double perpY = dx / length;
        
        // Calculate the rock frequency based on length
        double rockRate = BeltRockBaseRate / length;
        
        // Calculate the rock amount based on time and position along belt
        double rockAmount = BeltRockAmount * length * sin(rockRate * mTime);
        
        // Calculate the control points for the Bézier curve
        // The control points are offset perpendicular to the line to create the flapping effect
        double ctrlX1 = start.x + position.x + perpX * rockAmount;
        double ctrlY1 = start.y + position.y + perpY * rockAmount;
        
        double ctrlX2 = end.x + position.x - perpX * rockAmount;
        double ctrlY2 = end.y + position.y - perpY * rockAmount;
        
        // Add a curved line to the path
        path.AddCurveToPoint(ctrlX1, ctrlY1, ctrlX2, ctrlY2, end.x + position.x, end.y + position.y);
    }
    
    // Draw the path
    graphics->StrokePath(path);
} 