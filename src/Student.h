#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include "libs/Vector.h"
#include"Course.h"
#include"Semester.h"

using std::string;

class User;
class Class;
class Course;
struct scorePerCourse
{
  Course *crs;
  float overallGPA,midtermGMark,finalMark,otherMark;
};
struct scorePerSemester
{
  Semester *sms;
  float gpa;
};
class Student
{
public:
  int student_id;
  Vector<scorePerCourse*> gpa_courses;
  Vector<scorePerSemester*> sms_courses;
  float overallGPA;
  string firstName, lastName, gender, dateOfBirth, socialID;
  User *pUser;
  Class *pClass;
  Vector<Course *> pEnrolledCourses;
  int numberOfEnrolledCourse;
  static void createStudent();
  static void showStudent();
};

#endif
