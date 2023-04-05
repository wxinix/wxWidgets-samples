// wxWidgets "Hello World" Program
// For compilers that support pre-compilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

/*
 * Practically every app should define a new class derived from wxApp.
 * By overriding wxApp's OnInit() virtual method the program can be
 * initialized, e.g. by creating a new main window.
 */
class MyApp : public wxApp
{
public:
  bool OnInit() override;
};

/*
 * The main window is created by deriving a class from wxFrame and giving
 * it a menu and a status bar in its constructor.
 *
 * Also, any class that wishes
 * to respond to an "event" (such as mouse clicks, messages from the menu,
 * or a button) must declare an event table using the macro below.
 *
 * Finally, reacting to such events is done via "event handlers" which are just
 * functions (or functors, including lambdas if you're using C++11) taking the
 * event parameter of the type corresponding to the event being handled,
 * e.g. wxCommandEvent for the events from simple controls such as buttons,
 * text fields and also menu items.
 *
 * In our example, we react to three menu items:
 * our custom "Hello", and the "Exit" and "About" items (any program should normally
 * implement the latter two).
 *
 * Notice that these handlers don't need to be virtual or public.
 */
class MyFrame : public wxFrame
{
public:
  MyFrame();
private:
  void OnHello(wxCommandEvent &event);
  void OnExit(wxCommandEvent &event);
  void OnAbout(wxCommandEvent &event);
};

/*
 * In order to be able to react to a menu command, it must be given a unique identifier
 * which can be defined as a const variable or an enum element.
 *
 * The latter is often used because typically many such constants will be needed.
 */
enum
{
  ID_Hello = 1
};

/*
 * there must be a "main" function. Under wxWidgets, main is implemented inside
 * the wxIMPLEMENT_APP() macro, which creates an application instance of the
 * specified class and starts running the GUI event loop.
 */
wxIMPLEMENT_APP(MyApp);

/*
 * wxApp::OnInit() is called upon startup and should be used to initialize the
 * program, maybe showing a "splash screen" and creating the main window (or several).
 *
 * Frames are created hidden by default, to allow the creation of child windows
 * before displaying them. We thus need to explicitly show them.
 *
 * Finally, we return true from this method to indicate successful initialization.
 */

bool MyApp::OnInit()
{
  auto *frame = new MyFrame();
  frame->Show(true);
  return true;
}

/*
 * In the constructor of the main window (or later on), we create a menu with
 * our menu items, as well as a status bar to be shown at the bottom of
 * the main window. Both have to be bound to the frame with respective calls.
 */
MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, "Hello World", wxPoint(50, 50), wxSize(450, 340))
{

  /*
   * Notice that we don't need to specify the labels for the standard menu
   * items wxID_ABOUT and wxID_EXIT — they will be given standard (even correctly translated)
   * labels and standard accelerators correct for the current platform, making
   * our program behaviour more native.
   *
   * For this reason, you should prefer reusing the standard ids
   * (see Stock Items) where possible.
   */
  auto *menuFile = new wxMenu;
  menuFile->Append(ID_Hello, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
  menuFile->AppendSeparator();
  menuFile->Append(wxID_EXIT); // didn't specify label.

  auto *menuHelp = new wxMenu;
  menuHelp->Append(wxID_ABOUT); // didn't specify label.

  auto *menuBar = new wxMenuBar;
  menuBar->Append(menuFile, "&File");
  menuBar->Append(menuHelp, "&Help");

  SetMenuBar(menuBar);

  CreateStatusBar();
  SetStatusText("Welcome to wxWidgets!");

  /*
   We also have to connect our event handlers to the events we want to handle in them.
   We do this by calling Bind() to send all the menu events (identified by wxEVT_MENU event type)
   with the specified ID to the given function. The parameters we pass to Bind() are

   1. The event type, e.g. wxEVT_MENU, wxEVT_BUTTON, wxEVT_SIZE, or one of many
      other events used by wxWidgets.
   2. A Pointer to the method to call, and the object to call it on. In this case,
      we just call our own function, and pass this pointer for the object itself.
      We could instead call the method of another object, or a non-member function — in fact,
      any object that can be called with a wxCommandEvent, can be used here.
   3. An optional identifier, allowing us to select just some events of wxEVT_MENU type,
      namely those from the menu item with the given ID, instead of handling all of them in
      the provided handler. This is mainly useful with menu items and rarely with
      other kinds of events.
   */
  Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
  Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
  Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);

  // Center();
}

void MyFrame::OnExit(wxCommandEvent &)
{
  Close(true);
}

void MyFrame::OnAbout(wxCommandEvent &)
{
  wxMessageBox("This is a wxWidgets' Hello world sample",
               "About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent &)
{
  wxLogMessage("Hello world from wxWidgets!");
}