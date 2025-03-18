project(Google_tests)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(ResourceUnitTests resource_test.cpp ../src/resource.cpp)
target_link_libraries(ResourceUnitTests gtest gtest_main)

add_executable(ResourceUnitTestsParameterized resource_test_parameterized.cpp ../src/resource.cpp)
target_link_libraries(ResourceUnitTestsParameterized gtest gtest_main)

add_executable(ResourceUnitTestsMocks resource_test_mock.cpp ../src/resource.cpp ../src/task.cpp)
target_link_libraries(ResourceUnitTestsMocks gtest gtest_main)