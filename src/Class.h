#ifndef CLASS_H
#define CLASS_H

#include <iostream>
#include <string>
#include "libs/Vector.h"

using std::string;

class Student;

class Class {
public:
  string class_id;
  string class_name;
  Vector<Student*> pStudents;

  Class();
  Class(string id);

  string getID();

  static Class* selectClass(const Vector<Class*>& classes);

  static void createClass();
  static void editClass();
  static void viewClass();

  static void showScoreboard();

  void loadFromStream(std::istream& f);
  void writeToStream(std::ostream& f);

private:
  static Class* findClass(string classID);
};

#endif
