/*
 * ==============================================================================
 * File: xd_ctest.h
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

#ifndef XD_CTEST_H
#define XD_CTEST_H

#include <stdio.h>

// ========================
// ANSI Colors
// ========================

#define XD_CTEST_COLOR_FG_RED "\x1b[91m"     // Red foreground
#define XD_CTEST_COLOR_FG_GREEN "\x1b[92m"   // Green foreground
#define XD_CTEST_COLOR_FG_YELLOW "\x1b[93m"  // Yellow foreground
#define XD_CTEST_COLOR_FG_BLUE "\x1b[94m"    // Blue foreground
#define XD_CTEST_COLOR_RESET "\x1b[0m"       // Reset all colors

extern unsigned int xd_tests_total;   // Total number of tests
extern unsigned int xd_tests_passed;  // Number of passed tests
extern unsigned int xd_tests_failed;  // Number of failed tests

// ========================
// Defined Types
// ========================

/**
 * @brief Signature for test functions.
 *
 * @return `0` on success, `1` on failure.
 */
typedef int (*xd_test_func)();

/**
 * @brief Represents a test case.
 */
typedef struct xd_test_case {
  const char *func_name;  // Test name (function name)
  xd_test_func func;      // Pointer to the test function
} xd_test_case;

// ========================
// Functions
// ========================

/**
 * @brief Performs an assertion.
 *
 * @param condition The assertion condition.
 * @param file The file where this function was used.
 * @param line The line number where this function was used.
 * @param condition_string The assertion condition (as string).
 *
 * @return `0` on success (passed assertion), `1` on failure.
 */
int xd_test_assert(int condition, const char *file, int line,
                   const char *condition_string);

/**
 * @brief Runs a test function.
 *
 * @param func A pointer to the test function.
 * @param name The name of the test function.
 */
void xd_test_run(xd_test_func func, const char *name);

/**
 * @brief Prints the tests summary.
 *
 * @return `0` if all tests were passed, `1` otherwise.
 */
int xd_test_summary();

// ========================
// Macros
// ========================

/**
 * @brief Expands the passed function pointer to `{func_name, func}`, used
 * as shorthand when creating `xd_test_case` structures.
 */
#define XD_TEST_CASE(func) {#func, func}

/**
 * @brief Initializes the test result variable.
 *
 * Place this macro at the start of every test function.
 */
#define XD_TEST_START int xd_test_result = 0;

/**
 * @brief Returns the final result of the test.
 *
 * Place this macro at the end of each test function.
 */
#define XD_TEST_END return xd_test_result;

/**
 * @brief Asserts if a condition is true, if not jumps to `xd_test_failed`
 * label.
 */
#define XD_TEST_ASSERT(condition)                                           \
  do {                                                                      \
    if (xd_test_assert((int)(condition), __FILE__, __LINE__, #condition) != \
        0) {                                                                \
      xd_test_result = 1;                                                   \
      goto xd_test_failed;                                                  \
    }                                                                       \
  } while (0);

#endif  // XD_CTEST_H
