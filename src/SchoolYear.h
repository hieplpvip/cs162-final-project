#ifndef SCHOOLYEAR_H
#define SCHOOLYEAR_H

#include "Semester.h"
#include "libs/Vector.h"

class SchoolYear {
public:
  Vector<Semester*> semesters;
};

#endif
