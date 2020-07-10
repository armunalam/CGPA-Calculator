#pragma once
#include <iostream>

namespace Calc
{
    double gradePoint(std::string g);
    double round(double num);
    double cgpaCalculate(std::string *grade, int *credit, int size);
};