#include "Global.h"
#include <iostream>
using namespace std;

void Semester::createSemester() {
  Semester *semester = new Semester;
  semester->pSchoolYear = Global::all_school_year.back();
  Global::all_semester.push_back(semester);
}

void Semester::showSemester() {
  cout << "Input school year:";
  string schoolYear;
  cin >> schoolYear;
  int count = 1;
  for (int i = 0; i < Global::all_semester.size(); i++) {
    if (Global::all_semester[i]->pSchoolYear->name == schoolYear) {
      cout << "Semester " << count++ << "-Number of course:" << Global::all_semester[i]->numberOfCourse;
    }
  }
}
