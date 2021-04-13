#ifdef _WIN32
#include <Windows.h>
#else
#include <iostream>
#include <unistd.h>
#endif
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
  std::cout << "\033[2J";
  std::cout << "\033[H";
#endif
}
