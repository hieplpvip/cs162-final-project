#include "Global.h"
using namespace std;

Course::Course() {}
Course::Course(string id) : course_id(id) {}

string Course::getID() {
  return course_id;
}

void Course::createCourse() {
  Course *crs = new Course();
  all_course.push_back(crs);
  cout << "Input course ID:";
  cin >> crs->course_id;
  cout << "Input course name:";
  cin >> crs->course_name;
  cout << "Input name of the lecturer:";
  cin >> crs->lecturer;
  cout << "Input start date:";
  cin >> crs->start_date;
  cout << "Input end date:";
  cin >> crs->end_date;
  cout << "Max student in course:";
  cin >> crs->maxNumberOfStudent;
  cout << "Time of the course";
  cout << "\nFirst time in week";
  getline(cin, crs->timeOfCourse[0]);
  cout << "Second time in week";
  getline(cin, crs->timeOfCourse[1]);
  cout << "What school year:";
  string schoolYear;
  cin >> schoolYear;
  cout << "What semester of school year " << schoolYear << ':';
  int semester;
  cin >> semester;
  crs->pSemester = Semester::getSemester(schoolYear, semester);
}

void Course::editCourse() {
  throw "Not implemented yet!";
}

void Course::viewCourse() {
  cout << "Here is a list of course:";
  for (int i = 0; i < all_course.size(); i++) {
    cout << "Course #" << i << ": ";
    cout << all_course[i]->course_id << " - ";
    cout << all_course[i]->course_name << "- ";
    cout << all_course[i]->pStudents.size() << "/";
    cout << all_course[i]->maxNumberOfStudent << " students\n";
    cout << "Lecturer:" << all_course[i]->lecturer << '\n';
    cout << "Start date:" << all_course[i]->start_date << '\n';
    cout << "End date:" << all_course[i]->end_date << '\n';
    cout << "Time:" << '\n';
    cout << all_course[i]->timeOfCourse[0] << '\n';
    cout << all_course[i]->timeOfCourse[1] << '\n';
  }
}

void Course::setCourseRegistration() {
  clearScreen();
  if (courseRegistrationOpen) {
    string cmd;
    cout << "Course Registration is open. Type 'close' to close it.\n";
    cin >> cmd;
    if (cmd == "close") {
      courseRegistrationOpen = false;
      cout << "Course Registration is close\n";
    } else {
      cout << "Invalid response\n";
    }
    milliSleep(1000);
  } else {
    string cmd;
    cout << "Course Registration is close. Type 'open' to open it.\n";
    cin >> cmd;
    if (cmd == "open") {
      courseRegistrationOpen = true;
      cout << "Course Registration is open\n";
    } else {
      cout << "Invalid response\n";
    }
    milliSleep(1000);
  }
}

void Course::viewEnrolledCourse() {
  throw "Not implemented yet!";
}

void Course::enrollCourse() {
  throw "Not implemented yet!";
}

void Course::unEnrollCourse() {
  throw "Not implemented yet!";
}

void Course::viewScore() {
  throw "Not implemented yet!";
}

bool Course::checkConflict(Course *crs, Vector<Course *> allEnrolledCourse) {
  for (int i = 0; i < allEnrolledCourse.size(); i++) {
    if (!(crs->course_id == allEnrolledCourse[i]->course_id)) {
      if (crs->timeOfCourse[0] == allEnrolledCourse[i]->timeOfCourse[0] || crs->timeOfCourse[0] == allEnrolledCourse[i]->timeOfCourse[1])
        return true;
      if (crs->timeOfCourse[1] == allEnrolledCourse[i]->timeOfCourse[0] || crs->timeOfCourse[1] == allEnrolledCourse[i]->timeOfCourse[1])
        return true;
    }
  }
  return false;
}

void Course::viewScoreboard() {
  cout << "Input the school year:";
  string schoolYear;
  cin >> schoolYear;
  cout << "Input semester:";
  int sms;
  cin >> sms;
  cout << "Input course ID:";
  string courseID;
  cin >> courseID;
  Course *course;
  for (int i = 0; i < all_course.size(); i++) {
    if (all_course[i]->pSemester->pSchoolYear->name == schoolYear && all_course[i]->pSemester->semester_ordinal) {
      course = all_course[i];
      break;
    }
  }
  cout << "List of student in course scoreboard:\n";
  cout << setw(10) << left << "ID";
  cout << setw(60) << left << "Name";
  cout << setw(5) << right << "GPA";
  cout << endl;
  cout << setfill('-');
  cout << setw(75) << '-' << endl;
  cout << setfill(' ');
  for (int i = 0; i < course->pStudents.size(); i++) {
    cout << setw(10) << left << course->pStudents[i]->student_id;
    cout << setw(60) << left << course->pStudents[i]->firstName + ' ' + course->pStudents[i]->lastName;
    for (int j = 0; j < course->pStudents[i]->gpa_courses.size(); j++) {
      if (course->pStudents[i]->gpa_courses[j]->crs == course) {
        cout << setw(5) << right << course->pStudents[i]->gpa_courses[j]->overallMark << endl;
        break;
      }
    }
  }
}

void Course::viewStudentInCourse() {
  cout << "Input course ID:";
  string crsID;
  cin >> crsID;
  cout << "Input school year:";
  string schYear;
  cin >> schYear;
  cout << "Input semester:";
  int sms;
  cin >> sms;
  Course *course = findCourse(Semester::getSemester(schYear, sms), crsID);
  cout << "Here is the list of student in class:\n";
  cout << setw(12) << left << "ID";
  cout << setw(60) << left << "Name";
  cout << endl;
  cout << setfill('-');
  cout << setw(72) << "-" << endl;
  cout << setw(' ');
  for (int i = 0; i < course->pStudents.size(); i++) {
    cout << setw(12) << left << course->pStudents[i]->student_id;
    cout << setw(60) << left << course->pStudents[i]->firstName << " " << course->pStudents[i]->lastName;
    cout << endl;
  }
}

Course *Course::findCourse(Semester *sms, string crsID) {
  for (int i = 0; i < sms->pCourses.size(); i++) {
    if (crsID == sms->pCourses[i]->course_id) {
      return sms->pCourses[i];
    }
  }
  return nullptr;
}

void Course::loadFromStream(std::istream &f) {
  string _course_id;
  getline(f, _course_id);
  assert(_course_id == course_id);

  getline(f, course_name);
  getline(f, lecturer);
  getline(f, start_date);
  getline(f, end_date);

  string semester_id;
  getline(f, semester_id);
  pSemester = nullptr;
  for (auto sem : all_semester) {
    if (sem->semester_id == semester_id) {
      pSemester = sem;
      break;
    }
  }
  assert(pSemester != nullptr);

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
  f >> maxNumberOfStudent;
  f.ignore();
}

void Course::writeToStream(std::ostream &f) {
  f << course_id << '\n';
  f << course_name << '\n';
  f << lecturer << '\n';
  f << start_date << '\n';
  f << end_date << '\n';
  f << pSemester->semester_id << '\n';
  f << pStudents.size() << '\n';
  for (auto st : pStudents) {
    f << st->student_id << '\n';
  }
  f << maxNumberOfStudent << '\n';
}
