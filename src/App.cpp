#include "App.h"
#include "Global.h"

using namespace std;

App::App() {
  clearScreen();
  cout << "Starting...\n";

  Global::current_user = nullptr;
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
  for (auto p : Global::all_school_year) {
    delete p;
  }
  for (auto p : Global::all_semester) {
    delete p;
  }
  for (auto p : Global::all_course) {
    delete p;
  }
  for (auto p : Global::all_student) {
    delete p;
  }
  for (auto p : Global::all_class) {
    delete p;
  }
  for (auto p : Global::all_user) {
    delete p;
  }

  milliSleep(1000);
}

void App::loadData() {
  ifstream fIn;
  ofstream fOut;

  auto loadIDs = [&]<typename T>(const string file, Vector<T*>& v) {
    fIn.open(file);
    string id;
    while (fIn >> id) {
      T* t = new T(id);
      v.push_back(t);
    }
    fIn.close();
  };

  auto loadContent = [&]<typename T>(const string dir, Vector<T*>& v) {
    for (auto p : v) {
      fIn.open(dir + "/" + p->getID());
      p->loadFromStream(fIn);
      fIn.close();
    }
  };

  loadIDs("data/class/list.txt", Global::all_class);
  loadIDs("data/course/list.txt", Global::all_course);
  loadIDs("data/schoolyear/list.txt", Global::all_school_year);
  loadIDs("data/semester/list.txt", Global::all_semester);
  loadIDs("data/student/list.txt", Global::all_student);
  loadIDs("data/user/list.txt", Global::all_user);

  loadContent("data/class", Global::all_class);
  loadContent("data/course", Global::all_course);
  loadContent("data/schoolyear", Global::all_school_year);
  loadContent("data/semester", Global::all_semester);
  loadContent("data/student", Global::all_student);
  loadContent("data/user", Global::all_user);
}

void App::saveData() {
}

bool App::authenticate() {
  Global::current_user = new User();
  Global::current_user->role = User::UserRole::STAFF;
  return true;
}

void App::showMenu(const FunctionRecord menu[], int num) {
  while (true) {
    clearScreen();

    int cnt_options = 0;

    for (int i = 0; i < num; ++i) {
      if (menu[i].is_section_header) {
        if (i != 0) {
          cout << "\n";
        }
        cout << "--- " << menu[i].title << " ---\n";
      } else {
        cout << ++cnt_options << ". " << menu[i].title << "\n";
      }
    }

    cout << "\n";
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
    goto exit;
  }
  assert(Global::current_user != nullptr);

  if (Global::current_user->role == User::UserRole::STAFF) {
    showMenu(STAFF_MENU, NUM_STAFF_MENU);
  } else {
    showMenu(STUDENT_MENU, NUM_STUDENT_MENU);
  }

  delete Global::current_user;

exit:
  saveData();
}
