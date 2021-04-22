#include "Global.h"
using namespace std;

const string Semester::ORD2STR[] = {
    "",  // padding
    "Fall",
    "Spring",
    "Summer",
};

Semester::Semester() {}
Semester::Semester(string id) : semester_id(id) {}

string Semester::getID() {
  return semester_id;
}

Semester *Semester::selectSemester(const Vector<Semester *> &semesters) {
  clearScreen();

  if (semesters.empty()) {
    cout << "No semester\n";
    milliSleep(1000);
    return nullptr;
  }

  while (true) {
    for (int i = 0; i < semesters.size(); i++) {
      cout << (i + 1) << ". ";
      cout << ORD2STR[semesters[i]->semester_ordinal] << ' ';
      cout << semesters[i]->pSchoolYear->name << '\n';
    }
    cout << "0. Go Back\n";

    int ind;
    cout << "Please select one: ";
    cin >> ind;

    if (ind < 0 || ind > semesters.size()) {
      cout << "Invalid choice\n";
      milliSleep(1000);
    } else if (ind == 0) {
      return nullptr;
    } else {
      return semesters[ind - 1];
    }
  }
}

void Semester::createSemester() {
  clearScreen();

  if (all_school_year.empty()) {
    cout << "Please create a school year first\n";
    milliSleep(1000);
    return;
  }

  for (int i = 0; i < all_school_year.size(); ++i) {
    auto sy = all_school_year[i];
    cout << (i + 1) << ". " << sy->name << '\n';
  }

  int ind;
  cout << "\nPlease select school year of new semester: ";
  cin >> ind;
  if (ind < 1 || ind > all_school_year.size()) {
    cout << "Invalid\n";
    milliSleep(1000);
    return;
  }
  --ind;

  int ord;
  cout << "\n1 (Fall), 2 (Spring), 3 (Summer)\n";
  cout << "Which semester is this: ";
  cin >> ord;
  if (ord < 1 || ord > 3) {
    cout << "Invalid\n";
    milliSleep(1000);
    return;
  }

  auto sy = all_school_year[ind];
  for (auto sem : sy->pSemesters) {
    if (sem->semester_ordinal == ord) {
      cout << "School year " << sy->name << " already has semester " << ord << '\n';
      milliSleep(1000);
      return;
    }
  }

  auto sem = new Semester();
  sem->semester_id = sy->school_year_id + '_' + to_string(ord);
  sem->semester_ordinal = ord;
  sem->pSchoolYear = sy;

  sy->pSemesters.push_back(sem);
  all_semester.push_back(sem);
  current_semester = sem;
}

void Semester::viewSemester() {
  string schoolYear;
  cout << "Input school year:";
  cin >> schoolYear;
  int count = 1;
  for (int i = 0; i < all_semester.size(); i++) {
    if (all_semester[i]->pSchoolYear->name == schoolYear) {
      cout << "Semester " << count++ << ":\n";
      cout << "  Number of course:" << all_semester[i]->pCourses.size() << '\n';
    }
  }
}

Semester *Semester::getSemester(string schYear, int sms) {
  int i = 0;
  SchoolYear *pSchYear;
  for (i = 0; i < all_school_year.size(); i++) {
    if (all_school_year[i]->name == schYear) {
      pSchYear = all_school_year[i];
      break;
    }
  }
  for (i = 0; i < all_school_year[i]->numberOfSemester; i++) {
    if (pSchYear->pSemesters[i]->semester_ordinal == sms) {
      return all_semester[i];
    }
  }
  return nullptr;
}

void Semester::loadFromStream(std::istream &f) {
  string _semester_id;
  getline(f, _semester_id);
  assert(_semester_id == semester_id);

  f >> semester_ordinal;
  f.ignore();

  string school_year_id;
  getline(f, school_year_id);
  pSchoolYear = nullptr;
  for (auto sy : all_school_year) {
    if (sy->school_year_id == school_year_id) {
      pSchoolYear = sy;
      break;
    }
  }
  assert(pSchoolYear != nullptr);

  int sz;
  f >> sz;
  f.ignore();
  for (int i = 0; i < sz; ++i) {
    string course_id;
    getline(f, course_id);
    bool found = false;
    for (auto crs : all_course) {
      if (crs->course_id == course_id) {
        pCourses.push_back(crs);
        found = true;
        break;
      }
    }
    assert(found);
  }
}

void Semester::writeToStream(std::ostream &f) {
  f << semester_id << '\n';
  f << semester_ordinal << '\n';
  f << pSchoolYear->school_year_id << '\n';
  f << pCourses.size() << '\n';
  for (auto crs : pCourses) {
    f << crs->course_id << '\n';
  }
}
