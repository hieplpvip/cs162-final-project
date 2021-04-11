#include <iostream>
#include "App.h"
#include "Global.h"
using namespace std;

App::App() {
  loadData();
}

App::~App() {
  cout << "Exiting...\n";
}

void App::loadData() {

}

void App::run() {
  cout << "hello world\n";
}
