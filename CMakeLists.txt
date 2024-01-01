# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.

cmake_minimum_required(VERSION 3.27)
project(StructsPp_Project)

set(CMAKE_CXX_STANDARD 20)
add_executable(StructsPp
        include/string.h
        include/file.h
        include/list.h
        test/test.cpp
        include/concept.h
        include/concept.h
        "include/allheader(msvc).h"
)
