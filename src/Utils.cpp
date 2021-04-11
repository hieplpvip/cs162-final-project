#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <cstdlib>
#include "Utils.h"

void milliSleep(int milliseconds) {
#ifdef _WIN32
  Sleep(milliseconds);
#else
  usleep(milliseconds * 1000);
#endif
}

void clearScreen() {
#ifdef WINDOWS
  std::system("cls");
#else
  std::system ("clear");
#endif
}
