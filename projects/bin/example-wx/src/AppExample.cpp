#include <config.h>

#include <AppExample.hpp>
#include <FrameMain.hpp>

#ifndef WX_PRECOMP
#include <wx/intl.h>
#endif

#include <wx/xrc/xmlres.h>

#ifndef WIN32
#include <resources/images/wx.xpm>
#endif

#include <iostream>

IMPLEMENT_APP_NO_MAIN(example::AppExample);

namespace example
{

bool
AppExample::OnInit()
{
    SetAppName(CFG_APP_NAME);

    InitLanguageSupport();

    // Load resources
    wxXmlResource::Get()->InitAllHandlers();
    wxXmlResource::Get()->LoadAllFiles("resources/ui");

    // Create Main wxFrame
    FrameMain *frame = new FrameMain();
    frame->SetTitle(GetAppName());
    frame->SetIcon(wxICON(aaaa));
    frame->Show(true);

    return true;
}

void
AppExample::InitLanguageSupport()
{
    language = wxLANGUAGE_DEFAULT;

#if 0 // non default language
    // fake functions, use proper implementation
    if( userWantsAnotherLanguageThanDefault() )
        language = getUsersFavoriteLanguage();
#endif
    // load language if possible, fall back to english otherwise
    if (wxLocale::IsAvailable(language))
    {
        locale = new wxLocale(language);

#ifdef __WXGTK__
        // add locale search paths
        locale->AddCatalogLookupPathPrefix(wxT("/usr"));
        locale->AddCatalogLookupPathPrefix(wxT("/usr/local"));
        wxStandardPaths *paths  = (wxStandardPaths *)&wxStandardPaths::Get();
        wxString         prefix = paths->GetInstallPrefix();
        locale->AddCatalogLookupPathPrefix(prefix);
#endif
        locale->AddCatalogLookupPathPrefix("resources/i18n");
        locale->AddCatalog(CFG_APP_NAME);
        locale->AddCatalog("ru");

        if (!locale->IsOk())
        {
            std::cerr << "Error: Selected language is wrong." << std::endl;
            delete locale;
            locale   = new wxLocale(wxLANGUAGE_ENGLISH);
            language = wxLANGUAGE_ENGLISH;
        }
    }
    else
    {
        std::cout << "The selected language is not supported by your system."
                  << "Try installing support for this language." << std::endl;
        locale   = new wxLocale(wxLANGUAGE_ENGLISH);
        language = wxLANGUAGE_ENGLISH;
    }
}

} // namespace example
