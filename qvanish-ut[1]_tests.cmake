add_test([=[HelloTest.BasicAssertions]=]  D:/Projects/CPP/quick-vanish/Debug/qvanish-ut.exe [==[--gtest_filter=HelloTest.BasicAssertions]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HelloTest.BasicAssertions]=]  PROPERTIES WORKING_DIRECTORY D:/Projects/CPP/quick-vanish SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  qvanish-ut_TESTS HelloTest.BasicAssertions)
