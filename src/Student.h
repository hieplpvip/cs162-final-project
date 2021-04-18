#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include "libs/Vector.h"

using std::string;

class User;
class Class;
class Course;
class Semester;

struct scorePerCourse {
  Course *crs;
  float overallGPA, midtermGMark, finalMark, otherMark;
};

struct scorePerSemester {
  Semester *sms;
  float gpa;
};

class Student {
public:
  string student_id;
  Vector<scorePerCourse *> gpa_courses;
  Vector<scorePerSemester *> sms_courses;
  float overallGPA;
  string firstName, lastName, gender, dateOfBirth, socialID;
  User *pUser;
  Class *pClass;
  Vector<Course *> pEnrolledCourses;
  int numberOfEnrolledCourse;

  static void createStudent();
  static void showStudent();

  static Student *loadFromStream(std::istream &f);
  void writeToStream(std::ostream &f);
};

#endif
