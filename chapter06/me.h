#include<stdexcept>
#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<numeric>
#include<iterator>

using std::cout;
using std::cin;
using std::accumulate;
using std::domain_error;
using std::istream;
using std::ostream;
using std::string;
using std::vector;
using std::back_inserter;
using std::endl;
using std::remove_copy;
using std::transform;
using std::sort;
using std::find;

//struct
struct Student_info{
    std::string name;
    double midterm, final;
    std::vector<double> homework;
};

//grade
double grade(double midterm, double final, double homework);
double grade(double midterm, double final, const vector<double>& hw);
double grade(const Student_info& s);
bool fgrade(const Student_info& s);
bool pgrade(const Student_info& s);

//median
double median(vector<double> vec);

//student_info
bool compare(const Student_info&, const Student_info&);
std::istream& read(std::istream&, Student_info&);
std::istream& read_hw(std::istream&, std::vector<double>&);

//analysis.h
bool did_all_hw(const Student_info& s);
double average_analysis(const std::vector<Student_info>& students);
double median_analysis(const std::vector<Student_info>& students);
double optimistic_median_analysis(const std::vector<Student_info>& students);
void write_analysis(std::ostream& out, const std::string& name,
                    double analysis(const std::vector<Student_info>&),
                    const std::vector<Student_info>& did,
                    const std::vector<Student_info>& didnt);

double average(const vector<double>& v);
double average_grade(const Student_info& s);
double average_analysis(const vector<Student_info>& students);
double optimistic_median(const Student_info& s);
double optimistic_median_analysis(const vector<Student_info>& students);
bool did_all_hw(const Student_info& s);