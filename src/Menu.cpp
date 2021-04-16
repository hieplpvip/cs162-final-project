#include "Menu.h"
#include "Global.h"
#include"SchoolYear.h"

const FunctionRecord STAFF_MENU[] = {
  {"School Year", nullptr, true},
  {"New School Year", &SchoolYear::createSchoolYear, false},
  {"Edit School Year", &SchoolYear::editSchoolYear, false},
  {"List School Years", &SchoolYear::showSchoolYear, false},

  {"Class", nullptr, true},
  {"New Class", &Class::createClass, false},
  {"Edit Class", nullptr, false},
  {"List Classes", &Class::showClass, false},

  {"Semester", nullptr, true},
  {"New Semester", &Semester::createSemester, false},
  {"Edit Semester", nullptr, false},
  {"List Semesters", nullptr, false},

  {"Student", nullptr, true},
  {"New Student", &Student::createStudent, false},
  {"Edit Student", nullptr, false},
  {"List Students", nullptr, false},

  {"Course", nullptr, true},
  {"New Course", &Course::createCourse, false},
  {"Edit Course", nullptr, false},
  {"List Courses", &Course::showCourse, false},
};

const FunctionRecord STUDENT_MENU[] = {
  {"School Year", nullptr, true},
  {"List School Years", nullptr, false},

  {"Class", nullptr, true},
  {"List Classes", nullptr, false},

  {"Semester", nullptr, true},
  {"List Semesters", nullptr, false},

  {"Course", nullptr, true},
  {"List all courses", nullptr, false},
  {"List enrolled courses", nullptr, false},
  {"Enroll in a course", nullptr, false},
  {"Un-enroll from a course", nullptr, false},
};

const int NUM_STAFF_MENU = (int)(sizeof(STAFF_MENU) / sizeof(FunctionRecord));
const int NUM_STUDENT_MENU = (int)(sizeof(STUDENT_MENU) / sizeof(FunctionRecord));
