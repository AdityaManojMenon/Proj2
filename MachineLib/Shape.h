/**
 * @file Shape.h
 *
 * @author Aditya Menon
 *
 * Class representing a shape component of a machine
 */

#ifndef CANADIANEXPERIENCE_SHAPE_H
#define CANADIANEXPERIENCE_SHAPE_H

#include "Component.h"

/**
 * Class representing a shape component of a machine
 */
class Shape : public Component
{
private:

public:
    /**
     * Constructor
     * @param machine The machine this shape is part of
     */
    Shape(Machine* machine);

    /** Default constructor (disabled) */
    Shape() = delete;

    /** Copy constructor (disabled) */
    Shape(const Shape &) = delete;

    /** Assignment operator (disabled) */
    void operator=(const Shape &) = delete;

    /**
     * Add a point to the shape polygon
     * @param point Point to add
     */
    void AddPoint(wxPoint point);

    /**
     * Set the color of this shape
     * @param color The color to set
     */
    void SetColor(wxColour color);

    /**
     * Draw this shape
     * @param graphics Graphics context to draw on
     * @param position Position to draw at
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position);

    // Methods not in UML but needed for implementation

    /**
     * Set the image for this shape (not in UML but needed)
     * @param filename Filename for the image
     */
    void SetImage(std::wstring filename);

    /**
     * Create a rectangle shape (not in UML but needed)
     * @param x Left coordinate
     * @param y Top coordinate
     * @param width Width of the rectangle
     * @param height Height of the rectangle
     */
    void Rectangle(double x, double y, double width, double height);

    /**
     * Override of Component::Draw (not in UML but needed)
     * @param graphics Graphics context to draw on
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
};

#endif //CANADIANEXPERIENCE_SHAPE_H 