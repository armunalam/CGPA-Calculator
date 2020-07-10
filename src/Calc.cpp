#include "Calc.h"

double Calc::gradePoint(std::string g)
{
    if (g == "A" || g == "a") return 4;
    else if (g == "A-" || g == "a-") return 3.7;
    else if (g == "B+" || g == "b+") return 3.3;
    else if (g == "B"  || g == "b" ) return 3;
    else if (g == "B-" || g == "b-") return 2.7;
    else if (g == "C+" || g == "c+") return 2.3;
    else if (g == "C"  || g == "c" ) return 2;
    else if (g == "C-" || g == "c-") return 1.7;
    else if (g == "D+" || g == "d+") return 1.3;
    else if (g == "D"  || g == "d" ) return 1;
    else if (g == "F"  || g == "f" ) return 0;
    else if (g == "O"  || g == "o" ) return 0;
    else return -1;
}

double Calc::round(double num)
{
    float val = (int)(num * 100 + .5); 
    return (double)val / 100; 
}

double Calc::cgpaCalculate(std::string *grade, int *credit, int size)
{
    int totalCredit = 0;
    double cgpa, gp = 0, temp;

    for (int i = 0; i < size; i++)
    {
        totalCredit += credit[i];
        temp = gradePoint(grade[i]);
        if (temp == -1) return -1;
        gp += temp * credit[i];
    }

    cgpa = gp / totalCredit;
    delete [] credit;

    return round(cgpa);
}