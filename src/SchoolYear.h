#ifndef SCHOOLYEAR_H
#define SCHOOLYEAR_H

#include "libs/Vector.h"

class Semester;

class SchoolYear {
public:
  Vector<Semester*> pSemesters;
  string schoolYear;
  static void createSchoolYear();
};

#endif
