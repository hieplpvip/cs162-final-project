#ifndef SEMESTER_H
#define SEMESTER_H

#include <iostream>
#include "libs/Vector.h"

class SchoolYear;
class Course;

class Semester {
public:
  SchoolYear* pSchoolYear;
  Vector<Course*> pCourses;
  static void createSemester();
  static void showSemester();
  static void editSemester();
  int numberOfCourse;
  int ordinalOfSemester;

  static Semester* getSemester(string schYear, int sms);

  static Semester* loadFromStream(std::istream& f);
  void writeToStream(std::ostream& f);
};

#endif
