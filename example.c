/*
 * ==============================================================================
 * File: example.c
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

#include <stddef.h>

#include "xd_ctest.h"

// Create test functions

int test_example_pass() {
  XD_TEST_START;

  XD_TEST_ASSERT(1 == 1);
  XD_TEST_ASSERT(5 > 3);

xd_test_failed:
  // Optional: Free resources or reset state

  XD_TEST_END;
}

int test_example_fail() {
  XD_TEST_START;

  XD_TEST_ASSERT(2 + 2 == 5);  // Will fail and jump to cleanup
  XD_TEST_ASSERT(1 == 1);

xd_test_failed:
  // Optional cleanup here

  XD_TEST_END;
}

// Register test functions

static xd_test_case test_suite[] = {XD_TEST_CASE(test_example_pass),
                                    XD_TEST_CASE(test_example_fail)};

// Run tests (Don't modify)
int main() {
  xd_tests_total = sizeof(test_suite) / sizeof(test_suite[0]);

  // Run all registered tests
  for (size_t i = 0; i < xd_tests_total; i++) {
    xd_test_run(test_suite[i].func, test_suite[i].func_name);
  }

  return xd_test_summary();
}
