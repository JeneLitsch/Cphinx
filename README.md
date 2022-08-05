# Cphinx
Cphinx is a minimalistic header only unit test framewort for C++.

## How to use

First a `cphinx::cphinx` object must be created.

This object provides the `.run(callable, name)` member function.
- The first parameter is the test we want to run.
- The second parameter is the name which will be displayed in the test results.

A test is a function that takes a `cphinx::validator &` and returns `void`.

The validator provides a couple functions to check test results.

- The member function `.assert_equal(got, expected, error)` can be used to compare a result to an expected value.
- The member function `.assert_true(boolean)` and `.assert_false(boolean)` can used check `bool` result more easily.

The error messages are optional and can be omitted. A default is provided.

After all test are run the `.dignostics(std::ostream &)` member function must be called to get the result. 


### Full Example

```cpp
#include "cphinx/cphinx.hxx"
#include <iostream>

int add(int a, int b) {
	return a + b;
}

void simple_test(cphinx::validator & validator) {
	validator.assert_equal(add(1, 3), 4, "Addition failed"); // Pass
	validator.assert_false(false, "Wrong boolean"); // Pass
	validator.assert_true(true); // Pass
}

void failing_test(cphinx::validator & validator) {
	validator.assert_true(false); // Fail
}

int main() {
	cphinx::cphinx framework;
	framework.run(simple_test, "Simple test");
	framework.run(failing_test, "Failing test");
	framework.dignostics(std::cout);
	return 0;
}
```

If we compile and run the code we get this output.

```
=== Test diagnostics ===

Test: Simple test -> Successful!

Test: Failing test -> Failed!
[ERROR] Expected true. 

=== Test conclusion ===

test: 2
cases: 4
errors: 1
ERRORS FOUND!!!
```