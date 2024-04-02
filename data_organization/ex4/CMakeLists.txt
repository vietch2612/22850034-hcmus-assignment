cmake_minimum_required(VERSION 3.10)  # Set the minimum version of CMake required

# Set your project name and version
project(VIQR_UTF8 VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executable target with source files
add_executable(VIQR_UTF8 main.cpp VIQR_UTF8.cpp)  # Add other source files here

