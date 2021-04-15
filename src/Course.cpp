#include "Course.h"
#include "Global.h"
#include "Semester.h"
#include <iostream>
#include "Student.h"
#include <string>
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
    cout << "Max student in course:";
    cin >> crs->maxNumberOfStudent;
    cout << "Time of the course";
    cout << "\nFirst time in week";
    getline(cin, crs->timeOfCourse[0]);
    cout << "Second time in week";
    getline(cin, crs->timeOfCourse[1]);
    for (int i = 0; i < crs->numberOfStudent; i++)
    {
        Student::createStudent();
        crs->pStudents.push_back(Global::all_student.back());
    }
}
bool Course::checkConflict(Course *crs,Vector<Course*> allEnrolledCourse)
{
    for (int i = 0; i < allEnrolledCourse.size(); i++)
        if (!(crs->course_id == allEnrolledCourse[i]->course_id))
        {
            if (crs->timeOfCourse[0] == allEnrolledCourse[i]->timeOfCourse[0] || crs->timeOfCourse[0] == allEnrolledCourse[i]->timeOfCourse[1])
                return true;
            if (crs->timeOfCourse[1] == allEnrolledCourse[i]->timeOfCourse[0] || crs->timeOfCourse[1] == allEnrolledCourse[i]->timeOfCourse[1])
                return true;
        }
    return false;
}
