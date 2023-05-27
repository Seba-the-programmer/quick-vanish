/* Copyright(C) 2023 by Trynity
All rights reserved. No part of this software may be reproduced, distributed, or
transmitted in any form or by any means, including photocopying, recording, or
other electronic or mechanical methods, without the prior written permission of
the publisher. This file is part of Quick vanish project. You can find full
policy at the end of the fle.
*/
#pragma once
#ifndef __QVANISH_H__
#define __QVANISH_H__
#ifdef _DEBUG
#define LOG(x) std::cout << x << std::endl
#else
#define LOG(x) 0
#endif
#define REFRESH_RATE_MS 200
#define VERSION "v0.8.1 Flame Thrower"
#include <Windows.h>

#include <iostream>

#include "data_loader.h"

namespace qvanish {

const enum console_codes { INFO = 0xF, SUCCESS = 0xA, FAULT = 0x4 };
void display_splash(std::string&& app_name, float time);

template <typename T>
inline void console_log(T&& arg, int type_of_log, float duration = 0) {
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

  Sleep(static_cast<DWORD>(duration * 1000));
}

void clean(std::unique_ptr<DataLoader>& data);

bool is_elevated();
}  // namespace qvanish

#endif

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
