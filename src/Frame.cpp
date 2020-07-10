#include "Frame.h"

Frame::Frame(wxString title, wxSize frameSize): wxFrame(nullptr, 
                                                 wxID_ANY,
                                                 title,
                                                 wxDefaultPosition,
                                                 frameSize)
{
    panel = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);

    prompt = new wxStaticText(panel, wxID_ANY, wxT("Number of courses:"));
    numOfCourses = new wxTextCtrl(panel, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    mainButton = new wxButton(panel, wxID_ANY, wxT("Submit"));

    panel->FitInside();
    panel->SetScrollRate(0, 10);

    layout();

    mainButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        fieldMaker();
    });
    numOfCourses->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent&) {
        fieldMaker();
    });

    Show();
}

void Frame::layout()
{
    gridSizer = new wxGridSizer(0, 1, 0, 0);
    flexSizer = new wxFlexGridSizer(3, 1, 15, 0);
    boxSizer  = new wxBoxSizer(wxHORIZONTAL);

    boxSizer->Add(prompt, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    boxSizer->Add(numOfCourses, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    boxSizer->Add(mainButton, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);

    flexSizer->Add(boxSizer, 1, wxALIGN_CENTER_HORIZONTAL, 0);
    gridSizer->Add(flexSizer, 1, wxALIGN_CENTER_HORIZONTAL | wxTOP, 30);

    panel->SetSizer(gridSizer);
}

void Frame::fieldMaker()
{
    if (size != 0 && !flag)
    {
        for (int i = 0; i < size; i++)
        {
            field1[i]->Destroy();
            field2[i]->Destroy();
            vbox->Remove(hbox[i]);
        }
        credit->Destroy();
        grade->Destroy();
        calcButton->Destroy();
        result->Destroy();
        flexSizer->Remove(vbox);

        delete [] field1;
        delete [] field2;

        flag = false;
    }

    if (numOfCourses->GetLineText(0) == "")
    {
        size = 0;
        return;
    }

    size = std::stoi((std::string)numOfCourses->GetLineText(0));
    if (size == 0) return;

    hbox = new wxBoxSizer *[size + 1];
    vbox = new wxBoxSizer(wxVERTICAL);
    
    field1 = new wxTextCtrl *[size];
    field2 = new wxTextCtrl *[size];

    credit = new wxStaticText(panel, wxID_ANY, wxT("Number of credits"),
                              wxDefaultPosition, {170, 30}, wxALIGN_CENTRE_HORIZONTAL);
    grade  = new wxStaticText(panel, wxID_ANY, wxT("Grade earned"), wxDefaultPosition,
                              {160, 30}, wxALIGN_CENTRE_HORIZONTAL);

    hbox[0] = new wxBoxSizer(wxHORIZONTAL);
    hbox[0]->Add(credit, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    hbox[0]->Add(grade,  0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    
    vbox->Add(hbox[0], 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);

    for (int i = 0; i < size; i++)
    {
        field1[i] = new wxTextCtrl(panel, wxID_ANY, wxT(""), wxDefaultPosition, {170, 30},
                                   wxALIGN_CENTRE_HORIZONTAL | wxTE_PROCESS_ENTER);
        field2[i] = new wxTextCtrl(panel, wxID_ANY, wxT(""), wxDefaultPosition, {170, 30},
                                   wxALIGN_CENTRE_HORIZONTAL | wxTE_PROCESS_ENTER);

        hbox[i + 1] = new wxBoxSizer(wxHORIZONTAL);
        hbox[i + 1]->Add(field1[i], 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
        hbox[i + 1]->Add(field2[i], 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

        vbox->Add(hbox[i + 1], 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
        field1[i]->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent&) {
            result->SetLabelText(calculate());
        });
        field2[i]->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent&) {
            result->SetLabelText(calculate());
        });
    }

    calcButton = new wxButton(panel, wxID_ANY, wxT("Calculate"));
    vbox->Add(calcButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

    result = new wxStaticText(panel, wxID_ANY, wxT(""), wxDefaultPosition,
                              {300, 30}, wxALIGN_CENTRE_HORIZONTAL);
    result->SetFont(wxFont(15, wxDEFAULT, wxNORMAL, wxNORMAL, 0));
    vbox->Add(result, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

    calcButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        result->SetLabelText(calculate());
    });

    flexSizer->Add(vbox, 1, wxALIGN_CENTER_HORIZONTAL, 0);
    gridSizer->Layout();
    panel->FitInside();

    flag = false;
}

std::string Frame::calculate()
{
    try
    {
        gradeList = new std::string [size];
        creditList = new int [size];

        for (int i = 0; i < size; i++)
        {
            if (field1[i]->GetLineText(0) == "" || field2[i]->GetLineText(0) == "")
                return "Please fill up the fields above";

            creditList[i] = std::stoi((std::string)field1[i]->GetLineText(0));
            gradeList[i] = (std::string)field2[i]->GetLineText(0);
        }

        double val = Calc::cgpaCalculate(gradeList, creditList, size);
        if (val == -1) return "Invalid format";
        std::string cgpaValLong = std::to_string(val);
        std::string cgpaVal = "";
        for (int i = 0; i < 4; i++)
            cgpaVal += cgpaValLong[i];

        return "CGPA = " + cgpaVal;
    }
    catch (std::exception e)
    {
        return "Invalid format";
    }
}