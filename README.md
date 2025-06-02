# 🧪 XD-Ctest

Minimalist C unit testing library

---

## 🌟 Features

* Zero external dependencies (pure C).
* Single-header distribution for quick setup.
* Easy test registration via macro.
* File name and line number reporting on assertion failures.
* ANSI-colored console output for clear PASS/FAIL visibility.
* Support resource cleanup section in each test.
* Program exits with `0` if all tests pass, `1` if any test fails.

---

## ❔ Why XD-Ctest?

Unit testing in C can sometimes feel overwhelming, especially when libraries come with extensive setup, extra dependencies, or a long list of features that aren't always needed. `xd-ctest` was created to keep things simple. Many times, all you need is a basic `ASSERT`, a clean test structure, and readable output to catch bugs quickly. This library offers just enough functionality to write and run tests without unnecessary complexity.

---

## 📑 Table of Contents

1. [🚀 Getting Started](#getting-started)
2. [✍️ Writing Tests](#writing-tests)
3. [🧾 Registering Tests](#registering-tests)
4. [⚙️ Running Tests](#running-tests)
5. [🛠️ Building Test Files](#building-test-files)
6. [🖥️ Example Output](#example-output)
7. [📜 License](#license)

---

## 🚀 Getting Started<a name="getting-started"></a>

Copy the header file `xd_ctest.h` to your project, then include it in your test source files:

```c
#include "xd_ctest.h"
```

No additional installation or linking is required.

---

## ✍️ Writing Tests<a name="writing-tests"></a>

Write your tests in functions:
* Each test function must match the signature `int test_function(void)`.
* Use `XD_TEST_START` and `XD_TEST_END` to wrap your test logic.
* Use `XD_TEST_ASSERT(condition)` for assertions.
* Write your cleanup code after the `xd_test_failed:` label.

```c
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
```

---

## 🧾 Registering Tests<a name="registering-tests"></a>

Use the `XD_TEST_CASE()` macro to register the test functions in the `test_suite` array:

```c
static xd_test_case test_suite[] = {
    XD_TEST_CASE(test_example_pass),
    XD_TEST_CASE(test_example_fail)
};
```

The macro automatically captures the function pointer and its name.

---

## ⚙️ Running Tests<a name="running-tests"></a>

Use the `XD_TEST_RUN_ALL(test_suite)` macro at the end of your `main()` function to run all the registered tests.

```c
int main() {
  XD_TEST_RUN_ALL(test_suite);
}
```
The program prints each test result, then a summary.
It exits with code `0` if all tests pass or `1` if any fail.

---

## 🛠️ Building Test Files<a name="building-test-files"></a>

Compile your test source files normally:

```bash
gcc example.c -o run_tests
```

Then execute:

```bash
./run_tests
```

---

## 🖥️ Example Output<a name="example-output"></a>

The following is the output of the example test file [example.c](example.c):

```text
[TEST] Running test_example_pass
[PASS] test_example_pass
[TEST] Running test_example_fail
  [FAIL] example.c:40: *num == 3
[FAIL] test_example_fail

[SUMMARY] Passed: 1, Failed: 1, Total: 2
SOME TESTS FAILED!
```

---

## 📜 License<a name="license"></a>

This project is released under the MIT License. See [LICENSE](LICENSE) for details.
