#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/frame.h>
#endif

namespace example
{

class FrameMain : public wxFrame
{
  public:

    FrameMain();

  private:

    void OnHello(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
};

} // namespace example
