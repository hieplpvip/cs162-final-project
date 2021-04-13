#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include "libs/Vector.h"

using std::string;

class User;
class Class;
class Course;

class Student {
public:
  int student_id;
  float gpa;
  User* pUser;
  Class* pClass;
  Vector<Course*> pEnrolledCourses;

  static void createStudent();
};

#endif
