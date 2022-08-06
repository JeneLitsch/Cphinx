# Cphinx
Cphinx is a minimalistic header only unit test framewort for C++.

## How to use

Tests can be run automatically. Just declare a test like this.
```cpp
CPHINX_TEST(name) {
	// test code goes her
}
```

A validator is passed to each test.
The validator provides a couple functions to check test results.

- The member function `.assert_equal(got, expected, error)` can be used to compare a result to an expected value.
- The member function `.assert_true(boolean)` and `.assert_false(boolean)` can used check `bool` result more easily.

After the program leaves main() the results are printed.