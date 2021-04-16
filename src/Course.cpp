#include "Global.h"
#include <iostream>
#include <string>
using namespace std;

void Course::createCourse() {
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
  cout << "What school year:";
  string schoolYear;
  cin >> schoolYear;
  cout << "What semester of school year " << schoolYear << ':';
  int semester;
  cin >> semester;
  int i = 0;
  while (Global::all_semester[i++]->pSchoolYear->name != schoolYear);
  Global::all_semester[i + semester - 1]->pCourses.push_back(crs);
  Global::all_course.push_back(crs);
}

bool Course::checkConflict(Course *crs, Vector<Course *> allEnrolledCourse) {
  for (int i = 0; i < allEnrolledCourse.size(); i++) {
    if (!(crs->course_id == allEnrolledCourse[i]->course_id)) {
      if (crs->timeOfCourse[0] == allEnrolledCourse[i]->timeOfCourse[0] || crs->timeOfCourse[0] == allEnrolledCourse[i]->timeOfCourse[1])
        return true;
      if (crs->timeOfCourse[1] == allEnrolledCourse[i]->timeOfCourse[0] || crs->timeOfCourse[1] == allEnrolledCourse[i]->timeOfCourse[1])
        return true;
    }
  }
  return false;
}

void Course::showCourse() {
  cout << "Here is a list of course:";
  for (int i = 0; i < Global::all_course.size(); i++) {
    cout << "Course ";
    cout << " #" << i << ':';
    cout << Global::all_course[i]->course_id << "-" << Global::all_course[i]->course_name << '-' << Global::all_course[i]->numberOfStudent << '/' << Global::all_course[i]->maxNumberOfStudent << " students";
    cout << "Lecturer:" << Global::all_course[i]->lecturer << '\n';
    cout << "Start date:" << Global::all_course[i]->start_date << '\n';
    cout << "End date:" << Global::all_course[i]->end_date << '\n';
    cout << "Time:" << '\n';
    cout << Global::all_course[i]->timeOfCourse[0] << '\n';
    cout << Global::all_course[i]->timeOfCourse[1];
  }
}
