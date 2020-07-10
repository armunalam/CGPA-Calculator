#include <wx/wx.h>
#include "Frame.h"

class Application: public wxApp
{
    bool OnInit() override
    {
        auto frame = new Frame(wxT("CGPA Calculator"), wxSize(550, 650));
        
        return true;
    }
};

wxIMPLEMENT_APP(Application);