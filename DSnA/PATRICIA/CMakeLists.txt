cmake_minimum_required(VERSION 3.10)
project(patricia)

add_library(patlib STATIC src/PATRICIA.cpp)	

add_executable(patricia src/main.cpp)

target_include_directories(patlib PRIVATE include/)
target_include_directories(patricia PRIVATE include/)
target_link_libraries(patricia patlib)	