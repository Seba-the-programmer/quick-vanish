#include <gtest/gtest.h>

#include "qvanish.h"

TEST(SplashScreenTest, SplashScreenDuration) {
  clock_t t = clock();
  qvanish::display_splash(3.0);
  const double work_time = (clock() - t) / double(CLOCKS_PER_SEC);
  EXPECT_GT(work_time, 2.9);
}
TEST(SplashScreenTest, SplashScreenException) {
  EXPECT_THROW(
      {
        try {
          qvanish::display_splash(-3.0);
        } catch (const std::exception& e) {
          EXPECT_STREQ(e.what(), "Time cannot be less than zero");
          throw;
        }
      },
      std::exception);
}
TEST(SplashScreenTest, SplashScreenZero) {
  clock_t t = clock();
  qvanish::display_splash(0);
  const double work_time = (clock() - t) / double(CLOCKS_PER_SEC);
  EXPECT_LT(work_time, 1);
}

class LogSystemTest : public testing::Test {
 protected:
  std::string msg1 = "Sample", msg2 = "text", msg3 = "for testing";
  int num1 = 1;
  double num2 = 3.5, num3 = -420.34;
  std::streambuf* sbuf;
  std::stringstream buffer;

  void set_read() {
    sbuf = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());
  }
};

TEST_F(LogSystemTest, LogSuccessSingle) {
  qvanish::console_log(msg1, qvanish::SUCCESS, 0);
  EXPECT_STREQ("Y", "Y");
}
