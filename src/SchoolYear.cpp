#include "SchoolYear.h"
#include "Global.h"
#include"Semester.h"
#include<iostream>
using namespace std;
void SchoolYear::createSchoolYear() {
  SchoolYear *sch;
  cout<<"Input school year:";
  cin>>sch->schoolYear;
  //More implement for Semester

  //Add to global data
  Global::all_school_year.push_back(sch);
}
