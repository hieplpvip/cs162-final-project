#include "Global.h"
using namespace std;

SchoolYear::SchoolYear() {}
SchoolYear::SchoolYear(string id) : school_year_id(id) {}

string SchoolYear::getID() {
  return school_year_id;
}

SchoolYear *SchoolYear::selectSchoolYear(const Vector<SchoolYear *> &school_years, bool showonly) {
  if (school_years.empty()) {
    cout << "No school year\n";
    milliSleep(1000);
    return nullptr;
  }

  while (true) {
    clearScreen();

    for (int i = 0; i < school_years.size(); i++) {
      cout << (i + 1) << ". ";
      cout << school_years[i]->name << " (";
      cout << school_years[i]->pSemesters.size() << " semesters)\n";
    }
    if (showonly) {
      waitForEnter();
      return nullptr;
    }
    cout << "0. Go Back\n";

    int ind;
    cout << "Please choose one: ";
    cin >> ind;

    if (ind < 0 || ind > school_years.size()) {
      cout << "Invalid choice\n";
      milliSleep(1000);
    } else if (ind == 0) {
      return nullptr;
    } else {
      return school_years[ind - 1];
    }
  }
}

void SchoolYear::createSchoolYear() {
  clearScreen();

  string name;
  cout << "School year (e.g. 2020-2021): ";
  cin >> name;

  if (name.length() != 9 || name[4] != '-' || stoi(name.substr(0, 4)) + 1 != stoi(name.substr(5, 4))) {
    cout << "Invalid!\n";
    milliSleep(1000);
    return;
  }

  for (auto sy : all_school_year) {
    if (sy->name == name) {
      cout << "School year " << name << " already exists\n";
      milliSleep(1000);
      return;
    }
  }

  SchoolYear *sy = new SchoolYear();
  sy->name = name;
  sy->school_year_id = name;
  sy->school_year_id[4] = '_';
  all_school_year.push_back(sy);
}

void SchoolYear::viewSchoolYear() {
  selectSchoolYear(all_school_year, true);
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
    for (auto sem : all_semester) {
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
