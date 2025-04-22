/**
 * @file MainFrame.cpp
 * @author Charles B. Owen
 */
#include "pch.h"

#include <wx/xrc/xmlres.h>
#include <wx/stdpaths.h>

#include "MainFrame.h"

#include "ViewEdit.h"
#include "ViewTimeline.h"
#include "Picture.h"
#include "PictureFactory.h"
#include "MachineAdapter.h"
#include "MachinePropertiesDialog.h"

/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"/images";

// Machine menu constants
const int ID_MACHINE1_PROPERTIES = wxID_HIGHEST + 300;
const int ID_MACHINE1_SELECT = wxID_HIGHEST + 301;
const int ID_MACHINE2_PROPERTIES = wxID_HIGHEST + 302;
const int ID_MACHINE2_SELECT = wxID_HIGHEST + 303;

/**
 * Constructor
 * @param resourcesDir Directory path containing resources
 */
MainFrame::MainFrame(std::wstring resourcesDir) :
    mResourcesDir(resourcesDir)
{

}



/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    wxXmlResource::Get()->LoadFrame(this, nullptr, L"MainFrame");
#ifdef WIN32
    SetIcon(wxIcon(L"mainframe", wxBITMAP_TYPE_ICO_RESOURCE));
#endif

    auto sizer = new wxBoxSizer( wxVERTICAL );

    auto imagesDir = mResourcesDir + ImagesDirectory;

    mViewEdit = new ViewEdit(this);
    mViewTimeline = new ViewTimeline(this, imagesDir);

    sizer->Add(mViewEdit,1, wxEXPAND | wxALL );
    sizer->Add(mViewTimeline, 0, wxEXPAND | wxALL);

    SetSizer( sizer );
    Layout();

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);

    //
    // Create the picture
    //
    PictureFactory factory;
    mPicture = factory.Create(mResourcesDir);

    // Tell the views about the picture
    mViewEdit->SetPicture(mPicture);
    mViewTimeline->SetPicture(mPicture);

    // Add a machine menu
    auto machineMenu = new wxMenu();
    machineMenu->Append(ID_MACHINE1_PROPERTIES, L"Machine 1 &Properties...\tCtrl+1", L"Set Machine 1 Properties");
    machineMenu->Append(ID_MACHINE1_SELECT, L"Machine 1 &Select Type...", L"Select Machine 1 Type");
    machineMenu->AppendSeparator();
    machineMenu->Append(ID_MACHINE2_PROPERTIES, L"Machine 2 P&roperties...\tCtrl+2", L"Set Machine 2 Properties");
    machineMenu->Append(ID_MACHINE2_SELECT, L"Machine 2 S&elect Type...", L"Select Machine 2 Type");
    
    // Add it after Timeline menu
    GetMenuBar()->Insert(3, machineMenu, L"&Machines");
    
    // Bind machine menu events
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnMachine1Properties, this, ID_MACHINE1_PROPERTIES);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnMachine1Select, this, ID_MACHINE1_SELECT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnMachine2Properties, this, ID_MACHINE2_PROPERTIES);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnMachine2Select, this, ID_MACHINE2_SELECT);
}



/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
  Close(true);
}

/**
 * Application about box menu handler
 * @param event The menu command event
 */
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxDialog aboutDlg;
    wxXmlResource::Get()->LoadDialog(&aboutDlg, this, L"AboutDialog");
    aboutDlg.ShowModal();
}


/**
 * Handle a close event. Stop the animation and destroy this window.
 * @param event The Close event
 */
void MainFrame::OnClose(wxCloseEvent& event)
{
    mViewTimeline->Stop();
    Destroy();
}

/**
 * Handler for Machine 1 Properties menu option
 * @param event Menu event
 */
void MainFrame::OnMachine1Properties(wxCommandEvent& event)
{
    auto machine = mPicture->GetMachine1();
    if (machine == nullptr)
        return;
        
    MachinePropertiesDialog dlg(this, machine->GetStartFrame(), machine->GetScale());
    if (dlg.ShowModal() == wxID_OK)
    {
        machine->SetStartFrame(dlg.GetStartFrame());
        machine->SetScale(dlg.GetScale());
        mViewEdit->Refresh();
    }
}

/**
 * Handler for Machine 1 Select menu option
 * @param event Menu event
 */
void MainFrame::OnMachine1Select(wxCommandEvent& event)
{
    auto machine = mPicture->GetMachine1();
    if (machine == nullptr)
        return;
        
    if (machine->ShowDialog(this))
    {
        mViewEdit->Refresh();
    }
}

/**
 * Handler for Machine 2 Properties menu option
 * @param event Menu event
 */
void MainFrame::OnMachine2Properties(wxCommandEvent& event)
{
    auto machine = mPicture->GetMachine2();
    if (machine == nullptr)
        return;
        
    MachinePropertiesDialog dlg(this, machine->GetStartFrame(), machine->GetScale());
    if (dlg.ShowModal() == wxID_OK)
    {
        machine->SetStartFrame(dlg.GetStartFrame());
        machine->SetScale(dlg.GetScale());
        mViewEdit->Refresh();
    }
}

/**
 * Handler for Machine 2 Select menu option
 * @param event Menu event
 */
void MainFrame::OnMachine2Select(wxCommandEvent& event)
{
    auto machine = mPicture->GetMachine2();
    if (machine == nullptr)
        return;
        
    if (machine->ShowDialog(this))
    {
        mViewEdit->Refresh();
    }
}


