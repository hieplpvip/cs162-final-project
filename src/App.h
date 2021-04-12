#ifndef APP_H
#define APP_H

class App {
private:
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
