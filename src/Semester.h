#ifndef SEMESTER_H
#define SEMESTER_H

#include "Course.h"
#include "libs/Vector.h"

class Semester {
public:
  Vector<Course*> courses;
};

#endif
