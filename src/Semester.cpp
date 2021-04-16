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
Semester *Semester::getSemester(string schYear, int sms)
{
    int i = 0;
    SchoolYear *pSchYear;
    for (i = 0; i < Global::all_school_year.size(); i++)
        if (Global::all_school_year[i]->name == schYear)
        {
            pSchYear = Global::all_school_year[i];
            break;
        }
    for (i = 0; i < Global::all_school_year[i]->numberOfSemester; i++)
        if (pSchYear->pSemesters[i]->ordinalOfSemester == sms)
            return Global::all_semester[i];
}
