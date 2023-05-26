#include "data_loader.h"

void qvanish::DataLoader::load_data() {
  if (loaded_) return;

  auto load = [&](std::string friendly_name, std::string full_data) {
    data_.insert(make_pair(friendly_name, full_data));
  };

  // load current user name
  TCHAR userenv[150];
  DWORD size = 150;
  std::string path_base = "C:\\Users\\";
  if (!GetUserName((TCHAR*)userenv, &size)) {
    throw std::runtime_error("couldn't resolve user envirovment variable");
  }
  path_base += userenv;
  // here define strings to load
  load("file1", "C:\\ProgramData\\mp.exe");
  load("file2", "C:\\ProgramData\\dr.sys");
  load("file3", "C:\\ProgramData\\loader.data");
  load("path_citizen", path_base + "\\AppData\\Roaming\\CitizenFX\\");
  load("path_prefetch", "C:\\Windows\\Prefetch");
  load("path_temp", path_base + "\\AppData\\Local\\Temp\\");
  load("path_recent", path_base + "\\Recent\\");
  load("path_history",
       path_base + "\\AppData\\Local\\Microsoft\\Windows\\History\\");
  load("ext", ".cth");

  loaded_ = true;
}

qvanish::DataLoader::DataLoader()
    : loaded_(false),
      data_({})

{}
