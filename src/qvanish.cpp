#include "qvanish.h"

#include <filesystem>

namespace fs = std::filesystem;

void render_splash(const std::string&) noexcept;

void qvanish::display_splash(std::string&& app_name, float time = 1) {
  if (time < 0) throw std::exception("Time cannot be less than zero");

  render_splash(app_name);

  for (int i = 0; i < (time * 1000); i += REFRESH_RATE_MS) {
    if (GetAsyncKeyState(VK_SPACE)) break;
    Sleep(REFRESH_RATE_MS);
  }
}

void qvanish::clean(std::unique_ptr<DataLoader>& data) {
  qvanish::console_log("Cleaner initialized", INFO, 0.5);
  qvanish::console_log("Proceeding to delete files...", INFO, 1);

  auto del_file = [](const char* file) {
    if (fs::remove(file)) {
      qvanish::console_log("File successfully deleted", SUCCESS, 1);
      return;
    }
    qvanish::console_log("One of the files could not be deleted", FAULT, 1);
  };

  del_file(data->get_data("file1").data());
  del_file(data->get_data("file2").data());
  del_file(data->get_data("file3").data());

  qvanish::console_log("No more single files to delete", INFO, 0.5);
  qvanish::console_log("Proceeding to clean up directories...", INFO, 1);

  auto del_dir = [](const fs::path& dir) {
    LOG(dir);
    if (!fs::exists(dir) || fs::is_empty(dir)) {
      qvanish::console_log("Couldn't open directory", FAULT, 1);
      return;
    }
    for (auto& path : fs::directory_iterator(dir)) {
      if (fs::remove_all(path)) {
        qvanish::console_log("Files in directory successfully deleted", SUCCESS,
                             1);
        return;
      }
      qvanish::console_log("Couldn't delete any files in directory", FAULT, 1);
    }
  };

  del_dir(data->get_data("path_citizen"));
  del_dir(data->get_data("path_prefetch"));

  // bizzare problem with these paths. undefined behavior
  //  del_dir(data->get_data("path_temp"));
  //  del_dir(data->get_data("path_recent"));
  del_dir(data->get_data("path_history"));
}

BOOL qvanish::is_elevated() {
  BOOL fRet = FALSE;
  HANDLE hToken = NULL;
  if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
    TOKEN_ELEVATION Elevation;
    DWORD cbSize = sizeof(TOKEN_ELEVATION);
    if (GetTokenInformation(hToken, TokenElevation, &Elevation,
                            sizeof(Elevation), &cbSize)) {
      fRet = Elevation.TokenIsElevated;
    }
  }
  if (hToken) {
    CloseHandle(hToken);
  }
  return fRet;
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
