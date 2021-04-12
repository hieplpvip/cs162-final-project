#ifndef APP_H
#define APP_H

#include "Menu.h"

class App {
private:
  void loadData();
  void saveData();
  bool authenticate();
  void showMenu(const FunctionRecord menu[], int num);

public:
  App();
  ~App();
  void run();
};

#endif
