# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name and C++ standard
project(net_recon_tests VERSION 1.0 LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable testing
enable_testing()

# Include GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

# Add test executable
add_executable(net_recon_tests
    src/test_tcp.cpp # Your test source file
    src/test_write_results.cpp
    src/integrated_test.cpp
)

set_target_properties(net_recon_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test
)


# Include the source headers for testing
target_include_directories(net_recon_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Link test executable to the main library and GoogleTest
target_link_libraries(net_recon_tests PRIVATE gtest gtest_main pthread scan_lib)

# Define the tests
add_test(NAME ScanTestSuite COMMAND net_recon_tests)
