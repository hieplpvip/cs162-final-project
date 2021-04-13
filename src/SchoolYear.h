#ifndef SCHOOLYEAR_H
#define SCHOOLYEAR_H
#include<iostream>
#include "libs/Vector.h"
using namespace std;
class Semester;

class SchoolYear {
public:
  Vector<Semester*> pSemesters;
  string name;
  static void createSchoolYear();
  static void deleteSchoolYear();
  static void editSchoolYear();
};

#endif
