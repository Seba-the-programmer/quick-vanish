#include "qvanish.h"

void qvanish::display_splash(float time = 1) {
  if (time < 0) throw std::exception("Time cannot be less than zero");
}
void qvanish::console_log(const char* arg, int type_of_log, float duration) {
  char symbol;
  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

  switch (type_of_log) {
    case qvanish::FAULT:
      symbol = '-';
      break;
    case qvanish::SUCCESS:
      symbol = '+';
      break;
    case qvanish::INFO:
    default:
      symbol = '*';
      type_of_log = qvanish::INFO;
      break;
  }
  SetConsoleTextAttribute(hStdOut, type_of_log);
  std::cout << "[" << symbol << "] " << arg;
  std::cout << std::endl;

  SetConsoleTextAttribute(hStdOut, 0xf);

  if (duration > 0) Sleep((DWORD)duration * 1000);
}
void qvanish::console_log(std::string& arg, int type_of_log, float duration) {
  char symbol;
  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

  switch (type_of_log) {
    case qvanish::FAULT:
      symbol = '-';
      break;
    case qvanish::SUCCESS:
      symbol = '+';
      break;
    case qvanish::INFO:
    default:
      symbol = '*';
      type_of_log = qvanish::INFO;
      break;
  }
  SetConsoleTextAttribute(hStdOut, type_of_log);
  std::cout << "[" << symbol << "] " << arg;
  std::cout << std::endl;

  SetConsoleTextAttribute(hStdOut, 0xf);

  if (duration > 0) Sleep((DWORD)duration * 1000);
}
