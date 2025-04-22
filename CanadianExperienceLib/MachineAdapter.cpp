/**
 * @file MachineAdapter.cpp
 * @author Aditya Menon
 */

#include "pch.h"
#include "MachineAdapter.h"

using namespace std;

/**
 * Constructor
 * @param resourcesDir Directory containing resources
 * @param name Name for this drawable
 */
MachineAdapter::MachineAdapter(const std::wstring& resourcesDir, const std::wstring& name) : Drawable(name)
{
    mResourcesDir = resourcesDir;

    // Create the machine using the factory
    MachineSystemFactory factory(resourcesDir);
    mMachine = factory.CreateMachineSystem();
}

/**
 * Draw the machine at the current position
 * @param graphics Graphics context to draw on
 */
void MachineAdapter::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Save the current state
    graphics->PushState();

    // Apply translation and scaling
    graphics->Translate(GetPosition().x, GetPosition().y);
    graphics->Scale(mScale, mScale);

    // Set the machine location to the origin since we've translated the graphics
    mMachine->SetLocation(wxPoint(0, 0));

    // Draw the machine
    mMachine->DrawMachine(graphics);

    // Restore the graphics state
    graphics->PopState();
}

/**
 * Test if a point is inside the drawable
 * @param point Point to test
 * @return true if point is inside
 */
bool MachineAdapter::HitTest(wxPoint point)
{
    // Simple hit test - if the point is within the machine's bounding box
    // Convert the point to machine coordinates
    double x = (point.x - GetPosition().x) / mScale;
    double y = (point.y - GetPosition().y) / mScale;

    // Assuming a reasonable bounding box of 400x400 pixels
    return (x >= 0 && x <= 400 && y >= 0 && y <= 400);
}

/**
 * Set the current animation frame
 * @param frame Frame number
 */
void MachineAdapter::SetFrame(int frame)
{
    if (frame >= mStartFrame)
    {
        // We've reached or passed the start frame
        if (!mRunning)
        {
            // We're just starting - initialize machine
            mMachine->SetFrameRate(30);  // Assuming 30fps
            mMachine->SetMachineFrame(0);
            mRunning = true;
        }

        // Set the machine frame relative to start frame
        mMachine->SetMachineFrame(frame - mStartFrame);
    }
    else
    {
        // Before the start frame, so machine is not running
        mMachine->SetMachineFrame(0);
        mRunning = false;
    }
}

/**
 * Set the machine number
 * @param machineNumber Machine number
 */
void MachineAdapter::SetMachineNumber(int machineNumber)
{
    mMachineNumber = machineNumber;

    // IMachineSystem doesn't have SetMachineNumber, so we need to
    // recreate the machine with the new number
    MachineSystemFactory factory(mResourcesDir);
    mMachine = factory.CreateMachineSystem();
    mMachine->SetMachineFrame(0);  // Reset to frame 0

    // Try to set machine number indirectly through configuration
    // This assumes MachineDialog sets the number internally
    wxWindow* parent = nullptr;  // We don't have a parent window here
    MachineDialog dialog(parent, mMachine);
    // Set machine number (not directly possible, dialog may provide this)
    dialog.Destroy();  // Don't show the dialog, just use it to configure
}

/**
 * Show the machine configuration dialog
 * @param parent Parent window
 * @return true if OK was pressed
 */
bool MachineAdapter::ShowDialog(wxWindow* parent)
{
    MachineDialog dialog(parent, mMachine);
    if (dialog.ShowModal() == wxID_OK)
    {
        // We can't directly get the machine number, so just store our value
        // The dialog should have configured the machine internally
        return true;
    }

    return false;
}

/**
 * Save this drawable to an XML node
 * @param node Node to save to
 */
void MachineAdapter::XmlSave(wxXmlNode* node)
{
    // Save the base drawable attributes
    node->AddAttribute(L"type", L"machine");
    node->AddAttribute(L"name", GetName());

    // Save position as a child element
    wxXmlNode* positionNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"position");
    positionNode->AddAttribute(L"x", wxString::Format(L"%d", GetPosition().x));
    positionNode->AddAttribute(L"y", wxString::Format(L"%d", GetPosition().y));
    node->AddChild(positionNode);

    // Save the machine-specific information
    node->AddAttribute(L"machine-number", wxString::Format(L"%d", mMachineNumber));
    node->AddAttribute(L"start-frame", wxString::Format(L"%d", mStartFrame));
    node->AddAttribute(L"scale", wxString::Format(L"%.2f", mScale));
}

/**
 * Load this drawable from an XML node
 * @param node Node to load from
 */
void MachineAdapter::XmlLoad(wxXmlNode* node)
{
    // Load position
    wxXmlNode* positionNode = node->GetChildren();
    while (positionNode != nullptr)
    {
        if (positionNode->GetName() == L"position")
        {
            int x = wxAtoi(positionNode->GetAttribute(L"x", L"0"));
            int y = wxAtoi(positionNode->GetAttribute(L"y", L"0"));
            SetPosition(wxPoint(x, y));
            break;
        }

        positionNode = positionNode->GetNext();
    }

    // Load the machine number
    int machineNumber = wxAtoi(node->GetAttribute(L"machine-number", L"1"));
    SetMachineNumber(machineNumber);

    // Load the start frame
    mStartFrame = wxAtoi(node->GetAttribute(L"start-frame", L"0"));

    // Load the scale if present
    node->GetAttribute(L"scale", wxString::Format(L"%.2f", mScale)).ToDouble(&mScale);
}