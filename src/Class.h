#ifndef CLASS_H
#define CLASS_H

#include <string>
#include "libs/Vector.h"

using std::string;

class Student;

class Class {
public:
  string class_id;
  string class_name;
  Vector<Student*> pStudents;

  static Class* createClass();
};

#endif
