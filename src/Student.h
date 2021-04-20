#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include "libs/Vector.h"

using std::string;

class User;
class Class;
class Course;
class Semester;

struct scorePerCourse {
  Course *crs;
  float midtermGMark, finalMark, otherMark, overallMark;
};

struct scorePerSemester {
  Semester *sms;
  float gpa;
};

class Student {
public:
  string student_id, firstName, lastName, gender, dateOfBirth, socialID;
  User *pUser;
  Class *pClass;
  Vector<Course *> pEnrolledCourses;

  float overallGPA;
  Vector<scorePerCourse *> gpa_courses;
  Vector<scorePerSemester *> sms_courses;

  Student();
  Student(string id);

  string getID();

  static void createStudent();
  static void editStudent();
  static void viewStudent();

  void loadFromStream(std::istream &f);
  void writeToStream(std::ostream &f);
};

#endif
