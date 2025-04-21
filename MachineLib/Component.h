/**
 * @file Component.h
 * @author Aditya Menon
 *
 * Base class for components
 */
 
#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>
#include <string>

// Forward references
class Machine;
namespace cse335 {
    class Polygon;
}

/**
 * Base class for components of a machine
 */
class Component {
private:
    /// The position of this component relative to the parent component
    wxPoint mPosition = wxPoint(0, 0);
    
    /// The component name
    std::string mName;
    
    /// The rotation in radians
    double mRotation = 0;
    
    /// The polygon that makes up the component base
    std::shared_ptr<cse335::Polygon> mBase;
    
    /// Current rotation of the component
    double mCurrentRotation = 0;
    
    /// Center for the component relative to position
    wxPoint mCenter = wxPoint(0, 0);
    
    /// The machine this component is associated with
    Machine* mMachine = nullptr;
    
    /// Phase offset for rotation
    double mPhase = 0;

public:
    Component();
    virtual ~Component();
    
    /**
     * Set the machine this component is associated with
     * @param machine Machine pointer
     */
    void SetMachine(Machine* machine);
    
    /**
     * Draw the component
     * @param graphics Graphics context to draw on
     * @param position Position to draw at
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position);
    
    /**
     * Get the current rotation
     * @return Rotation in radians
     */
    double GetRotation();
    
    /**
     * Get the base polygon
     * @return Polygon that makes up the base
     */
    std::shared_ptr<cse335::Polygon> GetBase();
    
    /**
     * Set the time for the component
     * @param time Time in seconds
     */
    virtual void SetTime(double time);
    
    /**
     * Set the current rotation of the component
     * @param rotation Rotation in radians
     */
    virtual void SetCurrentRotation(double rotation);
    
    /**
     * Get the current rotation of the component
     * @return Current rotation in radians
     */
    double GetCurrentRotation() const { return mCurrentRotation; }
    
    /**
     * Get the machine this component is associated with
     * @return Machine pointer
     */
    Machine* GetMachine();
    
    /**
     * Test if a point is within this component
     * @param pos Position to test
     * @return true if hit
     */
    virtual bool HitTest(wxPoint pos);
    
    /**
     * Set the position of this component
     * @param x X position in pixels
     * @param y Y position in pixels
     */
    void SetPosition(int x, int y);
    
    /**
     * Set the position of this component
     * @param position Position in pixels
     */
    void SetPosition(wxPoint position);
    
    /**
     * Get the position of this component
     * @return Position in pixels
     */
    wxPoint GetPosition() const { return mPosition; }
    
    /**
     * Draw a rectangle for this component
     * @param x Left edge
     * @param y Top edge
     * @param width Width of rectangle
     * @param height Height of rectangle
     */
    void Rectangle(int x, int y, int width, int height);
    
    /**
     * Set an image for this component
     * @param filename Image filename
     */
    void SetImage(const std::wstring& filename);
    
    /**
     * Set the phase offset for rotation
     * @param phase Phase offset (0-1)
     */
    void SetPhase(double phase);
    
    /**
     * Get the phase offset
     * @return Phase offset
     */
    double GetPhase() const { return mPhase; }
    
    /**
     * Place the component relative to an offset
     * @param offset Offset position
     */
    void Place(wxPoint offset);
    
    /**
     * Get the center point of the component
     * @return Center point
     */
    wxPoint Center() const { return mCenter; }
    
    /**
     * Helper function to set an image with proper path checking
     * @param imagePath Path to the image
     * @param defaultColor Default color to use if image not found
     * @return True if image was set successfully
     */
    bool SetComponentImage(const std::wstring& imagePath, wxColour defaultColor = *wxWHITE);
};

#endif //COMPONENT_H
