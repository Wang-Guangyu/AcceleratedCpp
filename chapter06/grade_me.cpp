#include<stdexcept>
#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<numeric>
#include<iterator>
#include "me.h"

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



//grade

//Calculate a student's grade form midterm and final exam grades and homework grade
double grade(double midterm, double final, double homework)
{
    return 0.2*midterm + 0.4*final + 0.4*homework;
}

// Calculate grade form midterm and final exam grades and vector of homework grades
double grade(double midterm, double final, const vector<double>& hw)
{
    if(hw.size()==0)
        throw domain_error("students has done no homework!");
    
    return grade(midterm, final, median(hw));
}

double grade(const Student_info& s)
{
	return grade(s.midterm, s.final, s.homework);
}

bool fgrade(const Student_info& s)
{
    return grade(s) < 60;
}

bool pgrade(const Student_info& s)
{
    return !fgrade(s);
}

//median

// compute the median of a `vector<double>'
// note that calling this function copies the entire argument `vector'
double median(vector<double> vec)
{
#ifdef _MSC_VER
	typedef std::vector<double>::size_type vec_sz;
#else
	typedef vector<double>::size_type vec_sz;
#endif

	vec_sz size = vec.size();
	if (size == 0)
		throw domain_error("median of an empty vector");

	sort(vec.begin(), vec.end());

	vec_sz mid = size/2;

	return size % 2 == 0 ? (vec[mid] + vec[mid-1]) / 2 : vec[mid];
}

//student_info

bool compare(const Student_info& x, const Student_info& y)
{
	return x.name < y.name;
}

istream& read(istream& is, Student_info& s)
{
	// read and store the student's name and midterm and final exam grades
	is >> s.name >> s.midterm >> s.final;

	read_hw(is, s.homework);  // read and store all the student's homework grades
	return is;
}

// read homework grades from an input stream into a `vector<double>'
istream& read_hw(istream& in, vector<double>& hw)
{
	if (in) {
		// get rid of previous contents
		hw.clear();

		// read homework grades
		double x;
		while (in >> x)
			hw.push_back(x);

		// clear the stream so that input will work for the next student
		in.clear();
	}
	return in;
}

//analysis

double grade_aux(const Student_info& s)
{
    try{
        return grade(s);
    } catch(domain_error){
        return grade(s.midterm, s.final, 0);
    }
}

double median_analysis(const vector<Student_info> & students)
{
    vector<double> grades;

    transform(students.begin(), students.end(), back_inserter(grades), grade_aux);
    return median(grades);
}

void write_analysis(ostream& out, const string& name, double analysis(const vector<Student_info>&), const vector<Student_info>& did, const vector<Student_info>& didnt)
{
    cout << name << ": median(did) = " << analysis(did) << ", median(didnt) = " << analysis(didnt) << endl;
}

double average(const vector<double>& v)
{
    return accumulate(v.begin(), v.end(), 0.0)/v.size();
}

double average_grade(const Student_info& s)
{
    return grade(s.midterm, s.final, average(s.homework));
}

double average_analysis(const vector<Student_info>& students)
{
    vector<double> grades;
    transform(students.begin(), students.end(), back_inserter(grades), average_grade);
    return median(grades);
}

// median of the nonzero elements of `s.homework', or `0' if no such elements exist
double optimistic_median(const Student_info& s)
{
    vector<double> nonzero;
    remove_copy(s.homework.begin(), s.homework.end(), back_inserter(nonzero), 0);

    if(nonzero.empty())
        return grade(s.midterm, s.final, 0);
    else
        return grade(s.midterm, s.final, median(nonzero));
}

double optimistic_median_analysis(const vector<Student_info>& students)
{
    vector<double> grades;

    transform(students.begin(), students.end(), back_inserter(grades), optimistic_median);
    return median(grades);
}

//grade check
bool did_all_hw(const Student_info& s)
{
	return ((find(s.homework.begin(), s.homework.end(), 0))
		 == s.homework.end());
}

//grade analysis
int main()
{
	// students who did and didn't do all their homework
	vector<Student_info> did, didnt;

	// read the student records and partition them
	Student_info student;
	while (read(cin, student)) {
		if (did_all_hw(student))
			did.push_back(student);
		else
			didnt.push_back(student);
	}

	// verify that the analyses will show us something
	if (did.empty()) {
		cout << "No student did all the homework!" << endl;
		return 1;
	}
	if (didnt.empty()) {
		cout << "Every student did all the homework!" << endl;
		return 1;
	}


	// do the analyses
	write_analysis(cout, "median", median_analysis, did, didnt);
	write_analysis(cout, "average", average_analysis, did, didnt);
	write_analysis(cout, "median of homework turned in",
	               optimistic_median_analysis, did, didnt);

	return 0;
}