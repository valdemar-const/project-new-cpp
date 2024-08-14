#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/app.h>
#endif

#include <wx/xrc/xmlres.h>

namespace example
{

class AppExample : public wxApp
{
  public:

    virtual bool OnInit();
};

} // namespace example

DECLARE_APP(example::AppExample);
