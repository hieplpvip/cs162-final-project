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
void SchoolYear::deleteSchoolYear()
{
    string delSchoolYear;
    cout << "Input school year to delete:";
    cin >> delSchoolYear;
    for (int i = 0; i < Global::all_school_year.size(); i++)
        if (Global::all_school_year[i]->name == delSchoolYear)
        {
            delete Global::all_school_year[i];
            for (int j = i; j < Global::all_school_year.size() - 1; j++)
                Global::all_school_year[j] = Global::all_school_year[j + 1];
            break;
        }
}