#ifndef COURSE_H
#define COURSE_H

#include <string>
#include "libs/Vector.h"

using std::string;

class Student;
class Semester;

class Course {
public:
  string course_id;
  string course_name;
  string lecturer;
  string start_date;
  string end_date; // TODO: create dedicated struct for date
  Semester* pSemester;
  Vector<Student*> pStudents;

  static void createCourse();
};

#endif
