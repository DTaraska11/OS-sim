cmake_minimum_required(VERSION 3.14)
project(project1)

set(CMAKE_CXX_STANDARD 14)

add_executable(project1 main.cpp Job.h compare_time.h read_config.h definitions.h)