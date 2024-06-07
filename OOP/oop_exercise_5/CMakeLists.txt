cmake_minimum_required(VERSION 2.8)

project(oop_exercise_5)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/mnt/d/X-Files/MAI/3 sem/OOp/labs/oop_exercise_5")

add_compile_options(--std=c++20)

add_executable(oop_exercise_5 main.cpp)

target_include_directories(oop_exercise_5
 PRIVATE
  headers/)