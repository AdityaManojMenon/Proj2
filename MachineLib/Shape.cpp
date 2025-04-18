/**
 * @file Shape.cpp
 *
 * @author Aditya Menon
 */

#include "pch.h"
#include "Shape.h"
#include "Machine.h"

/**
 * Constructor
 * @param machine The machine this shape is part of
 */
Shape::Shape(Machine* machine) : Component(machine)
{
}

/**
 * Set the color of this shape
 * @param color The color to set
 */
void Shape::SetColor(wxColour color)
{
    mPolygon.SetColor(color);
}

/**
 * Add a point to the shape polygon
 * @param point Point to add
 */
void Shape::AddPoint(wxPoint point)
{
    mPolygon.AddPoint(point.x, point.y);
}

/**
 * Draw this shape at the given position
 * @param graphics Graphics context to draw on
 * @param position Position to draw at
 */
void Shape::Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position)
{
    mPolygon.DrawPolygon(graphics, position.x, position.y);
}

/**
 * Set the image for this shape (not in UML but needed)
 * @param filename Filename for the image
 */
void Shape::SetImage(std::wstring filename)
{
    mPolygon.SetImage(filename);
}

/**
 * Create a rectangle shape (not in UML but needed)
 * @param x Left coordinate
 * @param y Top coordinate
 * @param width Width of the rectangle
 * @param height Height of the rectangle
 */
void Shape::Rectangle(double x, double y, double width, double height)
{
    mPolygon.Rectangle(x, y, width, height);
}

/**
 * Override of Component::Draw (not in UML but needed)
 * @param graphics Graphics context to draw on
 */
void Shape::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Use the Component::Draw which handles the polygon drawing
    Component::Draw(graphics);
} 
