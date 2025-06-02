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

#include <stdlib.h>

#include "xd_ctest.h"

// Create test functions

int test_example_pass() {
  XD_TEST_START;

  XD_TEST_ASSERT(1 == 1);
  XD_TEST_ASSERT(5 > 3);

xd_test_failed:
  // Optional: test cleanup code

  XD_TEST_END;
}

int test_example_fail() {
  XD_TEST_START;

  int *num = (int *)malloc(sizeof(int));
  *num = 2;

  XD_TEST_ASSERT(*num == 3);  // Will fail and jump to cleanup
  XD_TEST_ASSERT(*num == 2);

xd_test_failed:
  free(num);  // test cleanup

  XD_TEST_END;
}

// Register test functions

static xd_test_case test_suite[] = {XD_TEST_CASE(test_example_pass),
                                    XD_TEST_CASE(test_example_fail)};

// Run tests (Don't modify)
int main() {
  XD_TEST_RUN_ALL(test_suite);
}
