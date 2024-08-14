#include <AppExample.hpp>

IMPLEMENT_WX_THEME_SUPPORT;

int
main(int argc, char *argv[])
{
    wxApp::SetInstance(wxCreateApp());
    wxEntryStart(argc, argv);
    {
        wxTheApp->CallOnInit();
        wxTheApp->OnRun();
        wxTheApp->OnExit();
    }
    wxEntryCleanup();
}

#ifdef WIN32
#include <windows.h>

int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    return main(__argc, __argv);
}
#endif
