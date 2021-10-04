cmake_minimum_required(VERSION 3.10)
project(float)
add_executable(float float.cpp)
target_compile_options(float PUBLIC -Wall -g)
