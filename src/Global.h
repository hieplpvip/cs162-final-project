#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <string>
#include <cassert>

#include "libs/Vector.h"
#include "Class.h"
#include "Course.h"
#include "SchoolYear.h"
#include "Semester.h"
#include "Student.h"
#include "User.h"
#include "Utils.h"

namespace Global {
  extern Vector<SchoolYear*> all_school_year;
  extern Vector<Semester*> all_semester;
  extern Vector<Course*> all_course;
  extern Vector<Student*> all_student;
  extern Vector<Class*> all_class;
  extern Vector<User**> all_user;
};

#endif
