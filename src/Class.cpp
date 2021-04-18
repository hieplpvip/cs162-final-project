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
    cout << "Input class ID:";
    string classID;
    cin >> classID;
    Class *cls = findClass(classID);
    cout << "Here is the score board of the class:\n";
    cout << setfill('*');
    cout << setw(17) << '*' < < < endl;
    for (int i = 0; i < cls->pStudents.size(); i++) {
        cout << "No." << i << endl;
        cout << "ID:" << cls->pStudents[i]->student_id << endl;
        cout << setw(12) << left << "Course ID:";
        cout << setw(5) << left << "GPA:";
        cout << endl;
        for (int j = 0; j < cls->pStudents[i]->pEnrolledCourses.size(); j++) {
        }
    }
}

Class *Class::findClass(string classID) {
    for (int i = 0; i < Global::all_class.size(); i++)
        if (Global::all_class[i]->class_id == classID) return Global::all_class[i];
    return nullptr;
}
