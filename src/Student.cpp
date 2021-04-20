#include "Global.h"
using namespace std;

Student::Student() {}
Student::Student(string id) : student_id(id) {}

string Student::getID() {
  return student_id;
}

void Student::createStudent() {
  Student *student = new Student();
  cout << "Input student ID:";
  cin >> student->student_id;
  cout << "Input student first name:";
  cin >> student->firstName;
  cout << "Input student last name:";
  cin >> student->lastName;
  cout << "Input student date of birth";
  cin >> student->dateOfBirth;
  cout << "Input student gender:";
  cin >> student->gender;
  cout << "Input student social ID:";
  cin >> student->socialID;
  cout << "Input student class ID";
  string stuClass;
  cin >> stuClass;
  for (int i = 0; i < Global::all_class.size(); i++) {
    if (Global::all_class[i]->class_id == stuClass) {
      Global::all_class[i]->pStudents.push_back(student);
      student->pClass = Global::all_class[i];
      break;
    }
  }
  Global::all_student.push_back(student);
}

void Student::editStudent() {
  throw "Not implemented yet!";
}

void Student::viewStudent() {
  for (int i = 0; i < Global::all_student.size(); i++) {
    cout << "Student ID:  " << Global::all_student[i]->student_id << endl;
    cout << "First name:  " << Global::all_student[i]->firstName << endl;
    cout << "Last name:  " << Global::all_student[i]->lastName << endl;
    cout << "Gender:  " << Global::all_student[i]->gender << endl;
    cout << "Date of birth:  " << Global::all_student[i]->dateOfBirth << endl;
    cout << "SocialID:  " << Global::all_student[i]->socialID << endl;
  }
}

void Student::loadFromStream(std::istream &f) {
  string _student_id;
  getline(f, _student_id);
  assert(_student_id == student_id);

  getline(f, firstName);
  getline(f, lastName);
  getline(f, gender);
  getline(f, dateOfBirth);
  getline(f, socialID);
}

void Student::writeToStream(std::ostream &f) {
  f << student_id << '\n';
  f << firstName << '\n';
  f << lastName << '\n';
  f << gender << '\n';
  f << dateOfBirth << '\n';
  f << socialID << '\n';
}
