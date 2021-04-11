#include "App.h"
#include "Global.h"
using namespace std;

App::App() {
  clearScreen();
  cout << "Starting...\n";

  user = nullptr;
  Global::all_school_year.clear();
  Global::all_semester.clear();
  Global::all_course.clear();
  Global::all_student.clear();
  Global::all_class.clear();
  Global::all_user.clear();

  milliSleep(1000);
}

App::~App() {
  clearScreen();
  cout << "Exiting...\n";

  // free memory
  for (auto p: Global::all_school_year) {
    delete p;
  }
  for (auto p: Global::all_semester) {
    delete p;
  }
  for (auto p: Global::all_course) {
    delete p;
  }
  for (auto p: Global::all_student) {
    delete p;
  }
  for (auto p: Global::all_class) {
    delete p;
  }
  for (auto p: Global::all_user) {
    delete p;
  }

  milliSleep(1000);
}

void App::loadData() {

}

void App::saveData() {

}

bool App::authenticate() {
  user = new User();
  user->role = User::UserRole::STAFF;
  return true;
}

void App::showStaffMenu() {
  clearScreen();
  cout << "--- School Year ---\n";
  cout << "1. New school year\n";
  cout << "2. Edit school year\n";
  cout << "3. List school years\n";
  cout << "\n";

  cout << "--- Class ---\n";
  cout << "4. New class\n";
  cout << "5. Edit class\n";
  cout << "6. List classes\n";
  cout << "\n";

  cout << "--- Semester ---\n";
  cout << "7. New semester\n";
  cout << "8. Edit semester\n";
  cout << "9. List semesters\n";
  cout << "\n";

  cout << "--- Student ---\n";
  cout << "10. New student\n";
  cout << "11. Edit student\n";
  cout << "12. List student\n";
  cout << "\n";

  cout << "--- Course ---\n";
  cout << "13. New course\n";
  cout << "14. Edit course\n";
  cout << "15. List course\n";
  cout << "\n";

  milliSleep(5000);
}

void App::showStudentMenu() {
  clearScreen();
  cout << "--- School Year ---\n";
  cout << "1. List school years\n";
  cout << "\n";

  cout << "--- Class ---\n";
  cout << "2. List classes\n";
  cout << "\n";

  cout << "--- Semester ---\n";
  cout << "3. List semesters\n";
  cout << "\n";

  cout << "--- Course ---\n";
  cout << "4. List all courses\n";
  cout << "5. List enrolled courses\n";
  cout << "6. Enroll in a course\n";
  cout << "7. Unenroll from a course\n";
  cout << "\n";

  milliSleep(5000);
}

void App::run() {
  loadData();
  if (!authenticate()) {
    cout << "Could not authenticate!\n";
    goto exit;
  }
  assert(user != nullptr);

  if (user->role == User::UserRole::STAFF) {
    showStaffMenu();
  } else {
    showStudentMenu();
  }

  delete user;

exit:
  saveData();
}
