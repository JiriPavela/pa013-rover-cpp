cmake_minimum_required(VERSION 3.15)
project(rover)

set(CMAKE_CXX_STANDARD 17)

# -----------------------
# Coverage option
# -----------------------
option(ENABLE_COVERAGE "Enable coverage reporting" ON)

if(ENABLE_COVERAGE)
    message(STATUS "Coverage enabled")
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

# -----------------------
# Main executable
# -----------------------
add_executable(rover
    src/main.cpp
    src/resource.cpp src/resource.hpp
    src/rover.cpp src/rover.hpp
    src/task.cpp src/task.hpp
)

# -----------------------
# GoogleTest
# -----------------------
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

# -----------------------
# Tests, compile them both separately and into a single executable.
# -----------------------
add_executable(ResourceUnitTests tests/resource_test.cpp src/resource.cpp src/task.cpp)
target_link_libraries(ResourceUnitTests gtest gtest_main)

add_executable(ResourceUnitTestsParameterized tests/resource_test_parameterized.cpp src/resource.cpp)
target_link_libraries(ResourceUnitTestsParameterized gtest gtest_main)

add_executable(ResourceUnitTestsMocks tests/resource_test_mock.cpp src/resource.cpp src/task.cpp)
target_link_libraries(ResourceUnitTestsMocks gtest gtest_main)

add_executable(rover_tests
    tests/resource_test.cpp
    tests/resource_test_parameterized.cpp
    tests/resource_test_mock.cpp
    src/resource.cpp
    src/task.cpp)
target_link_libraries(rover_tests gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(rover_tests)

# -----------------------
# Coverage target
# -----------------------
find_program(GCOVR gcovr)

if(GCOVR)
    add_custom_target(coverage
        COMMAND ${CMAKE_COMMAND} --build . --target rover_tests
        COMMAND ctest --output-on-failure
        COMMAND ${GCOVR}
            -r ${CMAKE_SOURCE_DIR}
            --html
            --html-details
            -o coverage.html
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running tests and generating coverage report"
    )
endif()