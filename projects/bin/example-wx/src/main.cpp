#include <example/example.hpp>

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/xrc/xmlres.h>

#ifndef WIN32
#include <resources/images/wx.xpm>
#endif

#include <iostream>
#include <array>

class MyApp : public wxApp
{
  public:

    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
  public:

    MyFrame();

  private:

    void OnHello(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
};

IMPLEMENT_APP(MyApp);

bool
MyApp::OnInit()
{
    SetAppName("Example");

    // Load resources
    wxXmlResource::Get()->InitAllHandlers();
    wxXmlResource::Get()->LoadAllFiles("resources/ui");

    // Create Main wxFrame
    MyFrame *frame = new MyFrame();
    frame->SetTitle(GetAppName());
    frame->SetIcon(wxICON(aaaa));
    frame->Show(true);
    return true;
}

MyFrame::MyFrame()
{
    // Load Layout from XRC
    wxXmlResource::Get()->LoadFrame(this, nullptr, "MainFrame");
    SetMinSize(FromDIP(wxSize {320, 240}));

    // Configure status
    SetStatusText("Welcome to wxWidgets!");
    auto ver = example::version_string();
    SetStatusText(ver, 1);
    std::array<int, 2> sizes = {-1, GetStatusBar()->GetTextExtent(ver).GetWidth()};
    SetStatusWidths(2, sizes.data());

    // Bind menu items handlers
    wxMenuItem *menu_item_exit  = GetMenuBar()->FindItem(XRCID("MenuItemExit"));
    wxMenuItem *menu_item_hello = GetMenuBar()->FindItem(XRCID("MenuItemHello"));
    wxMenuItem *menu_item_about = GetMenuBar()->FindItem(XRCID("MenuItemAbout"));

    Bind(wxEVT_MENU, &MyFrame::OnHello, this, menu_item_hello->GetId());
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, menu_item_about->GetId());
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, menu_item_exit->GetId());

    // Configure greetings label message
    wxStaticText *greetings_label = dynamic_cast<wxStaticText *>(FindWindowById(XRCID("LabelGreetings"), this));
    greetings_label->SetLabelText("Hello wxWidgets!");
}

void
MyFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}

void
MyFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox("This is a wxWidgets Hello World example", "About " + wxGetApp().GetAppName(), wxOK | wxICON_INFORMATION);
}

void
MyFrame::OnHello(wxCommandEvent &event)
{
    wxLogMessage("Hello world from wxWidgets!");
}
