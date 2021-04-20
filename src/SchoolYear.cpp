#include "Global.h"
using namespace std;

SchoolYear::SchoolYear() {}
SchoolYear::SchoolYear(string id) : school_year_id(id) {}

string SchoolYear::getID() {
  return school_year_id;
}

void SchoolYear::createSchoolYear() {
  SchoolYear *schYear = nullptr;
  string name;
  while (true) {
    cout << "School year (e.g. 2020-2021): ";
    cin >> name;
    if (name.length() != 9 || name[4] != '-' || stoi(name.substr(0, 4)) + 1 != stoi(name.substr(5, 4))) {
      cout << "Invalid!\n";
      milliSleep(1000);
      continue;
    }
    schYear = new SchoolYear();
    schYear->name = name;
    schYear->school_year_id = name;
    schYear->school_year_id[4] = '_';
    break;
  }
  Global::all_school_year.push_back(schYear);
  for (int i = 0; i < schYear->numberOfSemester; i++) {
    Semester::createSemester();
    Global::all_semester.back()->pSchoolYear = schYear;
    Global::all_semester.back()->ordinalOfSemester = i + 1;
  }
}

void SchoolYear::editSchoolYear() {
  throw "Not implemented yet!";
}

void SchoolYear::viewSchoolYear() {
  cout << "List of school year:\n";
  for (int i = 0; i < Global::all_school_year.size(); i++) {
    cout << Global::all_school_year[i]->name << '\n';
  }
}

void SchoolYear::loadFromStream(std::istream &f) {
  string _school_year_id;
  getline(f, _school_year_id);
  assert(_school_year_id == school_year_id);

  getline(f, name);

  int sz;
  f >> sz;
  f.ignore();
  for (int i = 0; i < sz; ++i) {
    string semester_id;
    getline(f, semester_id);
    bool found = false;
    for (auto sem : Global::all_semester) {
      if (sem->semester_id == semester_id) {
        pSemesters.push_back(sem);
        found = true;
        break;
      }
    }
    assert(found);
  }
}

void SchoolYear::writeToStream(std::ostream &f) {
  f << school_year_id << '\n';
  f << name << '\n';
  f << pSemesters.size() << '\n';
  for (auto sem : pSemesters) {
    f << sem->semester_id << '\n';
  }
}
