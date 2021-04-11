#ifndef APP_H
#define APP_H

#include "User.h"

class App {
private:
  User* user;

  void loadData();
  void saveData();
  bool authenticate();
  void showStaffMenu();
  void showStudentMenu();

public:
  App();
  ~App();
  void run();
};

#endif
