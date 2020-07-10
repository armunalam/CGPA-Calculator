#pragma once
#include <wx/wx.h>
#include <iostream>
#include "Calc.h"

class Frame: public wxFrame
{
    int size = 0;

    wxScrolledWindow *panel;
    wxStaticText *prompt, *credit, *grade, *result;
    wxTextCtrl *numOfCourses, **field1, **field2;
    wxButton *mainButton, *calcButton;

    wxGridSizer *gridSizer;
    wxFlexGridSizer *flexSizer;
    wxBoxSizer *boxSizer, **hbox, *vbox;

    int *creditList;
    std::string *gradeList;

    bool flag = false;


public:
    Frame(wxString title, wxSize frameSize);
    void layout();
    void fieldMaker();
    std::string calculate();
};