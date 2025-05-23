/*
 * ==============================================================================
 * File: xd_ctest.c
 * Author: Duraid Maihoub
 * Date: 23 May 2025
 * Description: Part of the xd-ctest project.
 * Repository: https://github.com/xduraid/xd-ctest
 * ==============================================================================
 * Copyright (c) 2025 Duraid Maihoub
 *
 * xd-ctest is distributed under the MIT License. See the LICENSE file
 * for more information.
 * ==============================================================================
 */

#include "xd_ctest.h"

#include <stdio.h>

unsigned int xd_tests_total = 0;
unsigned int xd_tests_passed = 0;
unsigned int xd_tests_failed = 0;

int xd_test_assert(int condition, const char *file, int line,
                   const char *condition_string) {
  if (!condition) {
    printf(XD_CTEST_COLOR_FG_RED "  [FAIL] %s:%d: %s\n" XD_CTEST_COLOR_RESET,
           file, line, condition_string);
    return 1;
  }
  return 0;
}  // xd_test_assert()

void xd_test_run(xd_test_func func, const char *name) {
  printf("%s[TEST] Running %s%s\n", XD_CTEST_COLOR_FG_BLUE, name,
         XD_CTEST_COLOR_RESET);
  if (func() == 0) {
    printf("%s[PASS] %s%s\n", XD_CTEST_COLOR_FG_GREEN, name,
           XD_CTEST_COLOR_RESET);
    xd_tests_passed++;
  }
  else {
    printf("%s[FAIL] %s%s\n", XD_CTEST_COLOR_FG_RED, name,
           XD_CTEST_COLOR_RESET);
    xd_tests_failed++;
  }
}  // xd_test_run()

int xd_test_summary() {
  printf(XD_CTEST_COLOR_FG_YELLOW
         "\n[SUMMARY] Passed: %d, Failed: %d, Total: %d\n" XD_CTEST_COLOR_RESET,
         xd_tests_passed, xd_tests_failed, xd_tests_total);
  if (xd_tests_failed == 0) {
    printf("%sALL TESTS PASSED!%s\n", XD_CTEST_COLOR_FG_GREEN,
           XD_CTEST_COLOR_RESET);
    return 0;
  }
  printf("%sSOME TESTS FAILED!%s\n", XD_CTEST_COLOR_FG_RED,
         XD_CTEST_COLOR_RESET);
  return 1;
}  // xd_test_summary()
