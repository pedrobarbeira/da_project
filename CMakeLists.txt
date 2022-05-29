cmake_minimum_required(VERSION 3.19)
project(da_project)

set(CMAKE_CXX_STANDARD 23)

include_directories(src)

add_executable(da_project
        main.cpp
        src/graph.h
        src/util.h
        src/maxHeap.h
        src/exception.h
        src/minHeap.h)
