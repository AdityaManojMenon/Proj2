/**
 * @file Picture.cpp
 * @author Charles B. Owen
 */
#include "pch.h"
#include <wx/stdpaths.h>

#include "Picture.h"
#include "PictureObserver.h"
#include "Actor.h"
#include "MachineAdapter.h"

using namespace std;

/**
 * Constructor with resource directory
 * @param resourcesDir Directory that contains resources for this application
 */
Picture::Picture(const std::wstring& resourcesDir)
{
    // Create and add first machine
    mMachine1 = std::make_shared<MachineAdapter>(resourcesDir, L"Machine 1");
    mMachine1->SetPosition(wxPoint(400, 500));  // Moved more to the left
    mMachine1->SetStartFrame(30);  // Starts at frame 30 (1 second at 30fps)

    // Create and add second machine
    mMachine2 = std::make_shared<MachineAdapter>(resourcesDir, L"Machine 2");
    mMachine2->SetPosition(wxPoint(1100, 500));  // Moved further to the right
    mMachine2->SetMachineNumber(2);  // Set it to a different machine type
    mMachine2->SetStartFrame(90);  // Starts at frame 90 (3 seconds at 30fps)
}

/**
 * Constructor
 */
Picture::Picture()
{
    // Default constructor - machines will be created later
}

/**
 * Set the animation time
 *
 * This sets the animation time for the picture, which
 * is then passed to all actors.
 *
 * @param time The new animation time in seconds
 */
void Picture::SetAnimationTime(double time)
{
    mTimeline.SetCurrentTime(time);
    
    for (auto actor : mActors)
    {
        actor->GetKeyframe();
    }
    
    // Update machines with the current frame
    int frame = (int)(time * 30);  // Assuming 30fps
    
    if (mMachine1 != nullptr)
    {
        mMachine1->SetFrame(frame);
    }
    
    if (mMachine2 != nullptr)
    {
        mMachine2->SetFrame(frame);
    }
    
    UpdateObservers();
}

/**
 * Get the current animation time.
 * @return The current animation time
 */
double Picture::GetAnimationTime()
{
    return mTimeline.GetCurrentTime();
}

/**
 * Add an observer to this picture.
 * @param observer The observer to add
 */
void Picture::AddObserver(PictureObserver* observer)
{
    mObservers.push_back(observer);
}

/**
 * Remove an observer from this picture
 * @param observer The observer to remove
 */
void Picture::RemoveObserver(PictureObserver* observer)
{
    auto loc = find(std::begin(mObservers), std::end(mObservers), observer);
    if (loc != std::end(mObservers))
    {
        mObservers.erase(loc);
    }
}

/**
 * Advance all observers to indicate the picture has changed.
 */
void Picture::UpdateObservers()
{
    for (auto observer : mObservers)
    {
        observer->UpdateObserver();
    }
}

/**
 * Draw this picture on a device context
 * @param graphics The device context to draw on
 */
void Picture::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    for (auto actor : mActors)
    {
        actor->Draw(graphics);
    }
    
    // Draw the machines
    if (mMachine1 != nullptr)
    {
        mMachine1->Draw(graphics);
    }
    
    if (mMachine2 != nullptr)
    {
        mMachine2->Draw(graphics);
    }
}

/**
 * Add an actor to this drawable.
 * @param actor Actor to add
 */
void Picture::AddActor(std::shared_ptr<Actor> actor)
{
    mActors.push_back(actor);
    actor->SetPicture(this);
}

/**
 * Save the picture animation to a file
 * @param filename File to save to.
 */
void Picture::Save(const wxString &filename)
{
    wxXmlDocument document;

    auto root = new wxXmlNode(wxXML_ELEMENT_NODE, L"anim");
    document.SetRoot(root);
    
    root->AddAttribute(L"title", L"Canadian Experience");

    // Save the timeline animation into the XML
    mTimeline.Save(root);

    //
    // It is possible we would want to save other aspects
    // of the program here.
    //
    
    // Save the machines
    auto machinesNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"machines");
    root->AddChild(machinesNode);
    
    if (mMachine1 != nullptr)
    {
        auto machine1Node = new wxXmlNode(wxXML_ELEMENT_NODE, L"machine");
        machinesNode->AddChild(machine1Node);
        mMachine1->XmlSave(machine1Node);
    }
    
    if (mMachine2 != nullptr)
    {
        auto machine2Node = new wxXmlNode(wxXML_ELEMENT_NODE, L"machine");
        machinesNode->AddChild(machine2Node);
        mMachine2->XmlSave(machine2Node);
    }

    document.Save(filename);
}

/**
 * Load a picture animation from a file
 * @param filename file to load from
 */
void Picture::Load(const wxString &filename)
{
    wxXmlDocument document;
    document.Load(filename);

    auto root = document.GetRoot();
    
    // Load the timeline animation from the XML
    mTimeline.Load(root);
    
    // Load the machines if present
    auto machinesNode = root->GetChildren();
    while (machinesNode != nullptr)
    {
        if (machinesNode->GetName() == L"machines")
        {
            auto machineNode = machinesNode->GetChildren();
            while (machineNode != nullptr)
            {
                if (machineNode->GetName() == L"machine")
                {
                    wxString name = machineNode->GetAttribute(L"name", L"");
                    if (name == L"Machine 1" && mMachine1 != nullptr)
                    {
                        mMachine1->XmlLoad(machineNode);
                    }
                    else if (name == L"Machine 2" && mMachine2 != nullptr)
                    {
                        mMachine2->XmlLoad(machineNode);
                    }
                }
                
                machineNode = machineNode->GetNext();
            }
            
            break;
        }
        
        machinesNode = machinesNode->GetNext();
    }
}


