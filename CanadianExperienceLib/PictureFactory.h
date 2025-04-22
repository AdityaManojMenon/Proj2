/**
 * @file PictureFactory.h
 * @author Charles Owen
 *
 * A factory class that builds our picture.
 */

#ifndef CANADIANEXPERIENCE_PICTUREFACTORY_H
#define CANADIANEXPERIENCE_PICTUREFACTORY_H

class Picture;

/**
 * Factory class that creates the picture and adds all to it.
 */
class PictureFactory
{
public:
    /**
     * Constructor
    */
    PictureFactory();

    std::shared_ptr<Picture> Create(std::wstring imagesDir);
    
    /**
     * Get the last used resources directory
     * @return Resources directory path
     */
    std::wstring GetResourcesDir() const { return mResourcesDir; }

private:
    /// The resources directory
    std::wstring mResourcesDir;
};

#endif //CANADIANEXPERIENCE_PICTUREFACTORY_H
