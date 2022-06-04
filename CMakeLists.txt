cmake_minimum_required(VERSION 3.19)
project(da_project)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

add_executable(da_project
        main.cpp
        src/graph.h
        src/utils.h
        src/maxHeap.h
        src/exception.h
        src/minHeap.h
        src/case1.h
        src/case2.h
        src/paretograph.h
        src/fulkersongraph.h
        src/timegraph.h
        src/testfulkerson.h
        src/caseJ.h)
