#include "Course.h"
#include "Global.h"
#include "Semester.h"
#include <iostream>
#include "Student.h"
using namespace std;
void Course::createCourse()
{
    Course *crs = new Course;
    Global::all_course.push_back(crs);
    cout << "Input course ID:";
    cin >> crs->course_id;
    cout << "Input course name:";
    cin >> crs->course_name;
    cout << "Input name of the lecturer:";
    cin >> crs->lecturer;
    cout << "Input start date:";
    cin >> crs->start_date;
    cout << "Input end date:";
    cin >> crs->end_date;
    cout << "How many student:";
    cin >> crs->numberOfStudent;
    for (int i = 0; i < crs->numberOfStudent; i++)
    {
        Student::createStudent();
        crs->pStudents.push_back(Global::all_student.back());
    }
}
