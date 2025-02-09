
#include "wx/toolbar.h"

// Define a new application
class MyApp : public wxApp
{
public:
    bool OnInit() wxOVERRIDE;
};

class MyCanvas : public wxScrolledWindow
{
public:
    MyCanvas(wxWindow *parent, const wxPoint &pos, const wxSize &size);

private:
    void OnDraw(wxDC &dc) wxOVERRIDE;
    void OnMouseEvent(wxMouseEvent &event);
};

// Define a new frame
class MyFrame : public wxMDIParentFrame
{
public:
    MyFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style);

protected:
    wxSashLayoutWindow *m_topWindow;
    wxSashLayoutWindow *m_leftWindow1;
    wxSashLayoutWindow *m_leftWindow2;
    wxSashLayoutWindow *m_bottomWindow;

private:
    void OnMyFrameSize([[maybe_unused]] wxSizeEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnNewWindow(wxCommandEvent &event);
    void OnQuit(wxCommandEvent &event);
    void OnToggleWindow(wxCommandEvent &event);
    void OnSashDrag(wxSashEvent &event);
};

class MyChild : public wxMDIChildFrame
{
public:
    MyChild(wxMDIParentFrame *parent, const wxString &title, const wxPoint &pos, const wxSize &size);
    ~MyChild() override;

    [[nodiscard]] MyCanvas *GetCanvas() const { return m_canvas; }
    void SetCanvas(MyCanvas *canvas) { m_canvas = canvas; }

private:
    [[maybe_unused]] void OnMyChildActivate(wxActivateEvent &event) const;
    void OnQuit(wxCommandEvent &event);

    MyCanvas *m_canvas{nullptr};
};

#define SASHTEST_QUIT wxID_EXIT
#define SASHTEST_NEW_WINDOW 2
#define SASHTEST_REFRESH 3
#define SASHTEST_CHILD_QUIT 4
#define SASHTEST_ABOUT wxID_ABOUT
#define SASHTEST_TOGGLE_WINDOW 6

#define ID_WINDOW_TOP 100
#define ID_WINDOW_LEFT1 101
#define ID_WINDOW_LEFT2 102
#define ID_WINDOW_BOTTOM 103
