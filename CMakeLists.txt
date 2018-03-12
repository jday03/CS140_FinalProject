cmake_minimum_required(VERSION 3.8)
project(CS140_FinalProject)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp pennant.cpp pennant.h)
add_executable(CS140_FinalProject ${SOURCE_FILES} pennant.cpp pennant.h)