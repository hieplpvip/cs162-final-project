#ifndef CLASS_H
#define CLASS_H

#include <string>
using std::string;

#include "Student.h"
#include "libs/Vector.h"

class Class {
public:
  string class_id;
  Vector<Student*> students;
};

#endif
