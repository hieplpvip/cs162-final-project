#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include "libs/Vector.h"

using std::string;

class User;
class Class;
class Course;
class Semester;

struct CourseScore {
  double midtermMark, finalMark, otherMark, totalMark;
};

class Student {
public:
  string student_id, firstName, lastName, gender, dateOfBirth, socialID;
  User *pUser;
  Class *pClass;
  Vector<Course *> pEnrolledCourses;
  Vector<CourseScore> pCourseScores;

  Student();
  Student(string id);

  string getID();

  static Student *selectStudent(const Vector<Student *> &students, bool showonly = false);

  static void createStudent();
  static void createStudentFromScreen();
  static void createStudentFromCSV();

  static void viewStudent();
  static void viewScore();

  static void viewEnrolledCourse();
  static void enrollCourse();
  static void unEnrollCourse();
  static void viewSchedule();

  double calculateSemesterGPA(const string semester_id);
  double calculateTotalGPA();

  void loadFromStream(std::istream &f);
  void writeToStream(std::ostream &f);
};

#endif
