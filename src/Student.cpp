#include "Global.h"
using namespace std;

Student::Student() {}
Student::Student(string id) : student_id(id) {}

string Student::getID() {
  return student_id;
}

Student *Student::selectStudent(const Vector<Student *> &students, bool showonly) {
  if (students.empty()) {
    cout << "No student\n";
    milliSleep(1000);
    return nullptr;
  }

  while (true) {
    clearScreen();

    for (int i = 0; i < students.size(); i++) {
      cout << (i + 1) << ". ";
      cout << students[i]->student_id << " - ";
      cout << students[i]->firstName << ' ' << students[i]->lastName << '\n';
    }
    if (showonly) {
      waitForEnter();
      return nullptr;
    }
    cout << "0. Go Back\n";

    int ind;
    cout << "Please choose one: ";
    cin >> ind;

    if (ind < 0 || ind > students.size()) {
      cout << "Invalid choice\n";
      milliSleep(1000);
    } else if (ind == 0) {
      return nullptr;
    } else {
      return students[ind - 1];
    }
  }
}

void Student::createStudent() {
  while (true) {
    clearScreen();

    int cmd;
    cout << "1. Manually enter student information\n";
    cout << "2. Import student information from CSV\n";
    cout << "0. Go Back\n";
    cout << "Please choose one: ";
    cin >> cmd;

    if (cmd == 0) break;
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

  if (!st->pClass) {
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

    if (!st->pClass) {
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

  waitForEnter();
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

void Student::viewScoreboard() {
  assert(current_user->role == User::UserRole::STUDENT);
  auto st = current_user->pStudent;

  while (true) {
    clearScreen();

    int cmd;
    cout << "1. View course score\n";
    cout << "2. View GPA\n";
    cout << "0. Go Back\n";
    cout << "Please choose one: ";
    cin >> cmd;

    if (cmd == 0) break;
    switch (cmd) {
      case 1:
        st->viewCourseScore();
        break;
      case 2:
        st->viewGPA();
        break;
      default:
        cout << "Invalid choice\n";
        break;
    }
  }
}

void Student::viewEnrolledCourse() {
  clearScreen();

  assert(current_user->role == User::UserRole::STUDENT);
  auto st = current_user->pStudent;
  auto &enrolledCourses = st->pEnrolledCourses;

  if (enrolledCourses.empty()) {
    cout << "You haven't enrolled in any courses\n";
    milliSleep(1000);
    return;
  }

  cout << "Here is a list of courses you have enrolled:\n\n";
  for (int i = 0; i < enrolledCourses.size(); i++) {
    cout << "Course #" << (i + 1) << ": ";
    cout << enrolledCourses[i]->course_code << " - ";
    cout << enrolledCourses[i]->course_name << " - ";
    cout << "Semester " << enrolledCourses[i]->pSemester->semester_ordinal << " - ";
    cout << "School Year " << enrolledCourses[i]->pSemester->pSchoolYear->name << '\n';
    cout << "Lecturer: " << enrolledCourses[i]->lecturer << '\n';
    cout << "Number of credits: " << enrolledCourses[i]->numberOfCredits << '\n';
    cout << "Start date: " << enrolledCourses[i]->start_date << '\n';
    cout << "End date: " << enrolledCourses[i]->end_date << '\n';
    cout << "Schedule:\n";
    cout << "  First session: " << enrolledCourses[i]->schedule[0] << '\n';
    cout << "  Second session: " << enrolledCourses[i]->schedule[1] << '\n';
    cout << '\n';
  }

  waitForEnter();
}

void Student::viewSchedule() {
  clearScreen();

  assert(current_user->role == User::UserRole::STUDENT);
  auto st = current_user->pStudent;

  Vector<Course *> courses;
  for (auto crs : st->pEnrolledCourses) {
    if (crs->pSemester == current_semester) {
      courses.push_back(crs);
    }
  }

  if (courses.empty()) {
    cout << "You haven't enrolled in any courses this semester\n";
    milliSleep(1000);
    return;
  }

  for (int i = 0; i < courses.size(); i++) {
    cout << "Course #" << (i + 1) << ": ";
    cout << courses[i]->course_code << " - ";
    cout << courses[i]->course_name << '\n';
    cout << "  First session: " << courses[i]->schedule[0] << '\n';
    cout << "  Second session: " << courses[i]->schedule[1] << '\n';
    cout << '\n';
  }

  waitForEnter();
}

void Student::viewCourseScore() {
  while (true) {
    auto crs = Course::selectCourse(pEnrolledCourses);
    if (!crs) break;

    clearScreen();

    int i = pEnrolledCourses.find(crs);
    auto score = pCourseScores[i];
    cout << pEnrolledCourses[i]->course_code << " - ";
    cout << pEnrolledCourses[i]->course_name << '\n';
    cout << "Midterm Mark: " << score.midtermMark << '\n';
    cout << "Final Mark: " << score.finalMark << '\n';
    cout << "Other Mark: " << score.otherMark << '\n';
    cout << "Total Mark: " << score.totalMark << '\n';

    waitForEnter();
  }
}

void Student::viewGPA() {
  clearScreen();

  for (auto sy : all_school_year) {
    bool ok = false;
    for (auto sem : sy->pSemesters) {
      if (calculateSemesterGPA(sem) > 0) {
        ok = true;
      }
    }

    if (!ok) continue;

    cout << "School Year " << sy->name << ":\n";
    for (auto sem : sy->pSemesters) {
      double sem_gpa = calculateSemesterGPA(sem);
      if (sem_gpa > 0) {
        cout << "  " << Semester::ORD2STR[sem->semester_ordinal] << " Semester:\n";
        for (int i = 0; i < pEnrolledCourses.size(); ++i) {
          if (pEnrolledCourses[i]->pSemester == sem) {
            cout << "    ";
            cout << pEnrolledCourses[i]->course_code << " - ";
            cout << pEnrolledCourses[i]->course_name << ": ";
            cout << pCourseScores[i].totalMark << '\n';
          }
        }
        cout << "    Semester GPA: " << sem_gpa << '\n';
      }
    }
  }

  cout << "Overall GPA: " << calculateTotalGPA() << '\n';

  waitForEnter();
}

void Student::enrollCourse() {
  clearScreen();

  if (!courseRegistrationOpen) {
    cout << "Course Registration is close\n";
    milliSleep(1000);
    return;
  }

  if (!current_semester) {
    cout << "No current semester\n";
    milliSleep(1000);
    return;
  }

  assert(current_user->role == User::UserRole::STUDENT);
  auto st = current_user->pStudent;

  Vector<Course *> courses;
  for (auto crs : current_semester->pCourses) {
    if (crs->pStudents.find(st) == crs->pStudents.size()) {
      courses.push_back(crs);
    }
  }

  while (true) {
    clearScreen();

    if (courses.empty()) {
      cout << "You have enrolled in all courses this semester\n";
      milliSleep(1000);
      return;
    }

    auto crs = Course::selectCourse(courses);
    if (!crs) break;

    for (auto enrolled_crs : st->pEnrolledCourses) {
      for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
          if (enrolled_crs->schedule[i] == crs->schedule[j]) {
            cout << "This course conflicts with course ";
            cout << enrolled_crs->course_code << " - " << enrolled_crs->course_name << '\n';
            milliSleep(1000);
            goto conflict;
          }
        }
      }
    }

    st->pEnrolledCourses.push_back(crs);
    crs->pStudents.push_back(st);
    courses.erase(crs);

    cout << "You have enrolled in course " << crs->course_code << " - " << crs->course_name << '\n';
    milliSleep(1000);

  conflict:
    // do nothing
    continue;
  }
}

void Student::unEnrollCourse() {
  clearScreen();

  if (!courseRegistrationOpen) {
    cout << "Course Registration is close\n";
    milliSleep(1000);
    return;
  }

  if (!current_semester) {
    cout << "No current semester\n";
    milliSleep(1000);
    return;
  }

  assert(current_user->role == User::UserRole::STUDENT);
  auto st = current_user->pStudent;

  Vector<Course *> courses;
  for (auto crs : st->pEnrolledCourses) {
    if (crs->pSemester == current_semester) {
      courses.push_back(crs);
    }
  }

  while (true) {
    clearScreen();

    if (courses.empty()) {
      cout << "You haven't enrolled in any courses this semester\n";
      milliSleep(1000);
      return;
    }

    auto crs = Course::selectCourse(courses);
    if (!crs) break;

    st->pEnrolledCourses.erase(crs);
    crs->pStudents.erase(st);
    courses.erase(crs);

    cout << "You have unenrolled from course " << crs->course_code << " - " << crs->course_name << '\n';
    milliSleep(1000);
  }
}

double Student::calculateSemesterGPA(Semester *sem) {
  double weightedSum = 0;
  int totalCredits = 0;
  for (int i = 0; i < pEnrolledCourses.size(); ++i) {
    if (pEnrolledCourses[i]->pSemester == sem) {
      weightedSum += (double)pEnrolledCourses[i]->numberOfCredits * (double)pCourseScores[i].totalMark;
      totalCredits += pEnrolledCourses[i]->numberOfCredits;
    }
  }
  if (totalCredits == 0) {
    return -1;
  } else {
    return weightedSum / (double)totalCredits;
  }
}

double Student::calculateTotalGPA() {
  double weightedSum = 0;
  int totalCredits = 0;
  for (int i = 0; i < pEnrolledCourses.size(); ++i) {
    weightedSum += (double)pEnrolledCourses[i]->numberOfCredits * (double)pCourseScores[i].totalMark;
    totalCredits += pEnrolledCourses[i]->numberOfCredits;
  }
  if (totalCredits == 0) {
    return -1;
  } else {
    return weightedSum / (double)totalCredits;
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
  for (int i = 0; i < sz; ++i) {
    double midtermMark, finalMark, otherMark, totalMark;
    f >> midtermMark;
    f >> finalMark;
    f >> otherMark;
    f >> totalMark;
    pCourseScores.push_back({midtermMark, finalMark, otherMark, totalMark});
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
  for (auto score : pCourseScores) {
    f << score.midtermMark << ' ';
    f << score.finalMark << ' ';
    f << score.otherMark << ' ';
    f << score.totalMark << '\n';
  }
}
