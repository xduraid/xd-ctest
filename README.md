# XD-CTEST

**Minimalist C Unit Testing Library**

`xd-ctest` is a lightweight, header-only unit testing library written in pure C. It has no external dependencies, offering a simple interface and ANSI-colored output for fast integration into small to medium C projects.

---

## Features

* Zero external dependencies (pure C).
* Single-header distribution for quick setup.
* Easy test registration via macro.
* File name and line number reporting on assertion failures.
* ANSI-colored console output for clear PASS/FAIL visibility.
* Built-in cleanup mechanism using `goto`.
* Program exits with `0` if all tests pass, `1` if any test fails.

---

## Table of Contents

1. [Getting Started](#getting-started)
2. [Writing Tests](#writing-tests)
3. [Registering Tests](#registering-tests)
4. [Running Tests](#running-tests)
5. [Example Output](#example-output)
6. [Building](#building)
7. [License](#license)

---

## Getting Started

Include the header in your test source file:

```c
#include "xd_ctest.h"
```

No additional installation is required.

---

## Writing Tests

* Each test function must match the signature `int test_function(void)`.
* Use `XD_TEST_START` and `XD_TEST_END` to wrap your test logic.
* Use `XD_TEST_ASSERT(condition)` for assertions.
* Place any resource deallocation after the `xd_test_failed:` label.

```c
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

    XD_TEST_ASSERT(2 + 2 == 5);  // Will fail and jump to xd_test_failed
    XD_TEST_ASSERT(1 == 1);

xd_test_failed:
    // Optional cleanup here

    XD_TEST_END;
}
```

---

## Registering Tests

Use the `XD_TEST_CASE()` macro to register the test functions in the `test_suite` array:

```c
static xd_test_case test_suite[] = {
    XD_TEST_CASE(test_example_pass),
    XD_TEST_CASE(test_example_fail)
};
```

The macro automatically captures the function pointer and its name.

---

## Running Tests

The following `main()` function drives the test suite.
**Do not modify it**, as it relies on global variables used by the library:

```c
int main() {
    xd_tests_total = sizeof(test_suite) / sizeof(test_suite[0]);

    // Run all registered tests
    for (size_t i = 0; i < xd_tests_total; i++) {
        xd_test_run(test_suite[i].func, test_suite[i].func_name);
    }

    return xd_test_summary();
}
```
The program prints each test result, then a summary.
It exits with code `0` if all tests pass or `1` if any fail.

For a complete working example, see: [example.c](example.c)

---

## Example Output

```text
[TEST] Running test_example_pass
[PASS] test_example_pass
[TEST] Running test_example_fail
  [FAIL] example.c:37: 2 + 2 == 5
[FAIL] test_example_fail

[SUMMARY] Passed: 1, Failed: 1, Total: 2
SOME TESTS FAILED!
```

---

## Building

Compile your tests by linking `xd_ctest.c` with your test suite:

```bash
gcc xd_ctest.c example.c -o run_tests
```

Then execute:

```bash
./run_tests
```

---

## License

This project is released under the MIT License. See [LICENSE](LICENSE) for details.
