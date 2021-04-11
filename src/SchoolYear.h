#ifndef SCHOOLYEAR_H
#define SCHOOLYEAR_H

#include "libs/Vector.h"

class Semester;

class SchoolYear {
public:
  Vector<Semester*> pSemesters;

  static SchoolYear* createSchoolYear();
};

#endif
