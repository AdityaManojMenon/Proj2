/**
 * @file MachinePropertiesDialog.cpp
 * @author Aditya Menon
 */


#include "pch.h"
#include "MachinePropertiesDialog.h"

/**
 * Constructor
 * @param parent Parent window
 * @param startFrame Initial start frame value
 * @param scale Initial scale value
 */
MachinePropertiesDialog::MachinePropertiesDialog(wxWindow* parent, int startFrame, double scale)
    : wxDialog(parent, wxID_ANY, L"Machine Properties", wxDefaultPosition, wxDefaultSize,
              wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER),
    mStartFrame(startFrame), mScale(scale)
{
    // Create dialog controls
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Start frame control
    wxBoxSizer* startFrameSizer = new wxBoxSizer(wxHORIZONTAL);
    startFrameSizer->Add(new wxStaticText(this, wxID_ANY, L"Start Frame:"), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    mStartFrameCtrl = new wxTextCtrl(this, wxID_ANY, wxString::Format(L"%d", mStartFrame));
    startFrameSizer->Add(mStartFrameCtrl, 1, wxALL | wxEXPAND, 5);
    mainSizer->Add(startFrameSizer, 0, wxEXPAND);

    // Add explanation text
    wxString explanation = L"This is the frame when the machine will start running.\n"
                          L"Setting different start times allows machines to begin\n"
                          L"at different times in your animation.";
    mainSizer->Add(new wxStaticText(this, wxID_ANY, explanation), 0, wxALL, 10);

    // Scale control
    wxBoxSizer* scaleSizer = new wxBoxSizer(wxHORIZONTAL);
    scaleSizer->Add(new wxStaticText(this, wxID_ANY, L"Scale:"), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    mScaleCtrl = new wxTextCtrl(this, wxID_ANY, wxString::Format(L"%.2f", mScale));
    scaleSizer->Add(mScaleCtrl, 1, wxALL | wxEXPAND, 5);
    mainSizer->Add(scaleSizer, 0, wxEXPAND);

    // Add standard dialog buttons
    wxStdDialogButtonSizer* buttons = new wxStdDialogButtonSizer();
    buttons->AddButton(new wxButton(this, wxID_OK));
    buttons->AddButton(new wxButton(this, wxID_CANCEL));
    buttons->Realize();
    mainSizer->Add(buttons, 0, wxALL | wxALIGN_CENTER, 10);

    // Set dialog sizer
    SetSizer(mainSizer);
    Fit();

    // Bind event handlers
    Bind(wxEVT_BUTTON, &MachinePropertiesDialog::OnOK, this, wxID_OK);
}

/**
 * Handle OK button
 * @param event Button event
 */
void MachinePropertiesDialog::OnOK(wxCommandEvent& event)
{
    // Validate start frame
    long startFrame;
    if (!mStartFrameCtrl->GetValue().ToLong(&startFrame) || startFrame < 0)
    {
        wxMessageBox(L"Invalid start frame value. Please enter a positive number.",
                    L"Error", wxOK | wxICON_ERROR);
        return;
    }

    // Validate scale
    double scale;
    if (!mScaleCtrl->GetValue().ToDouble(&scale) || scale <= 0.0)
    {
        wxMessageBox(L"Invalid scale value. Please enter a positive number.",
                    L"Error", wxOK | wxICON_ERROR);
        return;
    }

    // Store values
    mStartFrame = startFrame;
    mScale = scale;

    // Close the dialog
    EndModal(wxID_OK);
}
