/* Copyright(C) 2023 by Trynity
All rights reserved. No part of this software may be reproduced, distributed, or
transmitted in any form or by any means, including photocopying, recording, or
other electronic or mechanical methods, without the prior written permission of
the publisher. This file is part of Quick vanish project. You can find full
policy at the end of the fle.
*/
#pragma once
#include <conio.h>

#include "qvanish.h"

using namespace qvanish;

int main(int argc, char* argv[]) {
  std::unique_ptr<DataLoader> data = std::make_unique<DataLoader>();
  SetConsoleTitle("Qvanish");
  display_splash("Quick Vanish", 1);

  if (!is_elevated()) {
    console_log("Run this program as administrator", FAULT, 1);
    return 0;
  }
  // TODO: add keyauth

  try {
    data->load_data();
  } catch (const std::runtime_error& e) {
    console_log(e.what(), FAULT, 4);
  }
  console_log("Close all other programs to avoid unexpected errors", INFO, 0);
  console_log("Click any key to procced...", INFO, 0);
  _getch();

  clean(data);
  console_log("No more files to delete", INFO, 0.5);
  console_log("Press any key to close the program", INFO, 0);
  _getch();

  data.reset(nullptr);

  return 0;
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
