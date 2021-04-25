#ifndef SEMESTER_H
#define SEMESTER_H

#include <iostream>
#include "libs/Vector.h"

class SchoolYear;
class Course;

class Semester {
public:
  static const string ORD2STR[];

  string semester_id;
  int semester_ordinal;
  SchoolYear* pSchoolYear;
  Vector<Course*> pCourses;

  Semester();
  Semester(string id);

  string getID();

  static Semester* selectSemester(const Vector<Semester*>& semesters, bool showonly = false);

  static void createSemester();
  static void viewSemester();

  void loadFromStream(std::istream& f);
  void writeToStream(std::ostream& f);
};

#endif
