#include <config.h>

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

#include <string>
#include <array>
#include <format>

using namespace std::string_literals;

// FIXME: should be extracted from xrc file by wxrc utility.
#ifdef ADDITIONAL_TRANSLATIONS // from xrc
_("&Hello...");
_("&About...");
_("Hello, Hello, Hello!");
_("Show program information.");
_("Exit program.");
#endif

namespace example
{

FrameMain::FrameMain()
{
    // Load Layout from XRC
    wxXmlResource::Get()->LoadFrame(this, nullptr, "FrameMain");
    SetMinSize(FromDIP(wxSize {320, 240}));

    // Configure status
    const std::string welcome_msg = _("Welcome to {}!").ToStdString();
    const std::string app_name    = CFG_APP_NAME;
    SetStatusText(std::vformat(welcome_msg, std::make_format_args(app_name)));

    auto ver = CFG_APP_VERSION;
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
    wxStaticText *greetings_label = dynamic_cast<wxStaticText *>(FindWindowById(XRCID("LabelGreetings"), view_greetings));

    const std::string hello_msg = _("Hello {}!").ToStdString();
    greetings_label->SetLabelText(std::vformat(hello_msg, std::make_format_args(app_name)));
}

void
FrameMain::OnExit(wxCommandEvent &event)
{
    Close(true);
}

void
FrameMain::OnAbout(wxCommandEvent &event)
{
    const std::string about_info     = _("This is a {} program").ToStdString();
    const std::string about_title    = _("About {}").ToStdString();
    const std::string about_app_name = wxGetApp().GetAppName().ToStdString();

    wxMessageBox(
            std::vformat(about_info, std::make_format_args(CFG_APP_NAME)),
            std::vformat(about_title, std::make_format_args(about_app_name)),
            wxOK | wxICON_INFORMATION
    );
}

void
FrameMain::OnHello(wxCommandEvent &event)
{
    wxLogMessage(_("Hello world from wxWidgets!"));
}

} // namespace example
