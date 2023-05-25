#include "qvanish.h"

void render_splash(const std::string&) noexcept;

void qvanish::display_splash(std::string&& app_name, float time = 1) {
  if (time < 0) throw std::exception("Time cannot be less than zero");

  render_splash(app_name);

  for (int i = 0; i < (time * 1000); i += REFRESH_RATE_MS) {
    if (GetAsyncKeyState(VK_SPACE)) break;
    Sleep(REFRESH_RATE_MS);
  }
}

void render_splash(const std::string& app_name) noexcept {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  const int width = std::min<int>(
      static_cast<int>(csbi.srWindow.Right - csbi.srWindow.Left + 1), 50);
  const int height =
      static_cast<int>(csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
  constexpr char symbol = '@';
  constexpr int height_denomin = 6;
  const int middle = width / 2;
  const auto half_len = app_name.length() / 2;
  // draw top rank
  for (int i = 0; i < width; i++) std::cout << symbol;
  std::cout << '\n';
  // draw first part of splash screen
  for (int y = 0; y < (height / height_denomin); y++) {
    std::cout << symbol;
    for (int x = 2; x < width; x++) std::cout << " ";
    std::cout << symbol << '\n';
  }
  // draw title

  std::cout << symbol;
  for (int x = 1; x < (middle - half_len); x++) std::cout << " ";
  std::cout << app_name;
  for (int x = 1; x < (middle - half_len); x++) std::cout << " ";
  std::cout << symbol << '\n';

  // draw second part of splash screen
  for (int y = 0; y < (height / height_denomin); y++) {
    std::cout << symbol;
    for (int x = 2; x < width; x++) std::cout << " ";
    std::cout << symbol << '\n';
  }
  // draw bottom rank
  for (int i = 0; i < width; i++) std::cout << symbol;
  std::cout << '\n';
  std::cout << "by Trynity Software 2023     " << VERSION << "\n\n\n";
}
