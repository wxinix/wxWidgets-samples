/////////////////////////////////////////////////////////////////////////////
// Name:        sashtest.cpp
// Purpose:     Layout/sash sample
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// For compilers that support pre-compilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/mdi.h"
#include "wx/wx.h"
#endif

#include "wx/laywin.h"
#include "wx/toolbar.h"

#include "sashtest.h"

MyFrame *frame = nullptr;
wxList my_children;

wxIMPLEMENT_APP(MyApp);// NOLINT(*-pro-type-static-cast-downcast)

// For drawing lines in canvas
long xpos = -1;
long ypos = -1;

int winNumber = 1;

// Initialise this in OnInit, not statically
bool MyApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    // Create the main frame window. wxID_ANY is to let wxWidgets to assign the ID.
    frame = new MyFrame(nullptr, wxID_ANY, "Sash Demo", wxPoint(0, 0), wxSize(500, 400), wxDEFAULT_FRAME_STYLE | wxHSCROLL | wxVSCROLL);

    // Give it an icon (this is ignored in MDI mode: uses resources)
#ifdef __WXMSW__
    frame->SetIcon(wxIcon("sashtest_icn"));
#endif

    // Make a menubar
    auto *file_menu = new wxMenu;

    file_menu->Append(SASHTEST_NEW_WINDOW, "&New window");
    file_menu->Append(SASHTEST_TOGGLE_WINDOW, "&Toggle window");
    file_menu->Append(SASHTEST_QUIT, "&Exit");

    auto *help_menu = new wxMenu;
    help_menu->Append(SASHTEST_ABOUT, "&About");

    auto *menu_bar = new wxMenuBar;

    menu_bar->Append(file_menu, "&File");
    menu_bar->Append(help_menu, "&Help");

    // Associate the menu bar with the frame
    frame->SetMenuBar(menu_bar);

#if wxUSE_STATUSBAR
    frame->CreateStatusBar();
#endif// wxUSE_STATUSBAR

    frame->Show(true);
    return true;
}

// Define my frame constructor
MyFrame::MyFrame(wxWindow *parent, const wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, const long style) : wxMDIParentFrame(parent, id, title, pos, size, style)
{
    // Create some dummy layout windows
    // A window like a toolbar
    auto *win = new wxSashLayoutWindow(this, ID_WINDOW_TOP, wxDefaultPosition, wxSize(200, 30), wxNO_BORDER | wxSW_3D | wxCLIP_CHILDREN);

    win->SetDefaultSize(wxSize(1000, 30));
    win->SetOrientation(wxLAYOUT_HORIZONTAL);
    win->SetAlignment(wxLAYOUT_TOP);
    win->SetBackgroundColour(*wxRED);
    win->SetSashVisible(wxSASH_BOTTOM, true);

    m_topWindow = win;

    // A window like a statusbar
    win = new wxSashLayoutWindow(this, ID_WINDOW_BOTTOM, wxDefaultPosition, wxSize(200, 30), wxNO_BORDER | wxSW_3D | wxCLIP_CHILDREN);
    win->SetDefaultSize(wxSize(1000, 30));
    win->SetOrientation(wxLAYOUT_HORIZONTAL);
    win->SetAlignment(wxLAYOUT_BOTTOM);
    win->SetBackgroundColour(*wxBLUE);
    win->SetSashVisible(wxSASH_TOP, true);

    m_bottomWindow = win;

    // A window to the left of the client window
    win = new wxSashLayoutWindow(this, ID_WINDOW_LEFT1, wxDefaultPosition, wxSize(200, 30), wxNO_BORDER | wxSW_3D | wxCLIP_CHILDREN);
    win->SetDefaultSize(wxSize(120, 1000));
    win->SetOrientation(wxLAYOUT_VERTICAL);
    win->SetAlignment(wxLAYOUT_LEFT);
    win->SetBackgroundColour(*wxGREEN);
    win->SetSashVisible(wxSASH_RIGHT, true);
    win->SetExtraBorderSize(10);

    auto *textWindow = new wxTextCtrl(win, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxSUNKEN_BORDER);//wxTE_MULTILINE|wxNO_BORDER);
    textWindow->SetValue("A help window");
    m_leftWindow1 = win;

    // Another window to the left of the client window
    win = new wxSashLayoutWindow(this, ID_WINDOW_LEFT2, wxDefaultPosition, wxSize(200, 30), wxNO_BORDER | wxSW_3D | wxCLIP_CHILDREN);
    win->SetDefaultSize(wxSize(120, 1000));
    win->SetOrientation(wxLAYOUT_VERTICAL);
    win->SetAlignment(wxLAYOUT_LEFT);
    win->SetBackgroundColour(wxColour(0, 255, 255));
    win->SetSashVisible(wxSASH_RIGHT, true);

    m_leftWindow2 = win;

    Bind(wxEVT_SIZE, &MyFrame::OnMyFrameSize, this);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, SASHTEST_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnNewWindow, this, SASHTEST_NEW_WINDOW);
    Bind(wxEVT_MENU, &MyFrame::OnQuit, this, SASHTEST_QUIT);
    Bind(wxEVT_MENU, &MyFrame::OnToggleWindow, this, SASHTEST_TOGGLE_WINDOW);
    Bind(wxEVT_SASH_DRAGGED, &MyFrame::OnSashDrag, this, ID_WINDOW_TOP, ID_WINDOW_BOTTOM);
}

void MyFrame::OnQuit(wxCommandEvent &WXUNUSED(event))
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent &WXUNUSED(event))// NOLINT(*-convert-member-functions-to-static)
{
    (void)wxMessageBox("wxWidgets 2.0 Sash Demo\nAuthor: Julian Smart (c) 1998", "About Sash Demo");
}

void MyFrame::OnToggleWindow(wxCommandEvent &WXUNUSED(event))
{
    if (m_leftWindow1->IsShown()) {
        m_leftWindow1->Show(false);
    } else {
        m_leftWindow1->Show(true);
    }
#if wxUSE_MDI_ARCHITECTURE
    wxLayoutAlgorithm layout;
    layout.LayoutMDIFrame(this);
#endif// wxUSE_MDI_ARCHITECTURE
}

void MyFrame::OnSashDrag(wxSashEvent &event)
{
    if (event.GetDragStatus() == wxSASH_STATUS_OUT_OF_RANGE)
        return;

    switch (event.GetId()) {
        case ID_WINDOW_TOP: {
            m_topWindow->SetDefaultSize(wxSize(1000, event.GetDragRect().height));
            break;
        }
        case ID_WINDOW_LEFT1: {
            m_leftWindow1->SetDefaultSize(wxSize(event.GetDragRect().width, 1000));
            break;
        }
        case ID_WINDOW_LEFT2: {
            m_leftWindow2->SetDefaultSize(wxSize(event.GetDragRect().width, 1000));
            break;
        }
        case ID_WINDOW_BOTTOM: {
            m_bottomWindow->SetDefaultSize(wxSize(1000, event.GetDragRect().height));
            break;
        }
    }

#if wxUSE_MDI_ARCHITECTURE
    wxLayoutAlgorithm layout;
    layout.LayoutMDIFrame(this);
#endif// wxUSE_MDI_ARCHITECTURE

    // Leaves bits of itself behind sometimes
    GetClientWindow()->Refresh();
}

void MyFrame::OnNewWindow(wxCommandEvent &WXUNUSED(event))// NOLINT(*-convert-member-functions-to-static)
{
    // Make another frame, containing a canvas
    auto *subframe = new MyChild(frame, "Canvas Frame", wxPoint(10, 10), wxSize(300, 300));

    subframe->SetTitle(wxString::Format("Canvas Frame %d", winNumber));
    winNumber++;

    // Give it an icon (this is ignored in MDI mode: uses resources)
#ifdef __WXMSW__
    subframe->SetIcon(wxIcon("sashtest_icn"));
#endif

#if wxUSE_STATUSBAR
    // Give it a status line
    subframe->CreateStatusBar();
#endif// wxUSE_STATUSBAR

    // Make a menubar
    auto *file_menu = new wxMenu;

    file_menu->Append(SASHTEST_NEW_WINDOW, "&New window");
    file_menu->Append(SASHTEST_CHILD_QUIT, "&Close child");
    file_menu->Append(SASHTEST_QUIT, "&Exit");

    auto *option_menu = new wxMenu;

    // Dummy option
    option_menu->Append(SASHTEST_REFRESH, "&Refresh picture");

    auto *help_menu = new wxMenu;
    help_menu->Append(SASHTEST_ABOUT, "&About");

    auto *menu_bar = new wxMenuBar;
    menu_bar->Append(file_menu, "&File");
    menu_bar->Append(option_menu, "&Options");
    menu_bar->Append(help_menu, "&Help");

    // Associate the menu bar with the frame
    subframe->SetMenuBar(menu_bar);

    int width, height;
    subframe->GetClientSize(&width, &height);
    auto *canvas = new MyCanvas(subframe, wxPoint(0, 0), wxSize(width, height));
    canvas->SetCursor(wxCursor(wxCURSOR_PENCIL));
    subframe->SetCanvas(canvas);
    // Give it scrollbars
    canvas->SetScrollbars(20, 20, 50, 50);

    subframe->Show(true);
}

// Define a constructor for my m_canvas
MyCanvas::MyCanvas(wxWindow *parent, const wxPoint &pos, const wxSize &size) : wxScrolledWindow(parent, wxID_ANY, pos, size, wxSUNKEN_BORDER)
{
    SetBackgroundColour(*wxWHITE);

    Bind(wxEVT_LEFT_DOWN, &MyCanvas::OnMouseEvent, this);
    Bind(wxEVT_LEFT_UP, &MyCanvas::OnMouseEvent, this);
    Bind(wxEVT_LEFT_DCLICK, &MyCanvas::OnMouseEvent, this);
    Bind(wxEVT_RIGHT_DOWN, &MyCanvas::OnMouseEvent, this);
    Bind(wxEVT_RIGHT_UP, &MyCanvas::OnMouseEvent, this);
    Bind(wxEVT_RIGHT_DCLICK, &MyCanvas::OnMouseEvent, this);
    Bind(wxEVT_MIDDLE_DOWN, &MyCanvas::OnMouseEvent, this);
    Bind(wxEVT_MIDDLE_UP, &MyCanvas::OnMouseEvent, this);
    Bind(wxEVT_MIDDLE_DCLICK, &MyCanvas::OnMouseEvent, this);
    Bind(wxEVT_MOTION, &MyCanvas::OnMouseEvent, this);
    Bind(wxEVT_ENTER_WINDOW, &MyCanvas::OnMouseEvent, this);
    Bind(wxEVT_LEAVE_WINDOW, &MyCanvas::OnMouseEvent, this);
}

// Define the repainting behaviour
void MyCanvas::OnDraw(wxDC &dc)
{
    dc.SetFont(*wxSWISS_FONT);
    dc.SetPen(*wxGREEN_PEN);
    dc.DrawLine(0, 0, 200, 200);
    dc.DrawLine(200, 0, 0, 200);

    dc.SetBrush(*wxCYAN_BRUSH);
    dc.SetPen(*wxRED_PEN);
    dc.DrawRectangle(100, 100, 100, 50);
    dc.DrawRoundedRectangle(150, 150, 100, 50, 20);

    dc.DrawEllipse(250, 250, 100, 50);
#if wxUSE_SPLINES
    dc.DrawSpline(50, 200, 50, 100, 200, 10);
#endif// wxUSE_SPLINES
    dc.DrawLine(50, 230, 200, 230);
    dc.DrawText("This is a test string", 50, 230);

    wxPoint points[3];
    points[0].x = 200;
    points[0].y = 300;
    points[1].x = 100;
    points[1].y = 400;
    points[2].x = 300;
    points[2].y = 400;

    dc.DrawPolygon(3, points);
}

// This implements a tiny doodling program! Drag the mouse using
// the left button.
void MyCanvas::OnMouseEvent(wxMouseEvent &event)
{
    wxClientDC dc(this);
    PrepareDC(dc);

    wxPoint pt(event.GetLogicalPosition(dc));

    if (xpos > -1 && ypos > -1 && event.Dragging()) {
        dc.SetPen(*wxBLACK_PEN);
        dc.DrawLine(xpos, ypos, pt.x, pt.y);
    }
    xpos = pt.x;
    ypos = pt.y;
}

void MyFrame::OnMyFrameSize([[maybe_unused]] wxSizeEvent &event WXUNUSED(event))
{
#if wxUSE_MDI_ARCHITECTURE
    wxLayoutAlgorithm layout;
    layout.LayoutMDIFrame(this);
#endif// wxUSE_MDI_ARCHITECTURE
}

// Note that SASHTEST_NEW_WINDOW and SASHTEST_ABOUT commands get passed
// to the parent window for processing, so no need to
// duplicate event handlers here.
MyChild::MyChild(wxMDIParentFrame *parent, const wxString &title, const wxPoint &pos, const wxSize &size) : wxMDIChildFrame(parent, wxID_ANY, title, pos, size)
{
    my_children.Append(this);
    Bind(wxEVT_MENU, &MyChild::OnQuit, this, SASHTEST_CHILD_QUIT);
}

MyChild::~MyChild()
{
    my_children.DeleteObject(this);
}

void MyChild::OnQuit(wxCommandEvent &WXUNUSED(event))
{
    Close(true);
}

[[maybe_unused]] void MyChild::OnMyChildActivate(wxActivateEvent &event) const
{
    if (event.GetActive() && m_canvas)
        m_canvas->SetFocus();
}
