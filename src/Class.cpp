#include "Global.h"
using namespace std;

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

Class *Class::findClass(string classID) {
    for (int i = 0; i < Global::all_class.size(); i++)
        if (Global::all_class[i]->class_id == classID) return Global::all_class[i];
    return nullptr;
}
