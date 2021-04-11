#ifndef SEMESTER_H
#define SEMESTER_H

#include "libs/Vector.h"

class SchoolYear;
class Course;

class Semester {
public:
  SchoolYear* pSchoolYear;
  Vector<Course*> pCourses;

  static Semester* createSemester(const SchoolYear* &school_year);
};

#endif
