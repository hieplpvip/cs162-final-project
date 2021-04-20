#ifndef SEMESTER_H
#define SEMESTER_H

#include <iostream>
#include "libs/Vector.h"

class SchoolYear;
class Course;

class Semester {
public:
  string semester_id;
  SchoolYear* pSchoolYear;
  Vector<Course*> pCourses;

  int ordinalOfSemester;

  static void createSemester();
  static void editSemester();
  static void viewSemester();

  Semester();
  Semester(string id);

  string getID();

  static Semester* getSemester(string schYear, int sms);

  void loadFromStream(std::istream& f);
  void writeToStream(std::ostream& f);
};

#endif
