#include <config.h>

#include <AppExample.hpp>
#include <FrameMain.hpp>

#include <wx/xrc/xmlres.h>

#ifndef WIN32
#include <resources/images/wx.xpm>
#endif

IMPLEMENT_APP_NO_MAIN(example::AppExample);

namespace example
{

bool
AppExample::OnInit()
{
    SetAppName(CFG_APP_NAME);

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

} // namespace example
