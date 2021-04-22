#include "Global.h"
using namespace std;

Class::Class() {}
Class::Class(string id) : class_id(id) {}

string Class::getID() {
  return class_id;
}

Class *Class::selectClass(const Vector<Class *> &classes) {
  clearScreen();

  if (classes.empty()) {
    cout << "No class\n";
    milliSleep(1000);
    return nullptr;
  }

  while (true) {
    for (int i = 0; i < classes.size(); i++) {
      cout << (i + 1) << ". ";
      cout << classes[i]->class_name << " - ";
      cout << classes[i]->pStudents.size() << " students" << '\n';
    }
    cout << "0. Go Back\n";

    int ind;
    cout << "Please select one: ";
    cin >> ind;

    if (ind < 0 || ind > classes.size()) {
      cout << "Invalid choice\n";
      milliSleep(1000);
    } else if (ind == 0) {
      return nullptr;
    } else {
      return classes[ind - 1];
    }
  }
}

void Class::createClass() {
  clearScreen();

  Class *cls = new Class();
  cout << "Class ID: ";
  cin >> cls->class_id;
  cout << "Class Name: ";
  cin >> cls->class_name;

  all_class.push_back(cls);
}

void Class::viewClass() {
  while (true) {
    auto cls = selectClass(all_class);
    if (!cls) break;

    while (true) {
      clearScreen();

      cout << "Class " << cls->class_name << " - ";
      cout << cls->pStudents.size() << " students\n\n";

      int cmd;
      cout << "1. View students\n";
      cout << "0. Go Back\n";
      cout << "Please select one: ";
      cin >> cmd;

      if (cmd == 0) break;
      switch (cmd) {
        case 1:
          Student::selectStudent(cls->pStudents, true);
          break;
        default:
          cout << "Invalid choice\n";
          break;
      }
    }
  }
}

void Class::showScoreboard() {
  throw("Not implemented yet");
}

void Class::loadFromStream(std::istream &f) {
  string _class_id;
  getline(f, _class_id);
  assert(_class_id == class_id);

  getline(f, class_name);

  int sz;
  f >> sz;
  f.ignore();
  for (int i = 0; i < sz; ++i) {
    string student_id;
    getline(f, student_id);
    bool found = false;
    for (auto st : all_student) {
      if (st->student_id == student_id) {
        pStudents.push_back(st);
        found = true;
        break;
      }
    }
    assert(found);
  }
}

void Class::writeToStream(std::ostream &f) {
  f << class_id << '\n';
  f << class_name << '\n';
  f << pStudents.size() << '\n';
  for (auto st : pStudents) {
    f << st->student_id << '\n';
  }
}
