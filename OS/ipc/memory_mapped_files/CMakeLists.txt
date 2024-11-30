cmake_minimum_required(VERSION 2.8)

project(mmf_ipc)

add_compile_options(--std=c11 -Wall -pedantic -g)

add_executable(parent parent.c)
add_executable(child1 child1.c)
add_executable(child2 child2.c)