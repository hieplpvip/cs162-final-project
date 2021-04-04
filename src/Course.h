#ifndef COURSE_H
#define COURSE_H

#include <string>
using std::string;

#ifdef STUDENT_H
class Student;
#else
#include "Student.h"
#endif

#include "libs/Vector.h"

class Course {
public:
  string course_id;
  string course_name;
  string lecturer;
  string start_date;
  string end_date; // TODO: create dedicated struct for date
  Vector<Student*> students;
};

#endif
