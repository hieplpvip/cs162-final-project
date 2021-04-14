#include "SchoolYear.h"
#include "Global.h"
#include "Semester.h"
#include <iostream>
#include "Semester.h"
using namespace std;
void SchoolYear::createSchoolYear()
{
    SchoolYear *schYear = new SchoolYear;
    cout << "School year:";
    cin >> schYear->name;
    Global::all_school_year.push_back(schYear);
    for (int i = 0; i < 3; i++)
    {
        Semester::createSemester();
        schYear->pSemesters.push_back(Global::all_semester.back());
    }
}
void SchoolYear::showSchoolYear()
{
    cout << "List of sschool year:\n";
    for (int i = 0; i < Global::all_school_year.size();i++)
        cout << Global::all_school_year[i]->name << '\n';
}
void SchoolYear::editSchoolYear()
{
    throw "Not implemented yet!";
}