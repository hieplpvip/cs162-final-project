#include "Global.h"
using namespace std;

Class::Class() {}
Class::Class(string id) : class_id(id) {}

void Class::createClass() {
  Class *cls = new Class();
  cout << "Input class id:";
  cin >> cls->class_id;
  cout << "Input class name:";
  cin >> cls->class_name;
  Global::all_class.push_back(cls);
}

void Class::showClass() {
  cout << "Here is a list of class:\n";
  for (int i = 0; i < Global::all_class.size(); i++) {
    cout << i << ":" << Global::all_class[i]->class_id << "-" << Global::all_class[i]->class_name << "-" << Global::all_class[i]->numberOfStudent << " students" << '\n';
  }
}

void Class::showScoreboard() {
  cout << "Here is the score board of the class:\n";
}

void Class::findClass(string classID) {
  throw "Not implemented yet!";
}

Class *Class::loadFromStream(std::istream &f) {
  throw "Not implemented yet!";
}

void Class::writeToStream(std::ostream &f) {
  throw "Not implemented yet!";
}
