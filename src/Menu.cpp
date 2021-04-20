#include "Menu.h"
#include "Global.h"

const FunctionRecord STAFF_MENU[] = {
    {"School Year", nullptr, true},
    {"New School Year", &SchoolYear::createSchoolYear, false},
    {"Edit School Year", &SchoolYear::editSchoolYear, false},
    {"View School Year", &SchoolYear::viewSchoolYear, false},

    {"Class", nullptr, true},
    {"New Class", &Class::createClass, false},
    {"Edit Class", &Class::editClass, false},
    {"View Class", &Class::viewClass, false},

    {"Semester", nullptr, true},
    {"New Semester", &Semester::createSemester, false},
    {"Edit Semester", &Semester::editSemester, false},
    {"View Semester", &Semester::viewSemester, false},

    {"Student", nullptr, true},
    {"New Student", &Student::createStudent, false},
    {"Edit Student", &Student::editStudent, false},
    {"View Student", &Student::viewStudent, false},

    {"Course", nullptr, true},
    {"New Course", &Course::createCourse, false},
    {"Edit Course", &Course::editCourse, false},
    {"View Course", &Course::viewCourse, false},
    {"Open/Close Course Registration", &Course::setCourseRegistration, false},

    {"User", nullptr, true},
    {"Create Staff User", &User::createStaffUser, false},
};

const FunctionRecord STUDENT_MENU[] = {
    {"Course", nullptr, true},
    {"View enrolled courses", &Course::viewEnrolledCourse, false},
    {"Enroll in a course", &Course::enrollCourse, false},
    {"Un-enroll from a course", &Course::unEnrollCourse, false},
    {"View score", &Course::viewScore, false},
};

const int NUM_STAFF_MENU = (int)(sizeof(STAFF_MENU) / sizeof(FunctionRecord));
const int NUM_STUDENT_MENU = (int)(sizeof(STUDENT_MENU) / sizeof(FunctionRecord));
