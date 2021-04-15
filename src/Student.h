#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include "libs/Vector.h"

using std::string;

class User;
class Class;
class Course;

class Student
{
public:
  int student_id;
  string firstName, lastName, gender, dateOfBirth, socialID;
  User *pUser;
  Class *pClass;
  Vector<Course *> pEnrolledCourses;
  int numberOfEnrolledCourse;
  static void createStudent();
  static void showStudent();
};

#endif
