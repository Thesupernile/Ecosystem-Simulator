cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED False)

project(EcoSimulator)
include_directories(EcoSimulator src/headers)
add_executable(EcoSimulator src/main.cpp src/animal.cpp src/utilities.cpp)