#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include <limits>
#include "Global.h"
#include "Utils.h"

using namespace std;

void milliSleep(int milliseconds) {
#ifdef _WIN32
  Sleep(milliseconds);
#else
  usleep(milliseconds * 1000);
#endif
}

void clearScreen() {
#ifdef _WIN32
  HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD topLeft = {0, 0};
  DWORD dwCount, dwSize;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(hOutput, &csbi);
  dwSize = csbi.dwSize.X * csbi.dwSize.Y;
  FillConsoleOutputCharacter(hOutput, 0x20, dwSize, topLeft, &dwCount);
  FillConsoleOutputAttribute(hOutput, 0x07, dwSize, topLeft, &dwCount);
  SetConsoleCursorPosition(hOutput, topLeft);
#else
  cout << "\033[2J";
  cout << "\033[H";
#endif
}

void printHeader() {
  cout << "Logged in as " << current_user->username << "\n";
  if (current_semester != nullptr) {
    cout << "Current semester: ";
    cout << Semester::ORD2STR[current_semester->semester_ordinal] << ' ';
    cout << current_semester->pSchoolYear->name << '\n';
  }
  cout << "\n";
}

void waitForEnter() {
  // https://www.daniweb.com/programming/software-development/threads/90228/flushing-the-input-stream
#pragma push_macro("max")
#undef max
  if (cin.rdbuf()->sungetc() != std::char_traits<char>::eof() && cin.get() != '\n') {
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  cout << "Press Enter to continue...";
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
#pragma pop_macro("max")
}
