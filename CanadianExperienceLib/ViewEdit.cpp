/**
 * @file ViewEdit.cpp
 * @author Charles B. Owen
 */
#include "pch.h"

#include <wx/dcbuffer.h>
#include <wx/stdpaths.h>
#include <wx/xrc/xmlres.h>

#include "ViewEdit.h"
#include "Picture.h"
#include "Actor.h"
#include "Drawable.h"
#include "MachineAdapter.h"
#include "MachinePropertiesDialog.h"

/// A scaling factor, converts mouse motion to rotation in radians
const double RotationScaling = 0.02;

/**
 * Constructor
 * @param parent Parent window for this window
 */
ViewEdit::ViewEdit(wxFrame* parent) : 
    wxScrolledCanvas(parent,
                     wxID_ANY,
                     wxDefaultPosition, 
                     wxDefaultSize,
                     wxHSCROLL | wxVSCROLL | wxBORDER_SUNKEN)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &ViewEdit::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &ViewEdit::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &ViewEdit::OnLeftUp, this);
    Bind(wxEVT_MOTION, &ViewEdit::OnMouseMove, this);
    Bind(wxEVT_LEFT_DCLICK, &ViewEdit::OnLeftDoubleClick, this);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, 
        &ViewEdit::OnEditMove, this, XRCID("EditMove"));
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, 
        &ViewEdit::OnEditRotate, this, XRCID("EditRotate"));
    parent->Bind(wxEVT_UPDATE_UI, 
        &ViewEdit::OnUpdateEditMove, this, XRCID("EditMove"));
    parent->Bind(wxEVT_UPDATE_UI, 
        &ViewEdit::OnUpdateEditRotate, this, XRCID("EditRotate"));

    mMode = Mode::Move;
}

/**
 * Force an update of this window when the picture changes.
 */
void ViewEdit::UpdateObserver()
{
    Refresh();
}



/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void ViewEdit::OnPaint(wxPaintEvent& event)
{
    auto size = GetPicture()->GetSize();
    SetVirtualSize(size.GetWidth(), size.GetHeight());
    SetScrollRate(1, 1);

    wxAutoBufferedPaintDC dc(this);
    DoPrepareDC(dc);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create( dc ));

    GetPicture()->Draw(graphics);
}

/**
 * Handle the left mouse button down event
 * @param event
 */
void ViewEdit::OnLeftDown(wxMouseEvent &event)
{
    auto click = CalcUnscrolledPosition(event.GetPosition());
    mLastMouse = click;

    //
    // Did we hit anything?
    //

    std::shared_ptr<Actor> hitActor;
    std::shared_ptr<Drawable> hitDrawable;
    for (auto actor : *GetPicture())
    {
        // Note: We do not exit when we get the first hit, since
        // we are looking at these in drawing order. Instead, we
        // keep the last hit.
        std::shared_ptr<Drawable> drawable = actor->HitTest(wxPoint(click.x, click.y));
        if (drawable != nullptr)
        {
            hitActor = actor;
            hitDrawable = drawable;
        }
    }

    // If we hit something determine what we do with it based on the
    // current mode.
    if (hitActor != nullptr)
    {
        mSelectedActor = hitActor;
        mSelectedDrawable = hitDrawable;
    }
}

/**
* Handle the left mouse button up event
* @param event
*/
void ViewEdit::OnLeftUp(wxMouseEvent &event)
{
    OnMouseMove(event);
}

/**
* Handle the mouse move event
* @param event
*/
void ViewEdit::OnMouseMove(wxMouseEvent &event)
{
    auto click = CalcUnscrolledPosition(event.GetPosition());

    wxPoint newMouse(click.x, click.y);
    wxPoint delta = newMouse - mLastMouse;
    mLastMouse = newMouse;

    if (event.LeftIsDown())
    {
        switch (mMode)
        {
        case Mode::Move:
            if (mSelectedDrawable != nullptr)
            {
                if (mSelectedDrawable->IsMovable())
                {
                    mSelectedDrawable->Move(delta);
                }
                else
                {
                    mSelectedActor->SetPosition(mSelectedActor->GetPosition() + delta);
                }
                GetPicture()->UpdateObservers();
            }
            break;

        case Mode::Rotate:
            if (mSelectedDrawable != nullptr)
            {
                mSelectedDrawable->SetRotation(mSelectedDrawable->GetRotation() + delta.y * RotationScaling);
                GetPicture()->UpdateObservers();
            }
            break;

        default:
            break;
        }

    }
    else
    {
        mSelectedDrawable = nullptr;
        mSelectedActor = nullptr;
    }
}

/**
 * Handle a left double-click event
 * @param event Mouse event
 */
void ViewEdit::OnLeftDoubleClick(wxMouseEvent& event)
{
    auto picture = GetPicture();
    if (picture == nullptr)
        return;
    
    // Convert mouse coordinates to view coordinates
    auto point = CalcUnscrolledPosition(event.GetPosition());
    
    // Check if clicked on a machine
    if (picture->GetMachine1()->HitTest(point))
    {
        // Create and display properties dialog for machine 1
        MachinePropertiesDialog dlg(this, picture->GetMachine1()->GetStartFrame(), 
                                   picture->GetMachine1()->GetScale());
        if (dlg.ShowModal() == wxID_OK)
        {
            picture->GetMachine1()->SetStartFrame(dlg.GetStartFrame());
            picture->GetMachine1()->SetScale(dlg.GetScale());
            Refresh();
        }
        return;
    }
    else if (picture->GetMachine2()->HitTest(point))
    {
        // Create and display properties dialog for machine 2
        MachinePropertiesDialog dlg(this, picture->GetMachine2()->GetStartFrame(), 
                                   picture->GetMachine2()->GetScale());
        if (dlg.ShowModal() == wxID_OK)
        {
            picture->GetMachine2()->SetStartFrame(dlg.GetStartFrame());
            picture->GetMachine2()->SetScale(dlg.GetScale());
            Refresh();
        }
        return;
    }
    
    // Not a machine, pass to other handlers
    event.Skip();
}


/**
 * Handle an Edit>Move menu option
 * @param event The menu event
 */
void ViewEdit::OnEditMove(wxCommandEvent& event)
{
    mMode = Mode::Move;
}

/**
 * Handle an Edit>Rotate menu option
 * @param event The menu event
 */
void ViewEdit::OnEditRotate(wxCommandEvent& event)
{
    mMode = Mode::Rotate;
}

/**
 * Advance the user interface for Edit>Move
 * @param event The event we update
 */
void ViewEdit::OnUpdateEditMove(wxUpdateUIEvent& event)
{
    event.Check(mMode == Mode::Move);
}

/**
 * Advance the user interface for Edit>Rotate
 * @param event The event we update
 */
void ViewEdit::OnUpdateEditRotate(wxUpdateUIEvent& event)
{
    event.Check(mMode == Mode::Rotate);
}
