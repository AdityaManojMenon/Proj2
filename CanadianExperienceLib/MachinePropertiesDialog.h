/**
 * @file MachinePropertiesDialog.h
 * @author Aditya Menon
 *
 *
 */
 
#ifndef CANADIANEXPERIENCE_MACHINEPROPERTIESDIALOG_H
#define CANADIANEXPERIENCE_MACHINEPROPERTIESDIALOG_H



/**
 * Dialog class for setting machine properties
 */
class MachinePropertiesDialog : public wxDialog
{
private:
    /// The start frame value
    int mStartFrame;

    /// Control for start frame
    wxTextCtrl* mStartFrameCtrl;

    /// The scale value
    double mScale;

    /// Control for scale
    wxTextCtrl* mScaleCtrl;

public:
    /**
     * Constructor
     * @param parent Parent window
     * @param startFrame Initial start frame value
     * @param scale Initial scale value
     */
    MachinePropertiesDialog(wxWindow* parent, int startFrame, double scale);

    /**
     * Get the start frame
     * @return Start frame value
     */
    int GetStartFrame() const { return mStartFrame; }

    /**
     * Get the scale value
     * @return Scale value
     */
    double GetScale() const { return mScale; }

private:
    void OnOK(wxCommandEvent& event);
};



#endif //CANADIANEXPERIENCE_MACHINEPROPERTIESDIALOG_H

