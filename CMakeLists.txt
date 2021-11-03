cmake_minimum_required(VERSION 3.17.5)
project(BinarySignal)

set(CMAKE_CXX_STANDARD 20)

link_directories(C:/Users/Admin/CLionProjects/Library/BS/lib)

add_subdirectory(Google_tests)

add_executable(BinarySignal main.cpp binarySignal.cpp binarySignal.h menu.cpp menu.h)

find_library(TEST_LIBRARY test_library library)

target_link_libraries(BinarySignal libBS.a)