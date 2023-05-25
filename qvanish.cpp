#include "qvanish.h"

void qvanish::display_splash(std::string&& app_name, float time = 1) {
  if (time < 0) throw std::exception("Time cannot be less than zero");

  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  const int width = (int)(csbi.srWindow.Right - csbi.srWindow.Left + 1);
  const int height = (int)(csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
  const char symbol = '@';

  // draw top rank
  for (int i = 0; i < width; i++) std::cout << symbol;
  std::cout << '\n';
  // draw first part of splash screen
  for (int y = 0; y < (height / 5); y++) {
    std::cout << symbol;
    for (int x = 2; x < width; x++) std::cout << " ";
    std::cout << symbol << '\n';
  }
  // draw title
  const int middle = width / 2;
  const auto half_len = app_name.length() / 2;

  std::cout << symbol;
  for (int x = 1; x < (middle - half_len); x++) std::cout << " ";
  std::cout << app_name;
  for (int x = 1; x < (middle - half_len); x++) std::cout << " ";
  std::cout << symbol << '\n';

  // draw second part of splash screen
  for (int y = 0; y < (height / 5); y++) {
    std::cout << symbol;
    for (int x = 2; x < width; x++) std::cout << " ";
    std::cout << symbol << '\n';
  }
  // draw bottom rank
  for (int i = 0; i < width; i++) std::cout << symbol;
  std::cout << '\n';
  std::cout << "by Trynity Software 2023     " << VERSION << "\n\n\n ";
}
