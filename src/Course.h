#ifndef COURSE_H
#define COURSE_H

#include <iostream>
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
  string end_date;  // TODO: create dedicated struct for date
  Semester* pSemester;
  Vector<Student*> pStudents;
  int numberOfStudent;
  int maxNumberOfStudent;
  string timeOfCourse[2];

  static void createCourse();
  static bool checkConflict(Course* crs, Vector<Course*> allEnrolledCourse);
  static void showCourse();
  static void viewScoreboard();
  static void showStudentInCourse();

  static Course* loadFromStream(std::istream& f);
  void writeToStream(std::ostream& f);

private:
  static Course* findCourse(Semester* sms, string crsID);
};

#endif
