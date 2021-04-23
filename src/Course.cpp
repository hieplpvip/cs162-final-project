#include "Global.h"
using namespace std;

Course::Course() {}
Course::Course(string id) : course_id(id) {}

string Course::getID() {
  return course_id;
}

Course *Course::selectCourse(const Vector<Course *> &courses, bool showonly) {
  if (courses.empty()) {
    cout << "No course\n";
    milliSleep(1000);
    return nullptr;
  }

  while (true) {
    clearScreen();

    for (int i = 0; i < courses.size(); i++) {
      cout << (i + 1) << ". ";
      cout << courses[i]->course_code << " - ";
      cout << courses[i]->course_name << '\n';
    }
    if (showonly) {
      waitForEnter();
      return nullptr;
    }
    cout << "0. Go Back\n";

    int ind;
    cout << "Please select one: ";
    cin >> ind;

    if (ind < 0 || ind > courses.size()) {
      cout << "Invalid choice\n";
      milliSleep(1000);
    } else if (ind == 0) {
      return nullptr;
    } else {
      return courses[ind - 1];
    }
  }
}

void Course::createCourse() {
  clearScreen();

  if (current_semester == nullptr) {
    cout << "Please create a semester first\n";
    milliSleep(1000);
    return;
  }

  cout << "This new course will be taught in ";
  cout << "Semester " << current_semester->semester_ordinal << " - ";
  cout << "School Year " << current_semester->pSchoolYear->name << "\n\n";

  Course *crs = new Course();

  cin.ignore();
  cout << "Course Code: ";
  getline(cin, crs->course_code);
  cout << "Course Name: ";
  getline(cin, crs->course_name);
  cout << "Lecturer: ";
  getline(cin, crs->lecturer);
  cout << "Start Date: ";
  getline(cin, crs->start_date);
  cout << "End Date: ";
  getline(cin, crs->end_date);
  cout << "Max number of students: ";
  cin >> crs->maxNumberOfStudents;
  cout << "Number of credits: ";
  cin >> crs->numberOfCredits;
  cin.ignore();
  cout << "Schedule:\n";
  cout << "  First session: ";
  getline(cin, crs->schedule[0]);
  cout << "  Second session: ";
  getline(cin, crs->schedule[1]);

  crs->course_id = current_semester->semester_id + '_' + crs->course_code;

  crs->pSemester = current_semester;
  current_semester->pCourses.push_back(crs);
  all_course.push_back(crs);
}

void Course::viewCourse() {
  while (true) {
    auto sy = SchoolYear::selectSchoolYear(all_school_year);
    if (!sy) break;

    while (true) {
      auto sem = Semester::selectSemester(sy->pSemesters);
      if (!sem) break;

      while (true) {
        auto crs = selectCourse(sem->pCourses);
        if (!crs) break;

        while (true) {
          clearScreen();

          cout << "Course " << crs->course_code << " - ";
          cout << crs->course_name << " - ";
          cout << Semester::ORD2STR[crs->pSemester->semester_ordinal] << ' ';
          cout << crs->pSemester->pSchoolYear->name << '\n';
          cout << "Lecturer: " << crs->lecturer << '\n';
          cout << "Number of students: " << crs->pStudents.size() << "/" << crs->maxNumberOfStudents << " students\n";
          cout << "Number of credits: " << crs->numberOfCredits << '\n';
          cout << "Start date: " << crs->start_date << '\n';
          cout << "End date: " << crs->end_date << '\n';
          cout << "Schedule:\n";
          cout << "  First session: " << crs->schedule[0] << '\n';
          cout << "  Second session: " << crs->schedule[1] << '\n';
          cout << '\n';

          int cmd;
          cout << "1. View students\n";
          cout << "2. View scoreboard\n";
          cout << "3. Edit student score\n";
          cout << "4. Export scoreboard to CSV\n";
          cout << "5. Import scoreboard from CSV\n";
          cout << "6. Edit course information\n";
          cout << "7. Delete course\n";
          cout << "0. Go Back\n";
          cout << "Please select one: ";
          cin >> cmd;

          if (cmd == 0 || (cmd == 7 && deleteCourse(crs))) break;
          switch (cmd) {
            case 1:
              Student::selectStudent(crs->pStudents, true);
              break;
            case 2:
              crs->viewScoreboard();
              break;
            case 3:
              crs->editScoreboard();
              break;
            case 4:
              crs->exportScoreboard();
              break;
            case 5:
              crs->importScoreboard();
              break;
            case 6:
              crs->editCourse();
              break;
            default:
              cout << "Invalid choice\n";
              break;
          }
        }
      }
    }
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

void Course::viewScoreboard() {
  clearScreen();

  for (auto st : pStudents) {
    cout << st->firstName << ' ';
    cout << st->lastName << ' ';
    int i = st->pEnrolledCourses.find(this);
    auto score = st->pCourseScores[i];
    cout << score.midtermMark << ' ';
    cout << score.finalMark << ' ';
    cout << score.otherMark << ' ';
    cout << score.totalMark << '\n';
  }

  waitForEnter();
}

void Course::editScoreboard() {
  while (true) {
    auto st = Student::selectStudent(pStudents);
    if (!st) break;

    clearScreen();

    int i = st->pEnrolledCourses.find(this);
    auto &score = st->pCourseScores[i];

    cout << "Current score:\n";
    cout << "  Midterm Mark: " << score.midtermMark << '\n';
    cout << "  Final Mark: " << score.finalMark << '\n';
    cout << "  Other Mark: " << score.otherMark << '\n';
    cout << "  Total Mark: " << score.totalMark << '\n';
    cout << '\n';

    cout << "Please enter new score\n";
    cout << "  Midterm Mark: ";
    cin >> score.midtermMark;
    cout << "  Final Mark: ";
    cin >> score.finalMark;
    cout << "  Other Mark: ";
    cin >> score.otherMark;
    cout << "  Total Mark: ";
    cin >> score.totalMark;
  }
}

void Course::exportScoreboard() {
  clearScreen();

  string csvPath;
  cout << "Please enter CSV file path: ";
  cin.ignore();
  getline(cin, csvPath);

  ofstream fCSV(csvPath);
  if (!fCSV.is_open()) {
    cout << "Could not open CSV file\n";
    milliSleep(1000);
    return;
  }

  // write header
  fCSV << CSVParser::writeArgsToLine("Student ID",
                                     "Full Name",
                                     "Gender",
                                     "Class ID",
                                     "Midterm Mark",
                                     "Final Mark",
                                     "Other Mark",
                                     "Total Mark")
       << '\n';

  for (auto st : pStudents) {
    int i = st->pEnrolledCourses.find(this);
    auto score = st->pCourseScores[i];
    fCSV << CSVParser::writeArgsToLine(st->student_id,
                                       st->firstName + " " + st->lastName,
                                       st->gender,
                                       st->pClass->class_id,
                                       score.midtermMark,
                                       score.finalMark,
                                       score.otherMark,
                                       score.totalMark)
         << '\n';
  }

  fCSV.close();

  cout << "Course scoreboard has been exported to " << csvPath << '\n';
  waitForEnter();
}

void Course::importScoreboard() {
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

    string student_id, fullname, gender, class_id;
    double midtermMark, finalMark, otherMark, totalMark;

    auto res = CSVParser::parseLineToArgs(line,
                                          student_id,
                                          fullname,
                                          gender,
                                          class_id,
                                          midtermMark,
                                          finalMark,
                                          otherMark,
                                          totalMark);
    if (res != CSVParser::ParseError::Success) {
      continue;
    }

    for (auto st : pStudents) {
      if (st->student_id == student_id) {
        int i = st->pEnrolledCourses.find(this);
        auto &score = st->pCourseScores[i];
        score.midtermMark = midtermMark;
        score.finalMark = finalMark;
        score.otherMark = otherMark;
        score.totalMark = totalMark;
        ++success;
        break;
      }
    }
  }

  fCSV.close();

  cout << "Imported scores for " << success << "/" << total << " students\n\n";

  waitForEnter();
}

void Course::editCourse() {
  while (true) {
    clearScreen();

    cout << "Course " << course_code << " - ";
    cout << course_name << " - ";
    cout << Semester::ORD2STR[pSemester->semester_ordinal] << ' ';
    cout << pSemester->pSchoolYear->name << '\n';
    cout << "Lecturer: " << lecturer << '\n';
    cout << "Number of students: " << pStudents.size() << "/" << maxNumberOfStudents << " students\n";
    cout << "Number of credits: " << numberOfCredits << '\n';
    cout << "Start date: " << start_date << '\n';
    cout << "End date: " << end_date << '\n';
    cout << "Schedule:\n";
    cout << "  First session: " << schedule[0] << '\n';
    cout << "  Second session: " << schedule[1] << '\n';
    cout << '\n';

    int cmd;
    cout << "1. Edit course name\n";
    cout << "2. Edit lecturer\n";
    cout << "3. Edit number of credits\n";
    cout << "4. Edit start date\n";
    cout << "5. Edit end date\n";
    cout << "0. Go Back\n";
    cout << "Please choose one: ";
    cin >> cmd;

    if (cmd == 0) break;
    switch (cmd) {
      case 1:
        clearScreen();
        cout << "Please enter new course name: ";
        cin.ignore();
        getline(cin, course_name);
        break;
      case 2:
        clearScreen();
        cout << "Please enter new lecturer: ";
        cin.ignore();
        getline(cin, lecturer);
        break;
      case 3:
        clearScreen();
        cout << "Please enter new number of credits: ";
        cin >> numberOfCredits;
        cin.ignore();
        break;
      case 4:
        clearScreen();
        cout << "Please enter new start date: ";
        cin.ignore();
        getline(cin, start_date);
        break;
      case 5:
        clearScreen();
        cout << "Please enter new end date: ";
        cin.ignore();
        getline(cin, end_date);
        break;
      default:
        cout << "Invalid choice\n";
        break;
    }
  }
}

bool Course::deleteCourse(Course *crs) {
  clearScreen();

  cout << "Type 'yes' to confirm deleteing course ";
  cout << crs->course_code << " - ";
  cout << Semester::ORD2STR[crs->pSemester->semester_ordinal] << ' ';
  cout << crs->pSemester->pSchoolYear->name << '\n';

  string cmd;
  cin.ignore();
  getline(cin, cmd);

  if (cmd == "yes") {
    for (auto st : crs->pStudents) {
      int i = st->pEnrolledCourses.find(crs);
      st->pEnrolledCourses.erase(i);
      st->pCourseScores.erase(i);
    }
    crs->pSemester->pCourses.erase(crs);
    all_course.erase(crs);
    delete crs;
    cout << "Course deleted\n";
    waitForEnter();
    return true;
  } else {
    cout << "This course will not be deleted\n";
    milliSleep(1000);
    return false;
  }
}

void Course::loadFromStream(std::istream &f) {
  string _course_id;
  getline(f, _course_id);
  assert(_course_id == course_id);

  getline(f, course_code);
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

  f >> maxNumberOfStudents;
  f >> numberOfCredits;
  f.ignore();

  getline(f, schedule[0]);
  getline(f, schedule[1]);
}

void Course::writeToStream(std::ostream &f) {
  f << course_id << '\n';
  f << course_code << '\n';
  f << course_name << '\n';
  f << lecturer << '\n';
  f << start_date << '\n';
  f << end_date << '\n';
  f << pSemester->semester_id << '\n';
  f << pStudents.size() << '\n';
  for (auto st : pStudents) {
    f << st->student_id << '\n';
  }
  f << maxNumberOfStudents << '\n';
  f << numberOfCredits << '\n';
  f << schedule[0] << '\n';
  f << schedule[1] << '\n';
}
