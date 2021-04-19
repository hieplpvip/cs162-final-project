#include "Global.h"
using namespace std;

Semester::Semester() {}
Semester::Semester(string id) : semester_id(id) {}

string Semester::getID() {
  return semester_id;
}

void Semester::createSemester() {
  Semester *semester = new Semester();
  semester->pSchoolYear = Global::all_school_year.back();
  Global::all_semester.push_back(semester);
}

void Semester::showSemester() {
  string schoolYear;
  cout << "Input school year:";
  cin >> schoolYear;
  int count = 1;
  for (int i = 0; i < Global::all_semester.size(); i++) {
    if (Global::all_semester[i]->pSchoolYear->name == schoolYear) {
      cout << "Semester " << count++ << ":\n";
      cout << "  Number of course:" << Global::all_semester[i]->pCourses.size() << '\n';
    }
  }
}

Semester *Semester::getSemester(string schYear, int sms) {
  int i = 0;
  SchoolYear *pSchYear;
  for (i = 0; i < Global::all_school_year.size(); i++) {
    if (Global::all_school_year[i]->name == schYear) {
      pSchYear = Global::all_school_year[i];
      break;
    }
  }
  for (i = 0; i < Global::all_school_year[i]->numberOfSemester; i++) {
    if (pSchYear->pSemesters[i]->ordinalOfSemester == sms) {
      return Global::all_semester[i];
    }
  }
  return nullptr;
}

void Semester::loadFromStream(std::istream &f) {
  string _semester_id;
  getline(f, _semester_id);
  assert(_semester_id == semester_id);

  string school_year_id;
  getline(f, school_year_id);
  pSchoolYear = nullptr;
  for (auto sy : Global::all_school_year) {
    if (sy->school_year_id == school_year_id) {
      pSchoolYear = sy;
      break;
    }
  }
  assert(pSchoolYear != nullptr);

  int sz;
  f >> sz;
  for (int i = 0; i < sz; ++i) {
    string course_id;
    getline(f, course_id);
    bool found = false;
    for (auto c : Global::all_course) {
      if (c->course_id == course_id) {
        pCourses.push_back(c);
        found = true;
        break;
      }
    }
    assert(found);
  }
}

void Semester::writeToStream(std::ostream &f) {
  f << semester_id << '\n';
  f << pSchoolYear->school_year_id << '\n';
  f << pCourses.size() << '\n';
  for (auto c : pCourses) {
    f << c->course_id << '\n';
  }
}
