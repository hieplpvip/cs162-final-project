#ifndef STUDENT_H
#define STUDENT_H

#include <string>
using std::string;

#ifdef COURSE_H
class Course;
#else
#include "Course.h"
#endif

#include "libs/Vector.h"

class Student {
public:
  int student_id;
  float gpa;
  Vector<Course*> enrolled_courses;
};

#endif
