# PA013 Mars Rover Example in C++

The repository contains a simple Mars Rover C++ example project for demonstrating unit testing
with GoogleTest, and measuring test coverage with gcc and `gcovr`.


## Requirements

To install and play with the project, you need to have the following dependencies:

 - `gcc`
 - `cmake`
 - `gcovr`


## Installation

To install the project, simply run the `build.sh` script. This will build several executable files
in the `build/` directory:

 - `rover`: a demonstration of the rover code using the `main()` function from `src/main.cpp`.
 - `rover_tests`: a collection of all tests in a single executable.
 - `ResourceUnitTests`: a collection of simple GoogleTest tests.
 - `ResourceUnitTestsParameterized`: a collection of value-parameterized tests.
 - `ResourceUnitTestsMocks`: a collection of tests using a mock.


## Coverage

To test the coverage, navigate to the `build` directory and execute
`cmake --build . --target coverage`. This will recompile the tests with coverage enabled, execute
the tests and generate an HTML report file `coverage.html`, where you can interactively navigate
the coverage results.