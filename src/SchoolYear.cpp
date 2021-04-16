#include "Global.h"
#include <iostream>
using namespace std;

void SchoolYear::createSchoolYear() {
  SchoolYear *schYear = new SchoolYear;
  cout << "School year:";
  cin >> schYear->name;
  for (int i = 0; i < schYear->numberOfSemester; i++) {
    Semester::createSemester();
    Global::all_semester.back()->pSchoolYear = schYear;
  }
  Global::all_school_year.push_back(schYear);
}

void SchoolYear::showSchoolYear() {
  cout << "List of school year:\n";
  for (int i = 0; i < Global::all_school_year.size(); i++) {
    cout << Global::all_school_year[i]->name << '\n';
  }
}

void SchoolYear::editSchoolYear() {
  throw "Not implemented yet!";
}
