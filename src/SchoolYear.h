#ifndef SCHOOLYEAR_H
#define SCHOOLYEAR_H

#include <string>
#include "libs/Vector.h"

using std::string;

class Semester;

class SchoolYear {
public:
  Vector<Semester *> pSemesters;
  string name;
  static const int numberOfSemester = 3;
  static void createSchoolYear();
  static void showSchoolYear();
  static void editSchoolYear();
};

#endif
