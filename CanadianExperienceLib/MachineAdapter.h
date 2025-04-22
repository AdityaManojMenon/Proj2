/**
 * @file MachineAdapter.h
 * @author Aditya Menon
 *
 * Adapter class that makes IMachineSystem work as a Drawable
 */

#ifndef CANADIANEXPERIENCE_MACHINEADAPTER_H
#define CANADIANEXPERIENCE_MACHINEADAPTER_H

#include "Drawable.h"
#include <machine-api.h>

/**
 * Class that adapts the IMachineSystem to be a Drawable for
 * the Canadian Experience
 */
class MachineAdapter : public Drawable
{
private:
    /// The machine system we are adapting
    std::shared_ptr<IMachineSystem> mMachine;

    /// The machine number
    int mMachineNumber = 1;

    /// Frame when this machine starts
    int mStartFrame = 0;

    /// Flag to track if machine is running
    bool mRunning = false;

    /// Machine scaling factor
    double mScale = 0.75;

    /// Directory containing resources
    std::wstring mResourcesDir;

public:
    /// Default constructor (disabled)
    MachineAdapter() = delete;

    /**
     * Constructor
     * @param resourcesDir Directory containing resources
     * @param name Name for this drawable
     */
    MachineAdapter(const std::wstring& resourcesDir, const std::wstring& name);

    /**
     * Draw the machine at the current position
     * @param graphics Graphics context to draw on
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Test if a point is inside the drawable
     * @param point Point to test
     * @return true if point is inside
     */
    virtual bool HitTest(wxPoint point) override;

    /**
     * Set the current animation frame
     * @param frame Frame number
     */
    void SetFrame(int frame);

    /**
     * Get the start frame for this machine
     * @return Start frame
     */
    int GetStartFrame() const { return mStartFrame; }

    /**
     * Set the start frame for this machine
     * @param startFrame Start frame number
     */
    void SetStartFrame(int startFrame) { mStartFrame = startFrame; }

    /**
     * Get the current machine number
     * @return Machine number
     */
    int GetMachineNumber() const { return mMachineNumber; }

    /**
     * Set the machine number
     * @param machineNumber Machine number
     */
    void SetMachineNumber(int machineNumber);

    /**
     * Get the machine scale
     * @return Scale factor
     */
    double GetScale() const { return mScale; }

    /**
     * Set the machine scale factor
     * @param scale Scale factor
     */
    void SetScale(double scale) { mScale = scale; }

    /**
     * Show the machine configuration dialog
     * @param parent Parent window
     * @return true if OK was pressed
     */
    bool ShowDialog(wxWindow* parent);

    /**
     * Save this drawable to an XML node
     * @param node Node to save to
     */
    virtual void XmlSave(wxXmlNode* node);

    /**
     * Load this drawable from an XML node
     * @param node Node to load from
     */
    virtual void XmlLoad(wxXmlNode* node);
};

#endif //CANADIANEXPERIENCE_MACHINEADAPTER_H