#include "Global.h"
using namespace std;

Student::Student() {}
Student::Student(string id) : student_id(id) {}

string Student::getID() {
  return student_id;
}

void Student::createStudent() {
  clearScreen();

  int cmd;
  cout << "1. Manually enter student information\n";
  cout << "2. Import student information from CSV\n";
  cin >> cmd;
  switch (cmd) {
    case 1:
      createStudentFromScreen();
      break;
    case 2:
      createStudentFromCSV();
      break;
    default:
      cout << "Invalid choice\n";
  }
}

void Student::createStudentFromScreen() {
  clearScreen();

  Student *st = new Student();

  cout << "Student ID: ";
  cin >> st->student_id;
  cout << "First Name: ";
  cin >> st->firstName;
  cout << "Last Name: ";
  cin >> st->lastName;
  cout << "Date of Birth: ";
  cin >> st->dateOfBirth;
  cout << "Gender (MALE/FEMALE): ";
  cin >> st->gender;
  cout << "Social ID: ";
  cin >> st->socialID;

  cout << "Class ID: ";
  string class_id;
  cin >> class_id;
  st->pClass = nullptr;
  for (auto cls : all_class) {
    if (cls->class_id == class_id) {
      st->pClass = cls;
      break;
    }
  }

  if (st->pClass == nullptr) {
    cout << "Could not find class with ID " << class_id << '\n';
    delete st;
    return;
  }

  st->pClass->pStudents.push_back(st);
  st->pUser = User::createStudentUser(st->student_id, st->dateOfBirth, st);
  all_student.push_back(st);

  cout << "Login credentials for new student:\n";
  cout << "Username: " << st->pUser->username << '\n';
  cout << "Password: " << st->pUser->password << '\n';

  waitForEnter();
}

void Student::createStudentFromCSV() {
  clearScreen();

  string csvPath;
  cout << "Please enter CSV file path: ";
  cin.ignore();
  getline(cin, csvPath);

  ifstream fCSV(csvPath);
  if (!fCSV.is_open()) {
    cout << "Could not open CSV file\n";
    milliSleep(1000);
    return;
  }

  string line;

  // skip header
  getline(fCSV, line);

  // import each student
  int success = 0, total = 0;
  while (getline(fCSV, line)) {
    ++total;

    Student *st = new Student();
    string class_id;
    auto res = CSVParser::parseLineToArgs(line,
                                          st->student_id,
                                          st->firstName,
                                          st->lastName,
                                          st->dateOfBirth,
                                          st->gender,
                                          st->socialID,
                                          class_id);
    if (res != CSVParser::ParseError::Success) {
      continue;
    }

    st->pClass = nullptr;
    for (auto cls : all_class) {
      if (cls->class_id == class_id) {
        st->pClass = cls;
        break;
      }
    }

    if (st->pClass == nullptr) {
      delete st;
      continue;
    }

    st->pClass->pStudents.push_back(st);
    st->pUser = User::createStudentUser(st->student_id, st->dateOfBirth, st);
    all_student.push_back(st);
    ++success;
  }

  fCSV.close();

  cout << "Imported " << success << "/" << total << " students\n\n";
  cout << "Default login credentials for new student:\n";
  cout << "Username: same as Student ID\n";
  cout << "Password: same as Date of Birth\n";

  waitForEnter(false);
}

void Student::editStudent() {
  throw "Not implemented yet!";
}

void Student::viewStudent() {
  for (int i = 0; i < all_student.size(); i++) {
    cout << "Student ID:  " << all_student[i]->student_id << endl;
    cout << "First name:  " << all_student[i]->firstName << endl;
    cout << "Last name:  " << all_student[i]->lastName << endl;
    cout << "Gender:  " << all_student[i]->gender << endl;
    cout << "Date of birth:  " << all_student[i]->dateOfBirth << endl;
    cout << "SocialID:  " << all_student[i]->socialID << endl;
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

  string user_id;
  getline(f, user_id);
  pUser = nullptr;
  for (auto u : all_user) {
    if (u->user_id == user_id) {
      pUser = u;
      break;
    }
  }
  assert(pUser != nullptr);

  string class_id;
  getline(f, class_id);
  pClass = nullptr;
  for (auto cls : all_class) {
    if (cls->class_id == class_id) {
      pClass = cls;
      break;
    }
  }
  assert(pClass != nullptr);

  int sz;
  f >> sz;
  f.ignore();
  for (int i = 0; i < sz; ++i) {
    string course_id;
    getline(f, course_id);
    bool found = false;
    for (auto crs : all_course) {
      if (crs->course_id == course_id) {
        pEnrolledCourses.push_back(crs);
        found = true;
        break;
      }
    }
    assert(found);
  }
}

void Student::writeToStream(std::ostream &f) {
  f << student_id << '\n';
  f << firstName << '\n';
  f << lastName << '\n';
  f << gender << '\n';
  f << dateOfBirth << '\n';
  f << socialID << '\n';
  f << pUser->user_id << '\n';
  f << pClass->class_id << '\n';
  f << pEnrolledCourses.size() << '\n';
  for (auto crs : pEnrolledCourses) {
    f << crs->course_id << '\n';
  }
}
