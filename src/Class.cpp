#include "Global.h"
using namespace std;

Class::Class() {}
Class::Class(string id) : class_id(id) {}

string Class::getID() {
    return class_id;
}

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
    cout << "Here is a list of class:\n";
    for (int i = 0; i < Global::all_class.size(); i++) {
        cout << i << ":" << Global::all_class[i]->class_id << "-" << Global::all_class[i]->class_name << "-" << Global::all_class[i]->numberOfStudent << " students" << '\n';
    }
}

void Class::showScoreboard() {
    cout << "Input class ID:";
    string classID;
    cin >> classID;
    Class *cls = Class::findClass(classID);
    cout << "Here is the score board of the class:\n";
    cout << setfill('*');
    cout << setw(117) << '*' << endl;
    for (int i = 0; i < cls->pStudents.size(); i++) {
        cout << "No." << i << endl;
        cout << "ID:" << cls->pStudents[i]->student_id << endl;
        cout << setw(12) << left << "Course ID:";
        cout << setw(100) << left << "Course name";
        cout << setw(5) << left << "GPA:";
        cout << endl;
        for (int j = 0; j < cls->pStudents[i]->pEnrolledCourses.size(); j++) {
            cout << setw(12) << left << cls->pStudents[i]->gpa_courses[j]->crs->course_id;
            cout << setw(100) << left << cls->pStudents[i]->gpa_courses[j]->crs->course_name;
            cout << setw(5) << left << cls->pStudents[i]->gpa_courses[j]->overallMark;
            cout << endl;
        }
        cout << setw(12) << left << "Semester";
        cout << setw(5) << left << "GPA";
<<<<<<< Updated upstream
        for (int j = 0; j < cls->pStudents[i]->gpa_courses.size(); i++) {
            cout << setw(12) << left << cls->pStudents[i]->sms_courses[j]->sms->ordinalOfSemester;
            cout << setw(5) << left << cls->pStudents[i]->sms_courses[j]->gpa;
=======
        cout << endl;
        for (int j = 0; j < cls->pStudents[i]->gpa_semester.size(); i++) {
            cout << setw(12) << left << cls->pStudents[i]->gpa_semester[j]->sms->ordinalOfSemester;
            cout << setw(5) << left << cls->pStudents[i]->gpa_semester[j]->gpa;
>>>>>>> Stashed changes
            cout << endl;
        }
        cout << endl;
    }
}

Class *Class::findClass(string classID) {
    for (int i = 0; i < Global::all_class.size(); i++)
        if (Global::all_class[i]->class_id == classID) return Global::all_class[i];
    return nullptr;
    cout << "Here is the score board of the class:\n";
}

void Class::loadFromStream(std::istream &f) {
    throw "Not implemented yet!";
}

void Class::writeToStream(std::ostream &f) {
    throw "Not implemented yet!";
}
