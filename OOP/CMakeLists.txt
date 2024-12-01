cmake_minimum_required(VERSION 2.8)

project(oop_exercise_7)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../")

add_compile_options(--std=c++20 -Wall -pedantic -g)

add_executable(oop_exercise_7 main.cpp)

target_include_directories(oop_exercise_7
 PRIVATE
  headers/)