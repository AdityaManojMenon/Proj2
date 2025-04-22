/**
 * @file MainFrame.h
 * @author Charles B. Owen
 *
 * The top-level (main) frame of the application
 */
#ifndef _MAINFRAME_H_
#define _MAINFRAME_H_

class ViewEdit;
class ViewTimeline;
class Picture;

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame
{
private:
    /// View class for our edit window
    ViewEdit *mViewEdit;

    /// View class for the timeline
    ViewTimeline *mViewTimeline;

    /// The picture object we are viewing/editing
    std::shared_ptr<Picture> mPicture;

    /// The animation playing timer
    wxTimer mTimer;

    /// Current animation frame rate in frames per second
    double mFrameRate = 30.0;

    /// Is the animation currently playing?
    bool mPlaying = false;

    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);

    // Menu file handlers
    void OnOpen(wxCommandEvent& event);
    void OnSaveAs(wxCommandEvent& event);

    // Animation event handlers
    void OnPlayAnimation(wxCommandEvent& event);
    void OnPlayAnimationWithoutGears(wxCommandEvent& event);
    void OnSetAnimationSpeed(wxCommandEvent& event);
    void OnSetAnimationStop(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);
    
    // Machine menu handlers
    void OnMachine1Properties(wxCommandEvent& event);
    void OnMachine1Select(wxCommandEvent& event);
    void OnMachine2Properties(wxCommandEvent& event);
    void OnMachine2Select(wxCommandEvent& event);

    /// The resources directory to use
    std::wstring mResourcesDir;

public:
    MainFrame(std::wstring resourcesDir);

    void Initialize();
};

#endif //_MAINFRAME_H_
