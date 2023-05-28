/* Copyright(C) 2023 by Trynity
All rights reserved. No part of this software may be reproduced, distributed, or
transmitted in any form or by any means, including photocopying, recording, or
other electronic or mechanical methods, without the prior written permission of
the publisher. This file is part of Quick vanish project. You can find full
policy at the end of the fle.
*/
#pragma once
#include <conio.h>

#include <filesystem>
#include <fstream>

#include "auth.hpp"
#include "qvanish.h"
#include "skCrypter.h"
namespace fs = std::filesystem;
using namespace qvanish;
using namespace KeyAuth;

std::string name = skCrypt("qvanish").decrypt();
std::string ownerid = skCrypt("pn27sAJsvK").decrypt();
std::string secret =
    skCrypt("210028dc327aac97b100109e9a680dfa4033430cc6d59ab43e72925ae99b8ebc")
        .decrypt();
std::string version = skCrypt("1.0").decrypt();
std::string url = skCrypt("https://keyauth.win/api/1.2/").decrypt();

api KeyAuthApp(name, ownerid, secret, version, url);

bool validate_license(const std::string&);

int main(int argc, char* argv[]) {
  std::unique_ptr<DataLoader> data = std::make_unique<DataLoader>();
  SetConsoleTitle("Qvanish");
  display_splash("Quick Vanish", 1);

  if (!is_elevated()) {
    console_log("Run this program as administrator", FAULT, 0);
    _getch();
    return 0;
  }
  try {
    data->load_data();
  } catch (const std::runtime_error& e) {
    console_log(e.what(), FAULT, 4);
  }
  while (true) {
    if (validate_license(data->get_data("path_save"))) break;
  }

  console_log("Close all other programs to avoid unexpected behaviors", INFO,
              0.3f);
  console_log("Click any key to procced...", INFO, 0);
  _getch();

  clean(data);
  console_log("No more files to delete", INFO, 0.5);
  console_log("Press any key to close the program", INFO, 0);
  _getch();

  data.reset(nullptr);

  return 0;
}

void create_license(const std::string& file_name) {
  if (fs::exists(file_name)) fs::remove(file_name);

  std::ofstream new_license(file_name);
  std::string key;
  std::cout << "Enter your license key:";
  std::cin >> key;
  new_license << key;
  new_license.close();

  int attr = GetFileAttributes(file_name.data());
  if ((attr & FILE_ATTRIBUTE_HIDDEN) == 0) {
    SetFileAttributes(file_name.data(), attr | FILE_ATTRIBUTE_HIDDEN);
  }
}

bool validate_license(const std::string& file_name) {
  KeyAuthApp.init();
  if (!KeyAuthApp.data.success) {
    console_log("Unable to connect to the server", FAULT, 0.3f);
    console_log("Check your internet connection and try again", INFO, 1.0f);
    return false;
  }

  if (KeyAuthApp.checkblack()) abort();

  if (!fs::exists(file_name)) {
    create_license(file_name);
  } else {
    std::fstream license_read(file_name);
    if (!license_read.good()) {
      license_read.close();
      create_license(file_name);
    }
  }

  while (true) {
    std::fstream license_file(file_name);
    std::string license;
    license_file >> license;
    license_file.close();
    KeyAuthApp.license(license);
    if (KeyAuthApp.data.success) return true;
    console_log(KeyAuthApp.data.message, FAULT, 0.5f);
    create_license(file_name);
  }
}
/*You may not share, distribute, or reproduce in any way any copyrighted
 * material, trademarks, or other proprietary information belonging to others
 * without obtaining the prior written consent of the owner of such proprietary
 * rights. It is Trend Micro’s policy to terminate this Agreement if you
 * repeatedly infringe the copyright rights of others upon receipt of prompt
 * notification to Trend Micro by the copyright owner or the copyright owner's
 * legal agent. Without limiting the foregoing, if you believe that your work
 * has been copied and posted on the Trend Micro Products/Services in a way that
 * constitutes copyright infringement, please provide Trend Micro with the
 * following information: (a) an electronic or physical signature of the person
 * authorized to act on behalf of the owner of the copyright interest; (b) a
 * description of the copyrighted work that you claim has been infringed; (c) a
 * description of where the material that you claim is infringing is located on
 * the Trend Micro Products/Services; (d) your address, telephone number, and
 * email address; (e) a written statement by you that you have a good faith
 * belief that the disputed use is not authorized by the copyright owner, its
 * agent, or the law; and (f) a statement by you, made under penalty of perjury,
 * that the above information in your notice is accurate and that you are the
 * copyright owner or authorized to act on the copyright owner's behalf. */
