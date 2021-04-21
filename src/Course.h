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
  string course_code;
  string course_name;
  string lecturer;
  string start_date;
  string end_date;  // TODO: create dedicated struct for date
  Semester* pSemester;
  Vector<Student*> pStudents;
  int maxNumberOfStudents;
  string schedule[2];

  Course();
  Course(string id);

  string getID();

  static Course* selectCourse(Vector<Course*> courses);

  static void createCourse();
  static void editCourse();
  static void viewCourse();

  static void setCourseRegistration();

  static void viewEnrolledCourse();
  static void enrollCourse();
  static void unEnrollCourse();
  static void viewScore();

  static void viewScoreboard();
  static void viewStudentInCourse();

  void loadFromStream(std::istream& f);
  void writeToStream(std::ostream& f);

private:
  static Course* findCourse(Semester* sms, string crsID);
};

#endif
