#include <gtest/gtest.h>

#include "qvanish.hpp"

TEST(SplashScreenTest, SplashScreenSkipTest) {
  qvanish::Cleaner* screen = new qvanish::Cleaner();
  INPUT in{};
  clock_t t = clock();
  in.ki.wVk = VK_SPACE;
  SendInput(1, &in, sizeof(INPUT));

  const double work_time = (clock() - t) / double(CLOCKS_PER_SEC);
  EXPECT_LT(work_time, 1);
  delete screen;
}
TEST(SplashScreenTest, SplashScreenNormalTest) {
  qvanish::Cleaner* screen = new qvanish::Cleaner();
  clock_t t = clock();
  screen->run_splash_screen(3);
  const double work_time = (clock() - t) / double(CLOCKS_PER_SEC);
  EXPECT_GT(work_time, 3);
  delete screen;
}
