/**
 * @file Component.cpp
 *
 * @author Aditya Menon
 */

#include "pch.h"
#include "Component.h"
#include "Machine.h"

/**
 * Constructor
 * @param machine The machine this component is part of
 */
Component::Component(Machine* machine) : mMachine(machine)
{
}

/**
 * Set the position of this component
 * @param x X position
 * @param y Y position
 */
void Component::SetPosition(double x, double y)
{
    mPosition = wxPoint2DDouble(x, y);
}

/**
 * Draw this component
 * @param graphics Graphics context to draw on
 */
void Component::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mPolygon.DrawPolygon(graphics, mPosition.m_x, mPosition.m_y);
}

/**
 * Set the rotation of this component
 * @param rotation Rotation in turns (0-1 is one complete rotation)
 */
void Component::SetRotation(double rotation)
{
    mRotation = rotation;
    mPolygon.SetRotation(rotation * 2 * M_PI);
} 