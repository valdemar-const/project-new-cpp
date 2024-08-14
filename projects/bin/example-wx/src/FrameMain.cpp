#include <FrameMain.hpp>
#include <AppExample.hpp>

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/menu.h>
#include <wx/stattext.h>
#include <wx/msgdlg.h>
#endif

#include <wx/xrc/xmlres.h>

#include <example/example.hpp>

#include <array>

namespace example
{
FrameMain::FrameMain()
{
    // Load Layout from XRC
    wxXmlResource::Get()->LoadFrame(this, nullptr, "FrameMain");
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

    Bind(wxEVT_MENU, &FrameMain::OnHello, this, menu_item_hello->GetId());
    Bind(wxEVT_MENU, &FrameMain::OnAbout, this, menu_item_about->GetId());
    Bind(wxEVT_MENU, &FrameMain::OnExit, this, menu_item_exit->GetId());

    // Configure greetings label message
    wxPanel      *view_greetings  = wxXmlResource::Get()->LoadPanel(this, "PanelExampleGreetings");
    wxStaticText *greetings_label = dynamic_cast<wxStaticText *>(FindWindowById(XRCID("LabelGreetings"), this));
    greetings_label->SetLabelText("Hello wxWidgets!");
}

void
FrameMain::OnExit(wxCommandEvent &event)
{
    Close(true);
}

void
FrameMain::OnAbout(wxCommandEvent &event)
{
    wxMessageBox("This is a wxWidgets Hello World example", "About " + wxGetApp().GetAppName(), wxOK | wxICON_INFORMATION);
}

void
FrameMain::OnHello(wxCommandEvent &event)
{
    wxLogMessage("Hello world from wxWidgets!");
}

} // namespace example
