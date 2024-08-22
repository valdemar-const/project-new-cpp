#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/app.h>
#endif

namespace example
{

class AppExample : public wxApp
{
  public:

    virtual bool OnInit();

  protected:

    void InitLanguageSupport();

  protected:

    wxLocale  *locale   = nullptr;
    wxLanguage language = wxLANGUAGE_DEFAULT;
};

} // namespace example

DECLARE_APP(example::AppExample);
