#include "Semester.h"
#include "Global.h"
#include "Course.h"
#include <iostream>
using namespace std;
void Semester::createSemester()
{
    Semester *semester = new Semester;
    semester->pSchoolYear = Global::all_school_year.back();
    int numberOfCourse;
    cout << "How many number of course:";
    cin >> semester->numberOfCourse;
    for (int i = 0; i < semester->numberOfCourse; i++)
    {
        Course::createCourse();
        semester->pCourses.push_back(Global::all_course.back());
    }
}
