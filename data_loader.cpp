#include "data_loader.h"

void qvanish::DataLoader::load_data() noexcept {
  if (loaded_) return;

  auto load = [&](const char* friendly_name, const char* full_data) {
    data_[friendly_name] = full_data;
  };

  // here define strings to load
  load("path_cheat1", "C:\\dsadasd");
  load("path_cheat2", "C:\\dsadasd");
  load("path_cheat3", "C:\\dsadasd");

  loaded_ = true;
}
qvanish::DataLoader::DataLoader()
    : loaded_(false),
      data_({})

{}
