/**
 * @file PictureFactory.cpp
 *
 * @author Charles Owen
 * @author Anik Momtaz
 */

#include "pch.h"
#include "PictureFactory.h"
#include "Picture.h"
#include "HaroldFactory.h"
#include "SpartyFactory.h"
#include "Actor.h"
#include "ImageDrawable.h"


/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"/images";


/**
 * Constructor
 */
PictureFactory::PictureFactory()
{
}

/**
 * Create the picture.
 * @param resourcesDir Directory that contains the images, audio, etc.
 * @return The created picture
 */
std::shared_ptr<Picture> PictureFactory::Create(std::wstring resourcesDir)
{
    // Store the resources directory for future use
    mResourcesDir = resourcesDir;
    
    auto imagesDir = resourcesDir + ImagesDirectory;

    // Create a picture that will contain the animation
    auto picture = std::make_shared<Picture>(resourcesDir);

    // Create the background and add it
    auto background = std::make_shared<Actor>(L"Background");
    background->SetClickable(false);
    background->SetPosition(wxPoint(0, 0));
    auto backgroundI =
            std::make_shared<ImageDrawable>(L"Background", imagesDir + L"/Background2.png");
    background->AddDrawable(backgroundI);
    background->SetRoot(backgroundI);
    picture->AddActor(background);

    // Create and add Harold
    HaroldFactory haroldFactory;
    auto harold = haroldFactory.Create(imagesDir);

    // This is where Harold will start out.
    harold->SetPosition(wxPoint(150, 600));
    picture->AddActor(harold);

    // Create and add Sparty
    SpartyFactory spartyFactory;
    auto sparty = spartyFactory.Create(imagesDir);

    sparty->SetPosition(wxPoint(650, 620));
    picture->AddActor(sparty);

    return picture;
}

