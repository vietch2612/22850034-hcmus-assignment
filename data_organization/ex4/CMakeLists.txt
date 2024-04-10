# Prject name: VIQR_UTF8
# Author: Cao Hoai Viet (Ross)
# MSSV: 22850034

# CMakeLists.txt
# This is the main CMake configuration file for VIQR_UTF8 project.
# It is used to configure the project and generate the build system.

 # Set the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Set your project name and version
project(VIQR_UTF8 VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Create a library from the VIQR_UTF8 source
add_library(VIQR_UTF8_Lib VIQR_UTF8.cpp FileProcessor.cpp)  # This creates a library named VIQR_UTF8_Lib from VIQR_UTF8.cpp

# Create the main executable
add_executable(VIQR_UTF8 main.cpp)

# Link the VIQR_UTF8_Lib library with the VIQR_UTF8 executable
target_link_libraries(VIQR_UTF8 VIQR_UTF8_Lib)

# Enable testing functionalities
enable_testing()

# Add an executable for the tests
add_executable(VIQR_UTF8_Test VIQR_UTF8_test.cpp FileProcessor_test.cpp)

# Link the test executable with GoogleTest and the VIQR_UTF8_Lib library it tests
target_link_libraries(VIQR_UTF8_Test gtest_main VIQR_UTF8_Lib)

# Include GoogleTest's functionalities
include(GoogleTest)

# Discover tests automatically. This allows CTest to automatically discover tests.
gtest_discover_tests(VIQR_UTF8_Test)