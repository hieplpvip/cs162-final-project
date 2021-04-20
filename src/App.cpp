#include "App.h"
#include "Constants.h"
#include "Global.h"

using namespace std;

App::App() {
  clearScreen();
  cout << "Starting...\n";

  current_user = nullptr;
  current_semester = nullptr;
  all_school_year.clear();
  all_semester.clear();
  all_course.clear();
  all_student.clear();
  all_class.clear();
  all_user.clear();

  courseRegistrationOpen = false;

  milliSleep(500);
}

App::~App() {
  clearScreen();
  cout << "Exiting...\n";

  // free memory
  for (auto p : all_school_year) {
    delete p;
  }
  for (auto p : all_semester) {
    delete p;
  }
  for (auto p : all_course) {
    delete p;
  }
  for (auto p : all_student) {
    delete p;
  }
  for (auto p : all_class) {
    delete p;
  }
  for (auto p : all_user) {
    delete p;
  }

  milliSleep(500);
}

void App::loadData() {
  ifstream fIn;

  auto loadIDs = [&]<typename T>(const string file, Vector<T*>& v) {
    fIn.open(file + "list.txt");
    if (!fIn.is_open()) return;

    string id;
    while (fIn >> id) {
      T* t = new T(id);
      v.push_back(t);
    }
    fIn.close();
  };

  auto loadContent = [&]<typename T>(const string dir, Vector<T*>& v) {
    for (auto p : v) {
      fIn.open(dir + p->getID() + ".txt");
      if (!fIn.is_open()) continue;

      p->loadFromStream(fIn);
      fIn.close();
    }
  };

  loadIDs(Constants::CLASS_DIR, all_class);
  loadIDs(Constants::COURSE_DIR, all_course);
  loadIDs(Constants::SCHOOL_YEAR_DIR, all_school_year);
  loadIDs(Constants::SEMESTER_DIR, all_semester);
  loadIDs(Constants::STUDENT_DIR, all_student);
  loadIDs(Constants::USER_DIR, all_user);

  loadContent(Constants::CLASS_DIR, all_class);
  loadContent(Constants::COURSE_DIR, all_course);
  loadContent(Constants::SCHOOL_YEAR_DIR, all_school_year);
  loadContent(Constants::SEMESTER_DIR, all_semester);
  loadContent(Constants::STUDENT_DIR, all_student);
  loadContent(Constants::USER_DIR, all_user);

  fIn.open(Constants::DATA_DIR + "app.txt");
  if (fIn.is_open()) {
    string current_semester_id;
    getline(fIn, current_semester_id);
    current_semester = nullptr;
    for (auto sem : all_semester) {
      if (sem->semester_id == current_semester_id) {
        current_semester = sem;
        break;
      }
    }
    fIn >> courseRegistrationOpen;
    fIn.ignore();
    fIn.close();
  }
}

void App::saveData() {
  ofstream fOut;

  auto saveIDs = [&]<typename T>(const string file, Vector<T*>& v) {
    fOut.open(file + "list.txt");
    if (!fOut.is_open()) return;

    for (auto p : v) {
      fOut << p->getID() << '\n';
    }
    fOut.close();
  };

  auto saveContent = [&]<typename T>(const string dir, Vector<T*>& v) {
    for (auto p : v) {
      fOut.open(dir + p->getID() + ".txt");
      if (!fOut.is_open()) continue;

      p->writeToStream(fOut);
      fOut.close();
    }
  };

  saveIDs(Constants::CLASS_DIR, all_class);
  saveIDs(Constants::COURSE_DIR, all_course);
  saveIDs(Constants::SCHOOL_YEAR_DIR, all_school_year);
  saveIDs(Constants::SEMESTER_DIR, all_semester);
  saveIDs(Constants::STUDENT_DIR, all_student);
  saveIDs(Constants::USER_DIR, all_user);

  saveContent(Constants::CLASS_DIR, all_class);
  saveContent(Constants::COURSE_DIR, all_course);
  saveContent(Constants::SCHOOL_YEAR_DIR, all_school_year);
  saveContent(Constants::SEMESTER_DIR, all_semester);
  saveContent(Constants::STUDENT_DIR, all_student);
  saveContent(Constants::USER_DIR, all_user);

  fOut.open(Constants::DATA_DIR + "app.txt");
  if (fOut.is_open()) {
    if (current_semester != nullptr) {
      fOut << current_semester->semester_id << '\n';
    } else {
      fOut << "null\n";
    }
    fOut << courseRegistrationOpen << '\n';
    fOut.close();
  }
}

bool App::authenticate() {
  for (int attempt = 1; attempt <= 5; ++attempt) {
    clearScreen();

    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    for (auto p : all_user) {
      if (p->username == username && p->password == password) {
        current_user = p;
        return true;
      }
    }

    cout << "Invalid credential!\n";
    milliSleep(2000);
  }

  return false;
}

void App::showMenu(const FunctionRecord menu[], int num) {
  while (true) {
    clearScreen();
    printHeader();

    int cnt_options = 0;

    for (int i = 0; i < num; ++i) {
      if (menu[i].is_section_header) {
        if (i != 0) {
          cout << '\n';
        }
        cout << "--- " << menu[i].title << " ---\n";
      } else {
        cout << ++cnt_options << ". " << menu[i].title << '\n';
      }
    }

    cout << '\n';
    cout << "0. Quit\n\n";

    cout << "Please choose an option: ";
    int option;
    cin >> option;
    if (option < 0 || option > cnt_options) {
      cout << "Invalid option!\n";
      continue;
    }

    if (option == 0) {
      // quit
      break;
    }

    for (int i = 0; i < num; ++i) {
      if (menu[i].is_section_header) {
        continue;
      }
      if (--option == 0) {
        menu[i].function();
      }
    }
  }
}

void App::run() {
  loadData();

  if (!authenticate()) {
    cout << "Could not authenticate!\n";
    return;
  }
  assert(current_user != nullptr);

  if (current_user->role == User::UserRole::STAFF) {
    showMenu(STAFF_MENU, NUM_STAFF_MENU);
  } else {
    showMenu(STUDENT_MENU, NUM_STUDENT_MENU);
  }

  saveData();
}
