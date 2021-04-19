#ifndef SCHOOLYEAR_H
#define SCHOOLYEAR_H

#include <iostream>
#include <string>
#include "libs/Vector.h"

using std::string;

class Semester;

class SchoolYear {
public:
  static const int numberOfSemester = 3;

  Vector<Semester*> pSemesters;
  string school_year_id;
  string name;

  SchoolYear();
  SchoolYear(string id);

  string getID();

  static void createSchoolYear();
  static void showSchoolYear();
  static void editSchoolYear();

  void loadFromStream(std::istream& f);
  void writeToStream(std::ostream& f);
};

#endif
