#include "qvanish.h"

#include <filesystem>

namespace fs = std::filesystem;

void render_splash(const std::string&) noexcept;
void DeleteAllFiles(const std::string&);

void qvanish::display_splash(std::string&& app_name, float time = 1) {
  if (time < 0) throw std::exception("Time cannot be less than zero");

  render_splash(app_name);

  for (int i = 0; i < (time * 1000); i += REFRESH_RATE_MS) {
    if (GetAsyncKeyState(VK_SPACE)) break;
    Sleep(REFRESH_RATE_MS);
  }
}

void qvanish::clean(std::unique_ptr<DataLoader>& data) {
  qvanish::console_log("Cleaner initialized", INFO, 0.5f);
  qvanish::console_log("Proceeding to delete files...", INFO, 1.0f);

  auto del_file = [](const std::string& file) {
    qvanish::console_log("Searching for: " + file, INFO, 0.3f);
    if (fs::remove(file)) {
      qvanish::console_log("File successfully deleted", SUCCESS, 1);
      return;
    }
    qvanish::console_log(file + " could not be deleted", FAULT, 1);
  };

  del_file(data->get_data("file1").data());
  del_file(data->get_data("file2").data());
  del_file(data->get_data("file3").data());

  qvanish::console_log("No more single files to delete", INFO, 0.5f);
  qvanish::console_log("Proceeding to clean up directories...", INFO, 1.0f);

  auto del_dir = [](const std::string& dir) {
    qvanish::console_log("Entering to: " + dir, INFO, 0.3f);
    if (!fs::exists(dir)) {
      qvanish::console_log("Could not open the directory", FAULT, 1.0f);
      return;
    }
    if (fs::is_empty(dir)) {
      qvanish::console_log("Directory is empty", INFO, 1.0f);
      return;
    }
    DeleteAllFiles(dir);
    return;
  };

  del_dir(data->get_data("path_citizen"));
  del_dir(data->get_data("path_prefetch"));

  del_dir(data->get_data("path_temp"));
  // bizzare problem with these paths. undefined behavior
  // del_dir(data->get_data("path_recent"));
  del_dir(data->get_data("path_history"));
}

bool qvanish::is_elevated() {
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

void DeleteAllFiles(const std::string& path) {
  WIN32_FIND_DATA wfd;
  HANDLE hFile;
  DWORD dwFileAttr;
  std::string file;
  std::string strSpec = path + "*.*";
  std::string path_file;

  // find the first file
  hFile = FindFirstFile(strSpec.c_str(), &wfd);

  if (hFile != INVALID_HANDLE_VALUE) {
    do {
      file = wfd.cFileName;
      path_file = path + file;
      // get the file attributes
      dwFileAttr = GetFileAttributes(path_file.c_str());

      // see if file is read-only : if so unset read-only
      if (dwFileAttr & FILE_ATTRIBUTE_READONLY) {
        dwFileAttr &= ~FILE_ATTRIBUTE_READONLY;
        SetFileAttributes(path_file.c_str(), dwFileAttr);
      }

      // see if the file is a directory
      if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        // make sure it isn't current or parent directory
        if (file != "." && file != "..") {
          path_file += "\\";
          // recursively delete all files in this folder
          DeleteAllFiles(path_file);
          // remove the directory

          if (RemoveDirectory(path_file.c_str())) {
            qvanish::console_log("Deleted directory: " + path_file,
                                 qvanish::SUCCESS, 0);
          } else {
            qvanish::console_log("Could not delete directory: " + path_file,
                                 qvanish::INFO, 0);
          }
        }
      } else {
        // delete the file
        if (DeleteFile(path_file.c_str())) {
          qvanish::console_log("Deleted file: " + path_file, qvanish::SUCCESS,
                               0);
        } else {
          qvanish::console_log("Could not delete file: " + path_file,
                               qvanish::INFO, 0);
        }
      }
    } while (FindNextFile(hFile, &wfd));
  } else {
  }

  FindClose(hFile);
}
