#ifndef GUARD_grade_me_h
#define GUARD_grade_me_h

#include<vector>
#include "Student_info_me.h"

double grade(double, double, double);
double grade(double, double, const std::vector<double>&);
double grade(const Student_info&);

#endif
